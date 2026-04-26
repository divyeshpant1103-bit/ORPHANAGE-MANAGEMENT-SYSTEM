#include <stdio.h>
#include <string.h>
#include "data_management.h"

#define RECORDS_FILE "../data/records.dat"

void add_record()
{
    FILE *fp;
    struct record r;

    // Input record details
    printf("Enter Record ID: ");
    scanf("%d", &r.record_id);

    printf("Enter Record Type (child/staff/donor): ");
    scanf("%9s", r.record_type);

    printf("Enter Name: ");
    scanf("%99s", r.name);

    printf("Enter Action (update/delete): ");
    scanf("%9s", r.action);

    // Save record to file
    fp = fopen(RECORDS_FILE, "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&r, sizeof(r), 1, fp);
    fclose(fp);

    printf("Record saved successfully!\n");
}

void display_records()
{
    FILE *fp;
    struct record r;

    // Display all records
    fp = fopen(RECORDS_FILE, "rb");
    if (fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Records List ---\n");
    while (fread(&r, sizeof(r), 1, fp))
    {
        printf("ID: %d\n", r.record_id);
        printf("Type: %s\n", r.record_type);
        printf("Name: %s\n", r.name);
        printf("Action: %s\n", r.action);
        printf("-------------------\n");
    }
    fclose(fp);
}

void data_management_menu()
{
    int choice;

    while (1)
    {
        printf("\n--- Data Management ---\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            add_record();
        }
        else if (choice == 2)
        {
            display_records();
        }
        else if (choice == 0)
        {
            return;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }
}