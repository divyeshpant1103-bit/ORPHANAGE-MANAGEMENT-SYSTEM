#include <ctype.h>
#include <stdio.h>
#include "child.h"
#include "staff.h"
#include "adoption.h"
#include "report.h"

#define CHILD_DATA_FILE_PRIMARY "../data/children.dat"
#define CHILD_DATA_FILE_FALLBACK "data/children.dat"
#define STAFF_DATA_FILE "../data/staff.txt"

static int count_children_records()
{
    FILE *fp = fopen(CHILD_DATA_FILE_PRIMARY, "rb");
    if (fp == NULL)
    {
        fp = fopen(CHILD_DATA_FILE_FALLBACK, "rb");
    }

    if (fp == NULL)
    {
        return 0;
    }

    int total_children = 0;
    struct Orphan c;
    while (fread(&c, sizeof(c), 1, fp))
    {
        total_children++;
    }

    fclose(fp);
    return total_children;
}

static int count_staff_records()
{
    FILE *fp = fopen(STAFF_DATA_FILE, "r");
    if (fp == NULL)
    {
        fp = fopen("data/staff.txt", "r");
    }

    if (fp == NULL)
    {
        return 0;
    }

    char line[300];
    /* Skip header lines if present */
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    int total_staff = 0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (isdigit((unsigned char)line[0]))
        {
            total_staff++;
        }
    }

    fclose(fp);
    return total_staff;
}

static int count_adoption_records()
{
    return adoption_count;
}

void generate_report()
{
    int total_children = count_children_records();
    int total_staff = count_staff_records();
    int total_adoptions = count_adoption_records();

    printf("\n===== REPORT =====\n");
    printf("Report ID       : 1\n");
    printf("Total Children  : %d\n", total_children);
    printf("Total Staff     : %d\n", total_staff);
    printf("Total Adoptions : %d\n", total_adoptions);
    printf("==================\n");
}