#ifndef PAGE_H
#define PAGE_H

#include <stdint.h>
#include <stdio.h>

#define PAGE_SIZE 4096

int write_page(FILE *file, uint32_t page_id, const uint8_t *page_data);

int read_page(FILE *file, uint32_t page_id, uint8_t *page_data);

#endif