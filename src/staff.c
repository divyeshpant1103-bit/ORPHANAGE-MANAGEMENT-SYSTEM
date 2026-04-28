#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"staff.h"
#include"audit.h"


void staff_menu()
{
        int choice;
        do
        {
                printf("1. To add Staff details\n");
                printf("2. To display Staff list\n");
                printf("3. To search Staff\n");
                printf("4. To update Staff details\n");
                printf("5. To delete Staff details\n");
                printf("0. Back\n\n");
                printf("Enter the choice  ");
                scanf("%d",&choice);
                getchar();
                printf("\n");
                switch (choice)
                {
                case 1:
                        add_staff();
                        break;
                case 2:
                        display_staff_list();
                        break;
                case 3:
                        search_staff();
                        break;
                case 4:
                        update_staff_details();
                        break;
                case 5:
                        delete_staff();
                        break;
                case 0:
                        return ;
                default:
                        printf("\nInvalid input!!\n");
                        break;
                }
        } while(choice != 0);
}
static int count()
{
        FILE *fp;
        char line[300];
        fp = fopen(FILE_NAME, "r");
        if (fp == NULL)
        {
                fp = fopen(FILE_NAME, "w");
                if (fp == NULL)
                {
                        printf("Error opening file!\n");
                        return 0 ;
                }
                fprintf(fp,"%-15s\t%-18s\t%-18s\t%-18s\t%-15s\t%-15s\t%s\n","STAFF ID", "NAME", "ROLE", "CONTACT","JOINING DATE", "SALARY", "FEEDBACK" );
                fprintf(fp,"________________________________________________________________________________________________________________________________\n");
                fclose(fp);
                return 0;
        }

        int count=0;
        while (fgets(line, sizeof(line), fp) != NULL)
        {
                int id;
                if(sscanf(line, "%d", &id) == 1)
                {
                    count++;
                }
        }

        fclose(fp);
        return count;
}

int generate_prev_staff_id()
{
        int staff_count= count();
        char line[300];
        int prev_staff_id=25099;
        int file_id=0;
        FILE *fp;
        fp = fopen(FILE_NAME, "r");
        if (fp == NULL)
        {
                printf("Error opening file!\n");
                return 0;
        }
        if(staff_count==0)
        {
                fclose(fp);
                return 25099;
        }
        while(fgets(line, sizeof(line), fp)!= NULL)
        {
                if (sscanf(line, "%d",&file_id) == 1)
                {
                        prev_staff_id = file_id;
                }
        }
        fclose(fp);
        return (prev_staff_id);
}

void add_staff()
{
        int staff_count= count();
        int d,m,y;
        FILE *fp;
        fp = fopen(FILE_NAME, "a");
        if (fp == NULL)
        {
                printf("Error opening file!\n");
                return ;
        }

        int i;
        int n;
        printf("Enter the number of staff to input : ");
        scanf("%d",&n);
        getchar();
        if(staff_count==0)
        {
                fprintf(fp,"%-15s\t%-18s\t%-18s\t%-18s\t%-15s\t%-15s\t%s\n","STAFF ID", "NAME", "ROLE", "CONTACT","JOINING DATE", "SALARY", "FEEDBACK" );
                fprintf(fp,"________________________________________________________________________________________________________________________________\n");
        }
        int prev_staff_id= generate_prev_staff_id();

        struct staff *s = (struct staff*) malloc( n* sizeof(struct staff));
        if(s == NULL)
        {
                printf("Memory allocation failed!\n");
                fclose(fp);
                return;
        }
        for (i=0; i <  n ; i++) // input staff details
        {
                printf("Enter details of staff %d\n", staff_count+i+1);
                s[i].staff_id = prev_staff_id + i + 1;

                printf("Staff id : %d\n", s[i].staff_id );                                                    //from generated id
                                                                               
                printf("Enter staff name : ");                                                  //name
                fgets(s[i].name, sizeof(s[i].name), stdin);
                size_t len = strlen(s[i].name);
                if (len > 0 && s[i].name[len - 1] == '\n')
                {
                        s[i].name[len - 1] = '\0';
                }

                printf("Enter staff role : ");                                                  //role
                fgets(s[i].role, sizeof(s[i].role), stdin);
                size_t len1 = strlen(s[i].role);
                if (len1 > 0 && s[i].role[len1 - 1] == '\n')
                {
                        s[i].role[len1 - 1] = '\0';
                }

                printf("Enter staff contact: ");                                                //contact
                fgets(s[i].contact, sizeof(s[i].contact), stdin);
                size_t len2 = strlen(s[i].contact);
                if (len2 > 0 && s[i].contact[len2 - 1] == '\n')
                {
                        s[i].contact[len2 - 1] = '\0';
                }

                printf("Enter staff joining date (dd mm yyyy) ");                               //joining date
                scanf("%d%d%d", &d, &m, &y );


                sprintf(s[i].joining_date,"%02d/%02d/%04d", d, m, y );

                printf("Enter the salary of the staff : ");                                    // salary
                scanf("%d",&s[i].salary);

                getchar();                                                                     //empty buffer
                printf("Enter staff feedback : ");                                              //feedback
                fgets(s[i].feedback, sizeof(s[i].feedback), stdin);
                size_t len3 = strlen(s[i].feedback);
                if (len3 > 0 && s[i].feedback[len3 - 1] == '\n')
                {
                        s[i].feedback[len3 - 1] = '\0';
                }

                fprintf(fp,"%d\t%s\t%s\t%s\t%s\t%d\t%s\n", s[i].staff_id, s[i].name, s[i].role, s[i].contact, s[i].joining_date,  s[i].salary, s[i].feedback);
        }
        printf("\nStaff details added successfully!!!");
        audit("Added staff record");
        fclose(fp);
        free(s);
}

