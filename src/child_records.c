#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/child.h"

struct Orphan *children = NULL;
int child_count = 0;
int children_capacity = 0;
int next_child_id=1000;

void child_menu(){
    int choice;
    while(1){
        
        printf("1.To add child detail\n");
        printf("2.To display the child detail\n");
        printf("3.To search the child\n");
        printf("4.To delete the child detail\n");
        printf("5.To update the child detail\n");
        printf("0. Back\n");
        printf("Enter the choice: ");
        scanf("%d",&choice);
        switch(choice){
            
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
            default: printf("Invalid choice!\n") ;

        }
    }
}
void child_add(){
    // Resize array if needed
    if (child_count >= children_capacity) {
        int new_capacity = (children_capacity == 0) ? 10 : children_capacity * 2;
        struct Orphan *temp = realloc(children, new_capacity * sizeof(struct Orphan));
        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
        children = temp;
        children_capacity = new_capacity;
    }
    
    int i = child_count;
    getchar();//conume the newline character len by scanf
    
    children[i].child_id = generate_child_id();
    printf("Assigned Child ID: %d\n", children[i].child_id);
    printf("Enter the child name: ");
    fgets(children[i].child_name,100,stdin);
    children[i].child_name[strcspn(children[i].child_name,"\n")]=0;

    printf("Enter the Child gender: ");
    fgets(children[i].child_gender,50,stdin);
    children[i].child_gender[strcspn(children[i].child_gender,"\n")]=0;

    printf("Enter the child age: ");
    scanf("%d",&children[i].child_age);
    getchar();

    printf("Enter th child blood group: ");
    fgets(children[i].child_BG,20,stdin);
    children[i].child_BG[strcspn(children[i].child_BG,"\n")]=0;

    printf("Enter child education: ");
    fgets(children[i].education,100,stdin);
    children[i].education[strcspn(children[i].education,"\n")]=0;

    printf("Enter the child health status: ");
    fgets(children[i].health_status,20,stdin);
    children[i].health_status[strcspn(children[i].health_status,"\n")]=0;

    printf("Enter the child medical report: ");
    fgets(children[i].medical_report,20,stdin);
    children[i].medical_report[strcspn(children[i].medical_report,"\n")]=0;

    printf("Enter date of admission: ");
    fgets(children[i].date_of_admission,20,stdin);
    children[i].date_of_admission[strcspn(children[i].date_of_admission,"\n")]=0;

    printf("Enter the status: ");
    fgets(children[i].status,20,stdin);
    children[i].status[strcspn(children[i].status,"\n")]=0;

    child_count++;
}

void child_display(){
    if(child_count==0){
        printf("NO child record found!\n");
        return;
    }
    printf("\n======== CHILD RECORDS ===========\n");
    for(int i=0;i<child_count;i++){

        printf("CHILD ID: %d\n",children[i].child_id);
        printf("CHILD NAME: %s\n",children[i].child_name);
        printf("CHILD GENDER: %s\n",children[i].child_gender);
        printf("CHILD AGE: %d\n",children[i].child_age);
        printf("CHILD BLOOD GROUP: %s\n",children[i].child_BG);
        printf("CHILD EDUCATION: %s\n",children[i].education);
        printf("CHILD HEALTH STATUS: %s\n",children[i].health_status);
        printf("CHILD MEDICAL REPORT: %s\n",children[i].medical_report);
        printf("DATE OF ADMISSION: %s\n",children[i].date_of_admission);
        printf("STATUS: %s\n",children[i].status);
        printf("-----------------------------\n");

    }
    
}

void child_search(){
    if(child_count==0){
        printf("NO child record found!\n");
        return; 
    }
    printf("Enter the child ID to search: ");
    int id;
    int found=0;
    scanf("%d",&id);
    printf("\n======== SEARCH RESULT ===========\n");
    for(int i=0;i<child_count;i++){
        if(children[i].child_id==id){

            printf("CHILD ID: %d\n",children[i].child_id);
            printf("CHILD NAME: %s\n",children[i].child_name);
            printf("CHILD GENDER: %s\n",children[i].child_gender);
            printf("CHILD AGE: %d\n",children[i].child_age);
            printf("CHILD BLOOD GROUP: %s\n",children[i].child_BG);
            printf("CHILD EDUCATION: %s\n",children[i].education);
            printf("CHILD HEALTH STATUS: %s\n",children[i].health_status);
            printf("CHILD MEDICAL REPORT: %s\n",children[i].medical_report);
            printf("DATE OF ADMISSION: %s\n",children[i].date_of_admission);
            printf("STATUS: %s\n",children[i].status);
            printf("-----------------------------\n");
            found=1;
            break;

        }

    }
    if(found==0){
        printf("Child with ID %d not found!\n",id);

    }

}

