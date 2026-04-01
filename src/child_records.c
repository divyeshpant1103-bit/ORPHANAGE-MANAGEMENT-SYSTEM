/*
 * ============================================================
 *  child_records.c  —  Child Module for Orphanage Management System
 *  Handles: Add / Display / Search / Delete / Update children
 * ============================================================
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/child.h"

/* ── File paths (primary first, fallback if primary fails) ── */
#define CHILD_DATA_FILE_PRIMARY  "../data/children.dat"
#define CHILD_DATA_FILE_FALLBACK "data/children.dat"

/* ── Global variables (shared across this module) ── */
struct Orphan *children = NULL;  /* dynamic array of child records  */
int child_count       = 0;     /* how many children are stored     */
int children_capacity = 0;     /* current allocated size of array  */
int next_child_id     = 1000;  /* auto-increment ID starting point */


/* ════════════════════════════════════════════════════════════
   MENU  —  shown when user enters the Child section
   ════════════════════════════════════════════════════════════ */
void child_menu() {

    /* Load data from file only once per program run */
    static int loaded_once = 0;
    if (!loaded_once) {
        load_children();
        loaded_once = 1;
    }

    int choice;
    while (1) {
        printf("\n====== CHILD MENU ======\n");
        printf("1. Add child record\n");
        printf("2. Display all children\n");
        printf("3. Search child by ID\n");
        printf("4. Delete child record\n");
        printf("5. Update child record\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: child_add();     
            break;
            case 2: child_display(); 
            break;
            case 3: child_search();  
            break;
            case 4: child_delete();  
            break;
            case 5: child_update();  
            break;
            case 0: return;
            default: printf("Invalid choice!\n");
        }
    }
}


/* ════════════════════════════════════════════════════════════
   ADD CHILD  —  takes input for all fields and saves to file
   ════════════════════════════════════════════════════════════ */
void child_add() {

    /* If the array is full, double its size using realloc */
    if (child_count >= children_capacity) {
        int new_capacity = (children_capacity == 0) ? 10 : children_capacity * 2;
        struct Orphan *temp = realloc(children, new_capacity * sizeof(struct Orphan));
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        children          = temp;
        children_capacity = new_capacity;
    }

    int i = child_count; /* index where new child will be stored */

    /* consume the leftover '\n' character left by previous scanf */
    getchar();

    /* Auto-assign a unique ID */
    children[i].child_id = generate_child_id();
    printf("Assigned Child ID: %d\n", children[i].child_id);

    printf("Enter child name: ");
    fgets(children[i].child_name, 100, stdin);
    children[i].child_name[strcspn(children[i].child_name, "\n")] = 0; /* remove trailing newline */

    printf("Enter child gender: ");
    fgets(children[i].child_gender, 50, stdin);
    children[i].child_gender[strcspn(children[i].child_gender, "\n")] = 0;

    printf("Enter child age: ");
    scanf("%d", &children[i].child_age);
    getchar(); /* consume '\n' after scanf for age */

    printf("Enter child blood group: ");
    fgets(children[i].child_BG, 20, stdin);
    children[i].child_BG[strcspn(children[i].child_BG, "\n")] = 0;

    printf("Enter child education: ");
    fgets(children[i].education, 100, stdin);
    children[i].education[strcspn(children[i].education, "\n")] = 0;

    printf("Enter child health status: ");
    fgets(children[i].health_status, 80, stdin);
    children[i].health_status[strcspn(children[i].health_status, "\n")] = 0;

    printf("Enter child medical report: ");
    fgets(children[i].medical_report, 100, stdin);
    children[i].medical_report[strcspn(children[i].medical_report, "\n")] = 0;

    /* Date of admission — plain input, no validation applied */
    printf("Enter date of admission (DD-MM-YYYY): ");
    fgets(children[i].date_of_admission, 20, stdin);
    children[i].date_of_admission[strcspn(children[i].date_of_admission, "\n")] = 0;

    strcpy(children[i].status,"not adopted");

    child_count++; /* record successfully added, increase count */
    save_children();
    printf("Child record added successfully!\n");
}


/* ════════════════════════════════════════════════════════════
   DISPLAY  —  prints all child records on screen
   ════════════════════════════════════════════════════════════ */
