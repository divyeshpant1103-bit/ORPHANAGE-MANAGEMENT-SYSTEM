#include <stdio.h>
#include "child.h"
#include "staff.h"
#include "adoption.h"

void generate_report()
{
    FILE *fp;
    int total_children = 0, total_staff = 0, total_adoptions = 0;

    struct Orphan c;
    struct staff s;
    struct adoption a;

    // Count children
    fp = fopen("children.dat", "rb");
    if (fp != NULL)
    {
        while (fread(&c, sizeof(c), 1, fp))
            total_children++;
        fclose(fp);
    }

    // Count staff
    fp = fopen("staff.dat", "rb");
    if (fp != NULL)
    {
        while (fread(&s, sizeof(s), 1, fp))
            total_staff++;
        fclose(fp);
    }

    // Count adoptions
    fp = fopen("adoption.dat", "rb");
    if (fp != NULL)
    {
        while (fread(&a, sizeof(a), 1, fp))
            total_adoptions++;
        fclose(fp);
    }

    // Display report
    printf("\n===== REPORT =====\n");
    printf("Report ID       : 1\n");
    printf("Total Children  : %d\n", total_children);
    printf("Total Staff     : %d\n", total_staff);
    printf("Total Adoptions : %d\n", total_adoptions);
    printf("==================\n");
}