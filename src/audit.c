#include <stdio.h>
#include <string.h>

// Audit structure
struct audit {
    int audit_id;
    float donation_amount;
    char handled_by[50];     // Who handled the audit
    char compliance_status[10]; // approved / pending
};

void add_audit()
{
    struct audit a;
    FILE *fp;

    // Input details
    printf("\nEnter Audit ID: ");
    scanf("%d", &a.audit_id);

    printf("Enter Donation Amount: ");
    scanf("%f", &a.donation_amount);

    printf("Enter Name of Person Handling Audit: ");
    scanf("%s", a.handled_by);

    printf("Enter Compliance Status (approved/pending): ");
    scanf("%s", a.compliance_status);

    // Save to file
    fp = fopen("audit.dat", "ab");
    if (fp == NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("Audit record saved successfully!\n");
}

// Function to display all audits
void display_audits()
{
    struct audit a;
    FILE *fp = fopen("audit.dat", "rb");
    if (fp == NULL)
    {
        printf("No audit records found!\n");
        return;
    }

    printf("\n--- Audit Records ---\n");
    while (fread(&a, sizeof(a), 1, fp))
    {
        printf("Audit ID         : %d\n", a.audit_id);
        printf("Donation Amount  : %.2f\n", a.donation_amount);
        printf("Handled By       : %s\n", a.handled_by);
        printf("Compliance Status: %s\n", a.compliance_status);
        printf("-------------------------------\n");
    }

    fclose(fp);
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Audit Menu ---\n");
        printf("1. Add Audit Record\n");
        printf("2. Display Audit Records\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            add_audit();
        else if (choice == 2)
            display_audits();
        else if (choice == 3)
        {
            printf("Exiting...\n");
            break;
        }
        else
            printf("Invalid choice! Try again.\n");
    }

    return 0;
}