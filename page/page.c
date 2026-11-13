#include <stdio.h>
#include <stdint.h>

#define HEADER_SIZE 16
#define PAGE_SIZE 4096

int write_page(FILE *file, uint32_t page_id, const uint8_t *page_data)
{
    uint32_t offset = HEADER_SIZE + (page_id * PAGE_SIZE);

    if (fseek(file, offset, SEEK_SET) != 0)
        return 0;
    if (fwrite(page_data, PAGE_SIZE, 1, file) != 1)
        return 0;

    return 1;
}

int read_page(FILE *file, uint32_t page_id, uint8_t *page_data)
{

    uint32_t offset = HEADER_SIZE + (page_id * PAGE_SIZE);

    if (fseek(file, offset, SEEK_SET) != 0)
        return 0;

    if (fread(page_data, PAGE_SIZE, 1, file) != 1)
        return 0;

    return 1;
}
