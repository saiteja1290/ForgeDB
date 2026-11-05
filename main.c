#include <stdio.h>
#include <stdint.h>

#include "storage/storage.h"
#include "record/record.h"
#include "database/database.h"

int main(void)
{
    FILE *db = fopen("forgedb.db", "wb");

    if (db == NULL)
    {
        perror("Failed to create database");
        return 1;
    }

    // Initialize header
    fwrite("FRGD", 1, 4, db);
    write_u32_le(db, 0);
    write_u32_le(db, UINT32_MAX);
    write_u32_le(db, 0);

    fclose(db);

    db = fopen("forgedb.db", "r+b");

    if (db == NULL)
    {
        perror("Failed to open database");
        return 1;
    }

    if (!insert_user(db, 1, 20, "Alice") ||
        !insert_user(db, 2, 21, "Bob") ||
        !insert_user(db, 3, 22, "Teja") ||
        !insert_user(db, 4, 32, "asdasd"))
    {
        printf("Insertion failed\n");
        fclose(db);
        return 1;
    }

    fclose(db);

    db = fopen("forgedb.db", "rb");

    if (db == NULL)
    {
        perror("Failed to open database for reading");
        return 1;
    }

    printf("Reading database:\n\n");

    read_user_at(db, 0);
    read_user_at(db, 1);
    read_user_at(db, 2);
    read_user_at(db, 3);

    fclose(db);

    return 0;
}