void child_delete(){
    if(child_count==0){
        printf("NO CHILD RECORD FORUND!\n");
        return ;
    }
    int id;
    printf("Enter the child ID to delete: ");
    scanf("%d",&id);
    getchar();
    int found=-1;
    for(int i=0;i<child_count;i++){
        if(children[i].child_id==id){
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("Child with ID %d not found!\n",id);
        return;
    }
    for(int i=found;i<child_count-1;i++){
        children[i]=children[i+1];
    }
    child_count--;
    printf("Child with ID %d deleted successfully!\n",id);
}

void child_update(){
    if(child_count==0){
        printf("NO CHILD RECORD FOUND!\n");
        return;
    }
    int id;
    printf("Enter th child ID to update: ");
    scanf("%d",&id);
    getchar();
    int found=-1;
    for(int i=0;i<child_count;i++){
        if(children[i].child_id==id){
            found=i;
            break;
        }
    }
    if(found==-1){
        printf("Child with ID %d not found!\n",id);
        return;
    }
    while(1){
        printf("1. Update child name\n");
        printf("2. Update childe age\n");
        printf("3. Update child gender\n");
        printf("4. Update child blood group\n");
        printf("5. Update child education\n");
        printf("6. Update child health status\n");
        printf("7. Update child medical report\n");
        printf("8. Update child status\n");
        printf("0. Back\n");
        printf("Enter the choice: ");
        int choice;
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1: printf("Enter the new child name: ");
                    fgets(children[found].child_name,100,stdin);
                    children[found].child_name[strcspn(children[found].child_name,"\n")]=0;
                    printf("Child name Updated successfully!\n");
                    break;
            case 2: printf("Enter the new child age: ");
                    scanf("%d",&children[found].child_age);
                    getchar();
                    printf("Child age updated successfully!\n");
                    break;
            case 3: printf("Enter the child gender: ");
                    fgets(children[found].child_gender,50,stdin);
                    children[found].child_gender[strcspn(children[found].child_gender,"\n")]=0;
                    printf("Child gender updated successfully!\n");
                    break;
            
            case 4: printf("Enter the blood group: ");
                    fgets(children[found].child_BG,20,stdin);
                    children[found].child_BG[strcspn(children[found].child_BG,"\n")]=0;
                    printf("Child blood group updated successfully!\n");
                    break;
            case 5: printf("Update child education: ");
                    fgets(children[found].education,100,stdin);
                    children[found].education[strcspn(children[found].education,"\n")]=0;
                    printf("Child gender updated successfully!\n");
                    break;
            case 6: printf("Update child health status: ");
                    fgets(children[found].health_status,80,stdin);
                    children[found].health_status[strcspn(children[found].health_status,"\n")]=0;
                    printf("Child gender updated successfully!\n");
                    break;
            case 7: printf("Update child medical report: ");
                    fgets(children[found].medical_report,100,stdin);
                    children[found].medical_report[strcspn(children[found].medical_report,"\n")]=0;
                    printf("Child gender updated successfully!\n");
                    break;
            case 8: printf("Update child status: ");
                    fgets(children[found].status,20,stdin);
                    children[found].status[strcspn(children[found].status,"\n")]=0;
                    printf("Child gender updated successfully!\n");
                    break;
            case 0: return;
            default: printf("Invalid choice!\n");   
    }
}
}

int generate_child_id(){
    int id = next_child_id;
    printf("Suggested Child ID: %d\n", id);
    printf("Use this ID when adding a new child!\n"); 
    return id; 
}
int update_child_Status(int child_id, const char *new_status){
    for(int i=0;i<child_count;i++){
        if(children[i].child_id==child_id){
            strcpy(children[i].status,new_status);
            return 1;
        }
    }
    return 0;
}