void display_staff_list()
{
        printf("\n");
        FILE *fp;
        char line[300];
        struct staff s;
        fp = fopen(FILE_NAME, "r");
        if (fp == NULL)
        {
                printf("Error opening file!\n");
                return ;
        }

        fgets(line, sizeof(line), fp);
        puts(line);

        fgets(line, sizeof(line), fp);
        puts(line);

        while (fgets(line, sizeof(line), fp) != NULL)
        {
                sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\n]",&s.staff_id, s.name, s.role, s.contact, s.joining_date, &s.salary, s.feedback);
                printf("%-15d\t%-18s\t%-18s\t%-18s\t%-15s\t%-15d\t%s\n", s.staff_id, s.name, s.role, s.contact, s.joining_date,  s.salary, s.feedback);
        }
        fclose(fp);
        printf("\n");
}

void search_staff()
{
        FILE *fp;
        char line[300];
        struct staff s;
        int search_id, file_id, flag=0;
        fp = fopen(FILE_NAME, "r");
        if (fp == NULL)
        {
                printf("Error opening file!\n");
                return ;
        }
        printf("Enter the staff id to search : ");
        scanf("%d",&search_id);

        //skip headers
        fgets(line, sizeof(line), fp);
        printf("%s\n", line);
        fgets(line, sizeof(line), fp);
        printf("%s\n", line);

        while (fgets(line, sizeof(line), fp) != NULL)
        {
                sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\n]",&file_id, s.name, s.role, s.contact, s.joining_date, &s.salary, s.feedback);

                if(file_id == search_id)
                {
                        printf("%-15d\t%-18s\t%-18s\t%-18s\t%-15s\t%-15d\t%s\n", file_id, s.name, s.role, s.contact, s.joining_date,  s.salary, s.feedback);
                        flag=1;
                        break;
                }
        }
        if(flag==0)
        {
                printf("Staff ID not found !!");
        }

        fclose(fp);
}


