#include <stdio.h>
#include <string.h>


struct record {
    int record_id;
    char record_type[10];   // child / staff / donor
    char name[100];
    char action[10];        // update / delete
};

int main()
{
    FILE *fp;
    struct record r;
    int choice;

    while (1)
    {
        printf("\n--- Data Management ---\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // Input record details
            printf("Enter Record ID: ");
            scanf("%d", &r.record_id);

            printf("Enter Record Type (child/staff/donor): ");
            scanf("%s", r.record_type);

            printf("Enter Name: ");
            scanf("%s", r.name);

            printf("Enter Action (update/delete): ");
            scanf("%s", r.action);

            // Save record to file
            fp = fopen("records.dat", "ab");
            if (fp == NULL)
            {
                printf("Error opening file!\n");
                continue;
            }
            fwrite(&r, sizeof(r), 1, fp);
            fclose(fp);

            printf("Record saved successfully!\n");
        }
        else if (choice == 2)
        {
            // Display all records
            fp = fopen("records.dat", "rb");
            if (fp == NULL)
            {
                printf("No records found!\n");
                continue;
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
        else if (choice == 3)
        {
            printf("Exiting program...\n");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}