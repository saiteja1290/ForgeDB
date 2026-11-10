#include <stdio.h>
#include <stdint.h>
#include "../storage/storage.h"
#include "../record/record.h"
#include <string.h>

#define HEADER_SIZE 16
#define RECORD_SIZE 40

int insert_user(FILE *file,
                uint32_t id,
                uint32_t age,
                const char *name)
{
    // 2 cases - where free list in header in empty and non empty

    // go to 8th byte to read the free head
    if (fseek(file, 8, SEEK_SET) != 0)
        return 0;

    // go ahead and read the free list
    uint32_t freeListHeader = read_u32_le(file);

    // if case - we have something in free list
    if (freeListHeader != UINT32_MAX)
    {
        uint32_t offset = HEADER_SIZE + (RECORD_SIZE * freeListHeader);

        // Read the next free slot before overwriting this record.
        if (fseek(file, offset + 1, SEEK_SET) != 0)
            return 0;

        uint32_t next_free = read_u32_le(file);

        // Write the new user into the free slot.
        if (fseek(file, offset, SEEK_SET) != 0)
            return 0;

        if (!write_user(file, 1, id, age, name))
            return 0;

        // Update free-list head to the next free slot.
        if (fseek(file, 8, SEEK_SET) != 0)
            return 0;

        // write the next_free integer in the free list
        if (!write_u32_le(file, next_free))
            return 0;
    }
    // else case - we dont anything in free list
    else
    {
        if (fseek(file, 4, SEEK_SET) != 0)
            return 0;

        uint32_t slot_count = read_u32_le(file);

        uint32_t offset = HEADER_SIZE + (RECORD_SIZE * slot_count);
        if (fseek(file, offset, SEEK_SET) != 0)
            return 0;

        if (!write_user(file, 1, id, age, name))
            return 0;

        if (fseek(file, 4, SEEK_SET) != 0)
            return 0;

        if (!write_u32_le(file, slot_count + 1))
            return 0;
    }

    return 1;
}

int delete_user(FILE *file, uint32_t slot_number)

{
    // Read current free-list head
    fseek(file, 8, SEEK_SET);
    uint32_t current_free = read_u32_le(file);

    //  Mark record as free
    fseek(file, 16 + 40 * slot_number, SEEK_SET);

    uint8_t status = 0;
    fwrite(&status, 1, 1, file);

    // Store previous free-list head in the old ID field
    write_u32_le(file, current_free);

    //  Update header with the new free-list head
    fseek(file, 8, SEEK_SET);
    write_u32_le(file, slot_number);

    return 1;
}

int validate_database(FILE *file)
{
    // Function	Purpose
    // strcmp()	Compares null-terminated strings
    // memcmp()	Compares a fixed number of bytes
    // ==	Compares values, or pointer addresses when used with pointers

    // seek to 0th byte
    if (fseek(file, 0, SEEK_SET) != 0)
        return 0;

    // read first 4 bytes

    char magic[4] = {0};

    // read the first 4 bytes
    if (fread(magic, 1, 4, file) != 0)
        return 0;

    // use memcmp
    if (memcmp(magic, "FRGD", 4) == 0)
        return 1;

    return 0;
}