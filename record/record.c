#include <stdio.h>
#include <stdint.h>
#include "record.h"
#include "../storage/storage.h"
#include <string.h>
void read_user(FILE *file)
{
    // read status
    uint8_t status;
    fread(&status, 1, 1, file);

    // read id (int)
    uint32_t id = read_u32_le(file);
    uint32_t age = read_u32_le(file);

    if (status == 0)
    {
        printf("this user has been deleted");
        return;
    }

    // read name
    char name[32] = {0};

    fread(name, 1, 31, file);

    printf("ID: %u\n", id);
    printf("Age: %u\n", age);
    printf("Name: %s\n", name);
}

int write_user(FILE *file, uint8_t status,
               uint32_t id, uint32_t age,
               const char *name)
{
    char name_buffer[31] = {0};

    size_t name_length = strlen(name);

    if (name_length > 31)
        return 0;

    memcpy(name_buffer, name, name_length);

    if (fwrite(&status, 1, 1, file) != 1)
        return 0;

    if (!write_u32_le(file, id))
        return 0;

    if (!write_u32_le(file, age))
        return 0;

    if (fwrite(name_buffer, 1, 31, file) != 31)
        return 0;

    return 1;
}

void read_user_at(FILE *file, uint8_t slotnumber)
{

    fseek(file, 16 + (40 * slotnumber), SEEK_SET);

    read_user(file);
}
