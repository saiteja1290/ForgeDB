
#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdint.h>

#define RECORD_SIZE 40

// Write one user record at the current file position
int write_user(FILE *file,
               uint8_t status,
               uint32_t id,
               uint32_t age,
               const char *name);

// Read one user record at the current file position
void read_user(FILE *file);

// Read a user record at a specific slot number
void read_user_at(FILE *file, uint8_t slot_number);

#endif
