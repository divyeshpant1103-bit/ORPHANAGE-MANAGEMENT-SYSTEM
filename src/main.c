#include <stdio.h>
#include <string.h>
#include "../include/child.h"
#include "../include/adoption.h"
#include "../include/auth.h"

static int is_admin_role(const char role[]){
    return (strcmp(role, "Admin") == 0 || strcmp(role, "admin") == 0);
}// Helper function to check if the user has admin role

int main() {
    int choice;

    while(1) {
        struct user current_user;
        current_user.user_id = -1;

        while(current_user.user_id == -1) {
            int auth_choice;
            char username[50];
            char password[50];

            printf("\n===== USER AUTHENTICATION =====\n");
            printf("1. Register\n");
            printf("2. Login\n");
            printf("0. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &auth_choice);
            getchar();

            switch(auth_choice){
                case 1:
                    create_user();
                    break;
                case 2:
                    printf("Enter Username: ");
                    fgets(username, sizeof(username), stdin);
                    username[strcspn(username, "\n")] = 0;

                    printf("Enter Password: ");
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = 0;

                    current_user = login(username, password);
                    break;
                case 0:
                    printf("Goodbye!\n");
                    return 0;
                default:
                    printf("Invalid choice!\n");
            }
        }

        load_children();

        while(1) {
            int is_admin = is_admin_role(current_user.role);//check if the looged in user is admin or not

            printf("\n===== ORPHANAGE MANAGEMENT SYSTEM =====\n");
            printf("Logged in as: %s (%s)\n", current_user.username, current_user.role);
            printf("1. Child Records\n");
            printf("4. Adoption\n");
            if(is_admin){//only show when the user is admin
                printf("2. Staff Management\n");
                printf("3. Donations\n");
                printf("5. Reports\n");
            }
            printf("7. Logout\n");
            printf("0. Exit\n");
            printf("========================================\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch(choice) {
                case 1: child_menu();
                    break;
                case 2:
                    if(is_admin){
                        printf("Staff Management module coming soon.\n");
                    }else{
                        printf("Access denied! Admin only.\n");
                    }
                    break;
                case 3:
                    if(is_admin){
                        printf("Donations module coming soon.\n");
                    }else{
                        printf("Access denied! Admin only.\n");
                    }
                    break;
                case 4: adoption_menu();
                    break;
                case 5:
                    if(is_admin){
                        printf("Reports module coming soon.\n");
                    }else{
                        printf("Access denied! Admin only.\n");
                    }
                    break;
                case 7:
                    logout(current_user);
                    save_children();
                    current_user.user_id = -1;
                    break;
                case 0:
                    printf("Goodbye!\n");
                    logout(current_user);
                    save_children();
                    return 0;
                default:
                    printf("Invalid choice!\n");
            }

            if(current_user.user_id == -1) {
                break;
            }
        }
    }

    return 0;
}

