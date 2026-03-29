#ifndef ADOPT_H
#define ADOPT_H

struct adoption{
    int adoption_id;
    int child_id;
    char adopter_name[100];
    int adopter_age;
    char adopter_contact[15];
    char adopter_address[150];
    char adopter_occupation[50];
    float adopter_income;
    char marital_status[20];
    char application_date[30];
    char approval_date[30];
    char status[15];
};

void adoption_menu();
void adoption_add();
void adoption_display();
void adoption_search();
void adoption_update();
void adoption_delete();
void adoption_approve();

void save_adopter();
void load_adopter();

#endif