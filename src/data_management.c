#include <stdio.h>
#include <string.h>
#include "../include/data_management.h"
#include "child.h"
#include "adoption.h"
#include "auth.h"
#include "staff.h"
#include "donar.h"
#include "report.h"
#include "audit.h"



void data_management()
{
    int choice;
    while (1) {
        printf("\n1. Add child record\n");
        printf("2. Display all children\n");
        printf("3. Search child by ID\n");
        printf("4. Delete child record\n");
        printf("5. Update child record\n");
        printf("\n6. To add donor details\n");
        printf("7. To display donor list\n");
        printf("8. To search donor\n");
        printf("9. To update donor details\n");
        printf("10. To delete donor details\n");
        printf("\n11. To add Staff details\n");
        printf("12. To display Staff list\n");
        printf("13. To search Staff\n");
        printf("14. To update Staff details\n");
        printf("15. To delete Staff details\n");
        printf("0. Back\n");
        printf("Enter the choice: ");
        scanf("%d",&choice);
        getchar();
        printf("\n");
        switch (choice)
        {
        
            case 1:
                child_add();     
                break;
            case 2: 
                child_display(); 
                break;
            case 3: 
                child_search();  
                break;
            case 4:
                child_delete();  
                break;
            case 5:
                 child_update();  
                break;
            case 6:
                add_donar();
                break;
            case 7:
                display_donar_list();
                break;
            case 8:
                search_donar();
                break;
            case 9:
                update_donar_details();
                break;
            case 10:
                delete_donar();
                break;
            case 11:
                add_staff();
                break;
            case 12:
                display_staff_list();
                break;
            case 13:
                search_staff();
                break;
            case 14:
                update_staff_details();
                break;
            case 15:
                delete_staff();
                break;
            case 0: 
                return;
            default: printf("Invalid choice!\n");
        }
    }
}
