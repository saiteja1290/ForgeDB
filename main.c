#include <stdio.h>
#include <stdint.h>

#include "storage/storage.h"
#include "record/record.h"
#include "database/database.h"
#include "page/page.h"

// int main(void)
// {
//     FILE *db = fopen("forgedb.db", "wb");

//     if (db == NULL)
//     {
//         perror("Failed to create database");
//         return 1;
//     }

//     // Initialize header
//     fwrite("FRGD", 1, 4, db);
//     write_u32_le(db, 0);
//     write_u32_le(db, UINT32_MAX);
//     write_u32_le(db, 0);

//     fclose(db);

//     db = fopen("forgedb.db", "r+b");

//     if (db == NULL)
//     {
//         perror("Failed to open database");
//         return 1;
//     }

//     if (!insert_user(db, 1, 20, "Alice") ||
//         !insert_user(db, 2, 21, "Bob") ||
//         !insert_user(db, 3, 22, "Teja") ||
//         !insert_user(db, 4, 32, "asdasd"))
//     {
//         printf("Insertion failed\n");
//         fclose(db);
//         return 1;
//     }

//     fclose(db);

//     db = fopen("forgedb.db", "rb");

//     if (db == NULL)
//     {
//         perror("Failed to open database for reading");
//         return 1;
//     }

//     printf("Reading database:\n\n");

//     read_user_at(db, 0);
//     read_user_at(db, 1);
//     read_user_at(db, 2);
//     read_user_at(db, 3);

//     fclose(db);

//     // Deletion
//     db = fopen("forgedb.db", "r+b");

//     if (db == NULL)
//     {
//         perror("Failed to open database for deletion");
//         return 1;
//     }

//     // Delete Teja (slot 2)
//     if (!delete_user(db, 2))
//     {
//         printf("Deletion failed\n");
//         fclose(db);
//         return 1;
//     }

//     // Verify free-list head
//     uint32_t free_head;

//     if (fseek(db, 8, SEEK_SET) != 0)
//     {
//         perror("Failed to seek to free-list head");
//         fclose(db);
//         return 1;
//     }

//     free_head = read_u32_le(db);

//     printf("\nFree-list head: %u\n", free_head);

//     // Read records again
//     printf("\nReading database after deletion:\n\n");

//     read_user_at(db, 0);
//     read_user_at(db, 1);
//     read_user_at(db, 2);
//     read_user_at(db, 3);

//     // Try deleting the same slot again
//     printf("\nAttempting to delete slot 2 again:\n");

//     if (!delete_user(db, 2))
//     {
//         printf("Correctly rejected: slot is already free.\n");
//     }

//     fclose(db);
//     return 0;
// }

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "page/page.h"

int main(void)
{
    FILE *file = fopen("forgedb.db", "r+b");

    if (file == NULL)
    {
        perror("Failed to open database");
        return 1;
    }

    uint8_t page_data[PAGE_SIZE] = {0};

    // Put some sample data into the page.
    strcpy((char *)page_data, "Hello ForgeDB!");

    // Write page 0.
    if (!write_page(file, 0, page_data))
    {
        printf("Failed to write page\n");
        fclose(file);
        return 1;
    }

    // Clear our inmemory RAM buffer.
    memset(page_data, 0, PAGE_SIZE);

    // Read page 0.
    if (!read_page(file, 0, page_data))
    {
        printf("Failed to read page\n");
        fclose(file);
        return 1;
    }

    printf("Page contents: %s\n", (char *)page_data);

    fclose(file);
    return 0;
}