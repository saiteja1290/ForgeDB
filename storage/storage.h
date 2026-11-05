#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include <stdint.h>

int write_u32_le(FILE *file, uint32_t value);
uint32_t read_u32_le(FILE *file);

#endif