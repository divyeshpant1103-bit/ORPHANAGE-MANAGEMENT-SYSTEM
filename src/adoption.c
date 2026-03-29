#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/adoption.h"
#include "../include/child.h"

struct adoption *adopters = NULL;
int adoption_count = 0;
int adoption_capacity = 0;
int next_adoption_id = 5000;

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
void adoption_search(){}
void adoption_update(){}
void adoption_delete(){}