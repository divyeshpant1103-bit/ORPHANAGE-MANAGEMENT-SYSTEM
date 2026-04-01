/*
 * adoption.c
 * Manage adoption applications: collect adopter details,
 * track adoption applications, approve adoptions and update
 * related child status via the child records module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/adoption.h"
#include "../include/child.h"
/* Dynamic array for adoption applications */
struct adoption *adopters = NULL;
/* Number of adoption applications currently in memory */
int adoption_count = 0;
/* Allocated capacity of the `adopters` array */
int adoption_capacity = 0;
/* Next adoption id generator */
int next_adoption_id = 5000;


/*
 * adoption_menu: Shows the Adoption menu and routes user choices
 * to adoption operations (add, display, search, update, delete,
 * and approve adoption applications).
 */

void adoption_menu(){
    while(1){
        int choice;
        printf("\n===== ADOPTION MENU =====\n");
        printf("1. Add Adoption Record\n");
        printf("2. Display Adoption Records\n");
        printf("3. Search Adoption Records\n");
        printf("4. Update AdoptionRecord\n");
        printf("5.Delete Adoption Records\n");
        printf("6. Approve Adoption\n");
        printf("0. Back to Main Menu\n");
        printf("==============================\n");
        printf("Enter you choice:");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: adoption_add();
            break;
            case 2: adoption_display();
            break;
            case 3: adoption_search();
            break;
            case 4: adoption_update();
            break;
            case 5: adoption_delete();
            break;
            case 6: adoption_approve();
            break;
            case 0: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/*
 * adoption_add: Gather adopter details, assign an adoption id
 * and store the application in memory (persisting is left to
 * program lifecycle). New records start with status "Pending".
 */
void adoption_add(){
    if(adoption_count>=adoption_capacity){
        int new_capacity=(adoption_capacity==0)?10:adoption_capacity*2;
        struct adoption *temp=realloc(adopters,new_capacity*sizeof(struct adoption));
        if(temp==NULL){
            printf("Memory is not allocted");
            return;
        }
        adopters = temp;
        adoption_capacity = new_capacity;
    }
    int i=adoption_count;
    getchar();
    adopters[i].adoption_id=next_adoption_id++;
    printf("Assigned Adoption Id: %d \n",adopters[i].adoption_id);
    printf("Enter the ID of the child to be adopted:");
    scanf("%d",&adopters[i].child_id);
    getchar();

    printf("Enter the Adopter Name: ");
    fgets(adopters[i].adopter_name,100,stdin);
    adopters[i].adopter_name[strcspn(adopters[i].adopter_name,"\n")]=0;

    printf("Enter th Adopter Age: ");
    scanf("%d",&adopters[i].adopter_age);
    getchar();

    printf("Enter the Adopter Contact: ");
    fgets(adopters[i].adopter_contact,15,stdin);
    adopters[i].adopter_contact[strcspn(adopters[i].adopter_contact,"\n")]=0;

    printf("Enter the Adopter Address: ");
    fgets(adopters[i].adopter_address,150,stdin);
    adopters[i].adopter_address[strcspn(adopters[i].adopter_address,"\n")]=0;

    printf("Enter Adopter Occupation: ");
    fgets(adopters[i].adopter_occupation,50,stdin);
    adopters[i].adopter_occupation[strcspn(adopters[i].adopter_occupation,"\n")]=0;

    printf("Enter Adopter Annual Income: ");
    scanf("%f",&adopters[i].adopter_income);
    getchar();

    printf("Enter the marital status: ");
    fgets(adopters[i].marital_status,20,stdin);
    adopters[i].marital_status[strcspn(adopters[i].marital_status,"\n")]=0;

    printf("Enter the Applicaton form date");
    fgets(adopters[i].application_date,30,stdin);
    adopters[i].application_date[strcspn(adopters[i].application_date,"\n")]=0;

    strcpy(adopters[i].approval_date, "N/A");

    strcpy(adopters[i].status, "Pending");
    
    printf("Adoption application submitted successfully! Status is currently 'Pending'.\n");

    adoption_count++;

}



/*
 * adoption_approve: Mark an adoption record as approved, set
 * the approval date, and update the corresponding child's
 * status by calling `update_child_Status()` from child records.
 */
void adoption_approve(){
    if(adoption_count==0){
        printf("NO Adopters Record!!");
        return ;
    }
    int search_id;
    printf("Enter the Adopter Id to be Approved: ");
    scanf("%d",&search_id);
    getchar();

    int found=-1;
    for(int i=0;i<adoption_count;i++){
        if(adopters[i].adoption_id==search_id){
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("No Adopter found with this Adoption ID\n");
    }
    if(strcmp(adopters[found].status,"Approved")==0){
        printf("This adoption record is already approved!\n");
    }
    strcpy(adopters[found].status,"Approved");

    printf("Enter The Approval Date [dd-mm-yyy]");
    fgets(adopters[found].approval_date,30,stdin);
    adopters[found].approval_date[strcspn(adopters[found].approval_date,"\n")]=0;


    // Call the helper function from child.c (make sure you added it there!)
    int success = update_child_Status(adopters[found].child_id, "Adopted");
    
    if (success) {
        printf("SUCCESS! Adoption %d approved. Child %d status updated to 'Adopted'.\n", search_id, adopters[found].child_id);
    } else {
        printf("WARNING: Adoption approved, but Child ID %d was not found in the system!\n", adopters[found].child_id);
    }

}
/*
 * adoption_display: Print all loaded adoption application records.
 */
void adoption_display(){
    if(adoption_count == 0){
        printf("No adoption records found!\n");
        return;
    }
    printf("\n======== ADOPTION RECORDS ===========\n");
    for(int i = 0; i < adoption_count; i++){
        printf("ADOPTION ID: %d\n", adopters[i].adoption_id);
        printf("CHILD ID: %d\n", adopters[i].child_id);
        printf("ADOPTER NAME: %s\n", adopters[i].adopter_name);
        printf("STATUS: %s\n", adopters[i].status);
        printf("APPROVAL DATE: %s\n", adopters[i].approval_date);
        printf("-----------------------------\n");
    }
}
/*
 * adoption_search: Find and display a single adoption record
 * by adoption id.
 */
void adoption_search(){
    if(adoption_count==0){
        printf("NO adoption record found!!\n");
        return;
    }
    int search_id;
    printf("Enter th Adoption ID to search: ");
    scanf("%d",&search_id);
    getchar();
    int found=-1;
    for(int i=0;i<adoption_count;i++){
        if(adopters[i].adoption_id==search_id){
            printf("ADOPTION ID: %d\n", adopters[i].adoption_id);
            printf("CHILD ID: %d\n", adopters[i].child_id);
            printf("ADOPTER NAME: %s\n", adopters[i].adopter_name);
            printf("ADOPTER AGE: %d\n", adopters[i].adopter_age);
            printf("ADOPTER CONTACT: %s\n", adopters[i].adopter_contact);
            printf("ADOPTER ADDRESS: %s\n", adopters[i].adopter_address);
            printf("ADOPTER OCCUPATION: %s\n", adopters[i].adopter_occupation);
            printf("ADOPTER INCOME: %.2f\n", adopters[i].adopter_income);
            printf("MARITAL STATUS: %s\n", adopters[i].marital_status);
            printf("APPLICATION DATE: %s\n", adopters[i].application_date);
            printf("APPROVAL DATE: %s\n", adopters[i].approval_date);
            printf("STATUS: %s\n", adopters[i].status);
          
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("No adoption record found with this Adoption ID\n");
    }
}
/*
 * adoption_update: Allow interactive updates to an existing
 * adoption application's fields.
 */
void adoption_update(){
    if(adoption_count==0){
        printf("NO adoption record found!!\n");
        return;
    }
    int search_id;
    printf("Enter the Adoption ID to update: ");
    scanf("%d", &search_id);
    getchar();
    int found=-1;
    for(int i=0;i<adoption_count;i++){
        if(adopters[i].adoption_id==search_id){
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("No adoption record found with this Adoption ID\n");
        return;
    }
    while(1){
        printf("\nChoose the data that need to be updated:\n");
        printf("1. Update Adopter Name\n");
        printf("2. Update Adopter Age\n");
        printf("3. Update Adopter Contact\n");
        printf("4. Update Adopter Address\n");
        printf("5. Update Adopter Occuption\n");
        printf("6. Update Adopter Income\n");
        printf("7. Update Marital Status\n");
        printf("0. Back\n");
        printf("Enter the choice: ");
        int choice;
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: printf("Enter the new Adopter Name: ");
                    fgets(adopters[found].adopter_name,100,stdin);
                    adopters[found].adopter_name[strcspn(adopters[found].adopter_name,"\n")]=0;
                    printf("Adopter name updated successfully!\n");
                    break;
            case 2: printf("Enter the new Adopter Age: ");
                    scanf("%d",&adopters[found].adopter_age);
                    getchar();
                    printf("Adopter age updated successfully!\n");
                    break;          
            case 3: printf("Enter the new Adopter Contact: ");
                    fgets(adopters[found].adopter_contact,15,stdin);
                    adopters[found].adopter_contact[strcspn(adopters[found].adopter_contact,"\n")]=0;
                    printf("Adopter contact updated successfully!\n");
                    break;
            case 4: printf("Enter the new Adopter Address: ");
                    fgets(adopters[found].adopter_address,150,stdin);
                    adopters[found].adopter_address[strcspn(adopters[found].adopter_address,"\n")]=0;
                    printf("Adopter address updated successfully!\n");
                    break;
            case 5: printf("Enter the new Adopter Occupation: ");
                    fgets(adopters[found].adopter_occupation,50,stdin);
                    adopters[found].adopter_occupation[strcspn(adopters[found].adopter_occupation,"\n")]=0;
                    printf("Adopter occupation updated successfully!\n");
                    break;
            case 6: printf("Enter the new Adopter Income: ");
                    scanf("%f",&adopters[found].adopter_income);
                    getchar();
                    printf("Adopter income updated successfully!\n");
                    break;
            case 7: printf("Enter the new Marital Status: ");
                    fgets(adopters[found].marital_status,20,stdin);     
                    adopters[found].marital_status[strcspn(adopters[found].marital_status,"\n")]=0;
                    printf("Marital status updated successfully!\n");
                    break;
            case 0: return;
            default: printf("Invalid choice!\n");   
        }
    }
}
void adoption_delete(){
    if(adoption_count==0){
        printf("NO adoption record found!!\n");
        return;
    }
    int search_id;
    printf("Enter th adoption ID to delete: ");
    scanf("%d",&search_id);
    getchar();
    int found=-1;
    for(int i=0;i<adoption_count;i++){
        if(adopters[i].adoption_id==search_id){
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("No adoption record found with this Adoption ID\n");
        return;
    }
    for(int i=found;i<adoption_count-1;i++){
        adopters[i]=adopters[i+1];
        break;
    }
    adoption_count--;
    printf("Adoption record with ID %d deleted successfully!\n", search_id);
}