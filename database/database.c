#include <stdio.h>
#include <stdint.h>
#include "../storage/storage.h"
#include "../record/record.h"
#include <stdio.h>
#include <stdint.h>

#define HEADER_SIZE 16
#define RECORD_SIZE 40

int insert_user(FILE *file,
                uint32_t id,
                uint32_t age,
                const char *name)
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

    return 1;
}