#include <stdio.h>
#include <stdint.h>

int insert_user(FILE *file,
                uint32_t id,
                uint32_t age,
                const char *name);

int delete_user(FILE *file, uint32_t slot_number);

int validate_database(FILE *file);