void child_display() {
    if (child_count == 0) {
        printf("No child records found!\n");
        return;
    }

    printf("\n======== CHILD RECORDS ========\n");
    for (int i = 0; i < child_count; i++) {
        printf("Child ID       : %d\n", children[i].child_id);
        printf("Name           : %s\n", children[i].child_name);
        printf("Gender         : %s\n", children[i].child_gender);
        printf("Age            : %d\n", children[i].child_age);
        printf("Blood Group    : %s\n", children[i].child_BG);
        printf("Education      : %s\n", children[i].education);
        printf("Health Status  : %s\n", children[i].health_status);
        printf("Medical Report : %s\n", children[i].medical_report);
        printf("Date Admitted  : %s\n", children[i].date_of_admission);
        printf("Status         : %s\n", children[i].status);
        printf("-------------------------------\n");
    }
}


/* ════════════════════════════════════════════════════════════
   SEARCH  —  find and display a child by their ID
   ════════════════════════════════════════════════════════════ */
void child_search() {
    if (child_count == 0) {
        printf("No child records found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter child ID to search: ");
    scanf("%d", &id);

    printf("\n======== SEARCH RESULT ========\n");
    for (int i = 0; i < child_count; i++) {
        if (children[i].child_id == id) {
            printf("Child ID       : %d\n", children[i].child_id);
            printf("Name           : %s\n", children[i].child_name);
            printf("Gender         : %s\n", children[i].child_gender);
            printf("Age            : %d\n", children[i].child_age);
            printf("Blood Group    : %s\n", children[i].child_BG);
            printf("Education      : %s\n", children[i].education);
            printf("Health Status  : %s\n", children[i].health_status);
            printf("Medical Report : %s\n", children[i].medical_report);
            printf("Date Admitted  : %s\n", children[i].date_of_admission);
            printf("Status         : %s\n", children[i].status);
            printf("-------------------------------\n");
            found = 1;
            break; /* ID is unique, stop searching once found */
        }
    }

    if (!found)
        printf("Child with ID %d not found!\n", id);
}


/* ════════════════════════════════════════════════════════════
   DELETE  —  remove a child record by ID, shift array left
   ════════════════════════════════════════════════════════════ */
void child_delete() {
    if (child_count == 0) {
        printf("No child records found!\n");
        return;
    }

    int id;
    printf("Enter child ID to delete: ");
    scanf("%d", &id);
    getchar();

    /* Search for the child */
    int found = -1;
    for (int i = 0; i < child_count; i++) {
        if (children[i].child_id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Child with ID %d not found!\n", id);
        return;
    }

    /*
     * Shift all records after the deleted one, one position left.
     * This overwrites the deleted record and closes the gap.
     * Example: [A, B, C, D]  delete B  →  [A, C, D]
     */
    for (int i = found; i < child_count - 1; i++)
        children[i] = children[i + 1];

    child_count--;
    save_children();
    printf("Child with ID %d deleted successfully!\n", id);
}


/* ════════════════════════════════════════════════════════════
   UPDATE  —  edit one specific field of a child record
   ════════════════════════════════════════════════════════════ */
void child_update() {
    if (child_count == 0) {
        printf("No child records found!\n");
        return;
    }

    int id;
    printf("Enter child ID to update: ");
    scanf("%d", &id);
    getchar();

    /* Find the child */
    int found = -1;
    for (int i = 0; i < child_count; i++) {
        if (children[i].child_id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Child with ID %d not found!\n", id);
        return;
    }

    int choice;
    while (1) {
        printf("\n--- Update Menu ---\n");
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. Gender\n");
        printf("4. Blood group\n");
        printf("5. Education\n");
        printf("6. Health status\n");
        printf("7. Medical report\n");
        printf("8. Status\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter new name: ");
                fgets(children[found].child_name, 100, stdin);
                children[found].child_name[strcspn(children[found].child_name, "\n")] = 0;
                printf("Name updated successfully!\n");
                save_children();
                break;

            case 2:
                printf("Enter new age: ");
                scanf("%d", &children[found].child_age);
                getchar();
                printf("Age updated successfully!\n");
                save_children();
                break;

            case 3:
                printf("Enter new gender: ");
                fgets(children[found].child_gender, 50, stdin);
                children[found].child_gender[strcspn(children[found].child_gender, "\n")] = 0;
                printf("Gender updated successfully!\n");
                save_children();
                break;

            case 4:
                printf("Enter new blood group: ");
                fgets(children[found].child_BG, 20, stdin);
                children[found].child_BG[strcspn(children[found].child_BG, "\n")] = 0;
                printf("Blood group updated successfully!\n");
                save_children();
                break;

            case 5:
                printf("Enter new education: ");
                fgets(children[found].education, 100, stdin);
                children[found].education[strcspn(children[found].education, "\n")] = 0;
                printf("Education updated successfully!\n");
                save_children();
                break;

            case 6:
                printf("Enter new health status: ");
                fgets(children[found].health_status, 80, stdin);
                children[found].health_status[strcspn(children[found].health_status, "\n")] = 0;
                printf("Health status updated successfully!\n");
                save_children();
                break;

            case 7:
                printf("Enter new medical report: ");
                fgets(children[found].medical_report, 100, stdin);
                children[found].medical_report[strcspn(children[found].medical_report, "\n")] = 0;
                printf("Medical report updated successfully!\n");
                save_children();
                break;

            case 8:
                printf("Enter new status: ");
                fgets(children[found].status, 20, stdin);
                children[found].status[strcspn(children[found].status, "\n")] = 0;
                printf("Status updated successfully!\n");
                save_children();
                break;

            case 0:
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}


/* ════════════════════════════════════════════════════════════
   GENERATE CHILD ID  —  returns next available unique ID
   Uses post-increment: returns current value, then adds 1
   ════════════════════════════════════════════════════════════ */
int generate_child_id() {
    return next_child_id++;
}


/* ════════════════════════════════════════════════════════════
   UPDATE STATUS  —  called by adoption module to change status
   Returns 1 if child found and updated, 0 if not found
   ════════════════════════════════════════════════════════════ */
int update_child_Status(int child_id, const char *new_status) {
    for (int i = 0; i < child_count; i++) {
        if (children[i].child_id == child_id) {
            strcpy(children[i].status, new_status);
            save_children();
            return 1; /* success */
        }
    }
    return 0; /* child not found */
}


/* ════════════════════════════════════════════════════════════
   SAVE  —  writes all child records to binary file
   File format written in order:
     [child_count]  →  [all records]  →  [next_child_id]
   ════════════════════════════════════════════════════════════ */
void save_children() {

    /* Try primary path first, then fallback */
    FILE *file = fopen(CHILD_DATA_FILE_PRIMARY, "wb");
    if (file == NULL)
        file = fopen(CHILD_DATA_FILE_FALLBACK, "wb");

    if (file == NULL) {
        printf("ERROR: Unable to open child data file for writing.\n");
        return;
    }

    fwrite(&child_count,   sizeof(int),           1,           file);
    fwrite(children,       sizeof(struct Orphan),  child_count, file);
    fwrite(&next_child_id, sizeof(int),            1,           file);

    fclose(file);
}


/* ════════════════════════════════════════════════════════════
   LOAD  —  reads child records from binary file at startup
   File format expected in order:
     [child_count]  →  [all records]  →  [next_child_id]
   ════════════════════════════════════════════════════════════ */
void load_children() {

    /* Try primary path first, then fallback */
    FILE *file = fopen(CHILD_DATA_FILE_PRIMARY, "rb");
    if (file == NULL)
        file = fopen(CHILD_DATA_FILE_FALLBACK, "rb");

    if (file == NULL) {
        /* First run — no file exists yet, start fresh */
        child_count       = 0;
        next_child_id     = 1000;
        children_capacity = 0;
        children          = NULL;
        return;
    }

    /* Step 1: Read how many records were saved */
    fread(&child_count, sizeof(int), 1, file);

    if (child_count > 0) {
        /* Step 2: Allocate memory for that many records */
        children = (struct Orphan *)malloc(sizeof(struct Orphan) * child_count);
        if (children == NULL) {
            printf("Memory allocation failed during load!\n");
            fclose(file);
            child_count = 0;
            return;
        }

        /* Set capacity equal to loaded count so realloc in child_add() works */
        children_capacity = child_count;

        /* Step 3: Read all records into the array */
        fread(children, sizeof(struct Orphan), child_count, file);
    }

    /* Step 4: Read the last used ID so new IDs don't repeat old ones */
    fread(&next_child_id, sizeof(int), 1, file);

    /* Safety check: ID should never go below 1000 */
    if (next_child_id < 1000)
        next_child_id = 1000;

    fclose(file);
    printf("Loaded %d child record(s).\n", child_count);
}