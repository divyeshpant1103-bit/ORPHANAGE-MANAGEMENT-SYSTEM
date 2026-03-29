#include <stdio.h>
#include <string.h>
#include "../include/child.h"
#include "../include/adoption.h"

int main() {
    int choice;
    
    // load data here later
    
    while(1) {
        printf("\n===== ORPHANAGE MANAGEMENT SYSTEM =====\n");
        printf("1. Child Records\n");
        printf("2. Staff Management\n");
        printf("3. Donations\n");
        printf("4. Adoption\n");
        printf("5. Reports\n");
        printf("0. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: child_menu(); 
            break;
            case 0: printf("Goodbye!\n"); 
            return 0;
            default: printf("Invalid choice!\n");
            case 4:adoption_menu();
            break;
        }
    }
    return 0;
}