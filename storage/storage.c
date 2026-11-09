#include <stdio.h>
#include <stdint.h>

// writes an integer to the binary file
int write_u32_le(FILE *file, uint32_t value)
{
    uint8_t bytes[4];

    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;

    return fwrite(bytes, 1, 4, file) == 4;
}

// reads an integer from binary file
uint32_t read_u32_le(FILE *file)
{
    uint8_t bytes[4];

    if (fread(bytes, 1, 4, file) != 4)
    {
        perror("Failed to read 4 bytes");
        return 0;
    }

    uint32_t result =
        (uint32_t)bytes[0] |
        ((uint32_t)bytes[1] << 8) |
        ((uint32_t)bytes[2] << 16) |
        ((uint32_t)bytes[3] << 24);

    return result;
}