void change(struct staff *s)
{
        int choise;
        do
        {

                printf("\nChoose the data that needs to be changed : \n");
                printf("1. Staff name : \n");                                                   //name
                printf("2. Staff role : \n");                                                   //role
                printf("3. Staff contact: \n");                                                 //contact
                printf("4. Staff joining date : \n");                               //joining date
                printf("5. Salary of the staff : \n");
                printf("6. Staff feedback : \n");
                printf("0. To exit : \n");

                size_t len;
                scanf("%d",&choise);
                getchar();
                // printf("Entered ");
                switch(choise)
                {
                case 1: {                                                       //change name
                        char name[20];

                        printf("Enter staff name : ");                                                  //name
                        fgets(name, sizeof(name), stdin);
                        len = strlen(name);
                        if (len > 0 && name[len - 1] == '\n')
                        {
                                name[len - 1] = '\0';
                        }
                        strncpy(s->name, name, sizeof(s->name)-1);
                        s->name[sizeof(s->name)-1] = '\0';  // ensure null termination
                        break;
                }
                case 2: {                                                       //change name
                        char role[50];

                        printf("Enter staff role : ");                                                  //role
                        fgets(role, sizeof(role), stdin);

                        len = strlen(role);
                        if (len > 0 && role[len - 1] == '\n')
                        {
                                role[len - 1] = '\0';
                        }
                        strncpy(s->role, role, sizeof(s->role)-1);
                        s->role[sizeof(s->role)-1] = '\0';
                        break;
                }
                case 3: {                                                       //change name
                        char contact[50];

                        printf("Enter staff contact : ");                                                   //role
                        fgets(contact, sizeof(contact), stdin);

                        len = strlen(contact);
                        if (len > 0 && contact[len - 1] == '\n')
                        {
                                contact[len - 1] = '\0';
                        }
                        strncpy(s->contact, contact, sizeof(s->contact)-1);
                        s->contact[sizeof(s->contact)-1] = '\0';


                        break;
                }
                case 4: {                                                       //change name
                        int d,m,y;
                        char new_date[15];

                        printf("Enter staff date of joining (dd mm yyyy): ");                            //joining date
                        scanf("%d%d%d", &d, &m, &y );
                        sprintf(new_date,"%02d/%02d/%04d", d, m, y );

                        strncpy(s->joining_date, new_date, sizeof(s->joining_date)-1);
                        s->joining_date[sizeof(s->joining_date)-1] = '\0';

                        break;
                }

                case 5: {                                                       //change name
                        int salary;


                        printf("Enter the salary of the staff : ");                                    // salary
                        scanf("%d",&salary);

                        s->salary = salary;
                        break;
                }

                case 6: {                                                       //change feedback
                        char feedback[40];

                        printf("Enter staff feedback : ");                                                  //feedback
                        fgets(feedback, sizeof(feedback), stdin);
                        len = strlen(feedback);
                        if (len > 0 && feedback[len - 1] == '\n')
                        {
                                feedback[len - 1] = '\0';
                        }
                        strncpy(s->feedback, feedback, sizeof(s->feedback)-1);
                        s->feedback[sizeof(s->feedback)-1] = '\0';
                        break;
                }
                case 0:
                        printf("\nStaff record UPDATED successfully !!");
                        printf("\nExiting......\n");
                        return;
                        break;


                }
        } while(choise !=0);
}
void update_staff_details()
{
        FILE *fp, *temp;
        char line[300];
        struct staff s;
        int search_id, file_id;
        int flag=0;
start:

        printf("\nEnter the id of the satff to update details : ");
        scanf("%d",&search_id);

        fp = fopen(FILE_NAME, "r");
        temp = fopen("temp.txt", "w");
        if (fp == NULL || temp ==NULL)
        {
                printf("Error opening file!\n");
                return ;
        }

        fgets(line, sizeof(line), fp);
        fputs(line, temp);

        fgets(line, sizeof(line), fp);
        fputs(line, temp);

        while (fgets(line, sizeof(line), fp) != NULL)
        {
                // Extract staff ID (first column)
                sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\n]",&file_id, s.name, s.role, s.contact, s.joining_date, &s.salary, s.feedback);
                if (search_id== file_id)
                {
                        change(&s);
                        fprintf(temp,"%d\t%s\t%s\t%s\t%s\t%d\t%s\n", file_id, s.name, s.role, s.contact, s.joining_date, s.salary, s.feedback);
                        flag=1;

                }
                else
                {
                        fputs(line, temp);
                }
        }
        if(flag==0)
        {
                printf("Staff ID not found !!\n");
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                goto start;
        }

        fclose(fp);
        fclose(temp);
        remove(FILE_NAME);
        rename("temp.txt",FILE_NAME);



}
void delete_staff()
{
        FILE *fp, *temp;
        char line[300];
        struct staff s;
        int search_id, file_id ;
        int flag=0;
        fp = fopen(FILE_NAME, "r");
        temp = fopen("temp.txt", "w");
        if (fp == NULL || temp ==NULL)
        {
                printf("Error opening file!\n");
                return ;
        }

        printf("Enter the id of the staff to delete : ");
        scanf("%d",&search_id);
        getchar();

        fgets(line, sizeof(line), fp);
        fputs(line, temp);

        fgets(line, sizeof(line), fp);
        fputs(line, temp);

        while(fgets(line, sizeof(line), fp)!= NULL)
        {
                sscanf(line, "%d ", &file_id );
                if(search_id == file_id)
                {
                        flag=1;
                        continue;
                        
                }
                fputs(line, temp);

        }
        if(flag==0) 
        {
                printf("Staff ID not found !!");
        }
        else
                printf("\nStaff details DELETED successfully !!\n");
                audit("Deleted staff record");
        fclose(fp);
        fclose(temp);
        remove(FILE_NAME);
        rename("temp.txt",FILE_NAME);
}
