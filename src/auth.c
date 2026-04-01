/*
 * auth.c
 * Authentication helpers for the orphanage app. Provides simple
 * user creation, loading, saving and login/logout utilities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/auth.h"
 

static struct user invalid_user(){
    struct user u;
    u.user_id = -1;
    strcpy(u.username, "");
    strcpy(u.password, "");
    strcpy(u.role, "");
    u.is_active = 0;
    return u;
}

/*
 * create_user: Register a new user account and persist it.
 */
void create_user(){
    struct user u;

    printf("Enter UserID: ");
    scanf("%d",&u.user_id);
    getchar();

    printf("Enter Username: ");
    fgets(u.username,50,stdin);
    u.username[strcspn(u.username,"\n")]=0;

    if(strlen(u.username) == 0){
        printf("Username cannot be empty!\n");
        return;
    }

    if(load_user(FILE_NAME, u.username).user_id != -1){
        printf("Username already exists!\n");
        return;
    }

    printf("Enter Password: ");
    fgets(u.password,50,stdin);
    u.password[strcspn(u.password,"\n")]=0;
    
    printf("Enter Role: ");
    printf("1. Admin\n");
    printf("2. Staff\n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch(choice){
        case 1: strcpy(u.role,"Admin");
            break;
        case 2: strcpy(u.role,"Staff");
            break;
        default: printf("Invalid role choice! Defaulting to 'staff'.\n");
            strcpy(u.role,"staff");
    }


    u.is_active=1;
    save_user(u,FILE_NAME);
    printf("User created successfully!\n");
}

void save_user(struct user u,char filename[]){
    /* Append the user record to a binary file. Caller provides filename. */
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(&u, sizeof(struct user), 1, file);
    fclose(file);
    printf("User saved successfully!\n");
}

struct user load_user(char filename[],char username[]){
    /*
     * load_user: Scan the binary user file for a username match and
     * return the stored user. If file is missing or username not
     * found, returns an invalid user with `user_id == -1`.
     */
    struct user u = invalid_user();
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("User file not found.\n");
        return u;
    }

    while (fread(&u, sizeof(struct user), 1, file) == 1) {
        if (strcmp(u.username, username) == 0) {
            fclose(file);
            return u;   
        }
    }

    fclose(file);
    return invalid_user();
}

/*
 * login: Authenticate credentials against stored users and
 * return the authenticated `struct user` (or an invalid user).
 */
struct user login(char username[],char password[]){
    struct user u = load_user(FILE_NAME, username);
    if(u.user_id == -1){
        printf("Login failed! User not found.\n");
        return u;
    }

    if(strcmp(u.password, password) != 0){
        printf("Login failed! Invalid password.\n");
        return invalid_user();
    }

    if(u.is_active == 0){
        printf("Login failed! User is inactive.\n");
        return invalid_user();
    }

    printf("Login successful! Welcome %s (%s).\n", u.username, u.role);
    return u;
}

void logout(struct user u){
    /* Simple logout message; no session storage in this app. */
    if (u.user_id == -1) {
        printf("No active user session.\n");
        return;
    }
    printf("User %s logged out successfully.\n", u.username);
}


