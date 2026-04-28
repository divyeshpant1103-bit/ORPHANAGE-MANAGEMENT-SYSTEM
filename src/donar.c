#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"donar.h"

#undef DONAR_FILE
#define DONAR_FILE "data/donar.txt"

void donar_menu()
{
    int choice;
    do
    {
        printf("\n1. To add donor details\n");
        printf("2. To display donor list\n");
        printf("3. To search donor\n");
        printf("4. To update donor details\n");
        printf("5. To delete donor details\n");
        printf("0. Back\n");
        printf("Enter the choice: ");
        scanf("%d",&choice);
        getchar();
        printf("\n");
        switch (choice)
        {
        case 1:
            add_donar();
            break;
        case 2:
            display_donar_list();
            break;
        case 3:
            search_donar();
            break;
        case 4:
            update_donar_details();
            break;
        case 5:
            delete_donar();
            break;
        case 0:
            return ;
        default:
            printf("Invalid input\n");
            break;
        }
    } while(choice != 0);
}

static int count()
{
    FILE *fp;
    char line[300];
    fp = fopen(DONAR_FILE, "r");
    if (fp == NULL)
    {
        fp = fopen(DONAR_FILE, "w");
        if (fp == NULL)
        {
            printf("Error opening file!\n");
            return 0 ;
        }
        fprintf(fp,"%-15s\t%-18s\t%-29s\t%-18s\t%-15s\t%s\n","DONOR ID", "NAME", "TYPE OF DONATION", "CONTACT", "QUANTITY","DONATION DATE" );
        fprintf(fp,"_______________________________________________________________________________________________________________________\n");
        fclose(fp);
        return 0;
    }

    int count=0;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (isdigit((unsigned char)line[0]))
        {
            count++;
        }
    }

    fclose(fp);
    return count;
}

int generate_prev_donar_id()
{
    int donar_count= count();
    char line[300];
    int prev_donar_id=35099;
    int file_id=0;
    FILE *fp;
    fp = fopen(DONAR_FILE, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    if(donar_count==0)
    {
        fclose(fp);
        return 35099;
    }
    while(fgets(line, sizeof(line), fp)!= NULL)
    {
        if (sscanf(line, "%d",&file_id) == 1)
        {
            prev_donar_id = file_id;
        }
    }
    fclose(fp);
    return (prev_donar_id);
}

void add_donar()
{
    int donar_count= count();
    int d,m,y;
    FILE *fp;
    fp = fopen(DONAR_FILE, "a");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return ;
    }

    int i;
    int n;
    printf("Enter the number of donors to input: ");
    scanf("%d",&n);
    if(donar_count==0)
    {
        fprintf(fp,"%-15s\t%-18s\t%-29s\t%-18s\t%-15s\t%s\n","DONOR ID", "NAME", "TYPE OF DONATION", "CONTACT", "QUANTITY","DONATION DATE" );
        fprintf(fp,"_______________________________________________________________________________________________________________________\n");
    }
    int prev_donar_id= generate_prev_donar_id();

    struct donar *s = (struct donar*) malloc( n* sizeof(struct donar));

    for (i=0; i <  n ; i++) 
    {
        printf("\nEnter details of donor %d\n", donar_count+i+1);
        s[i].donar_id = prev_donar_id + i + 1;

        printf("Donor id : %d\n", s[i].donar_id );                                                    
        getchar();                                                                      

        printf("Enter Donor name : ");                                                  
        fgets(s[i].name, sizeof(s[i].name), stdin);
        size_t len = strlen(s[i].name);
        if (len > 0 && s[i].name[len - 1] == '\n')
        {
            s[i].name[len - 1] = '\0';
        }

        printf("Enter Donation type : ");                                                  
        fgets(s[i].donation_type, sizeof(s[i].donation_type), stdin);
        size_t len1 = strlen(s[i].donation_type);
        if (len1 > 0 && s[i].donation_type[len1 - 1] == '\n')
        {
            s[i].donation_type[len1 - 1] = '\0';
        }

        printf("Enter Donor contact: ");                                                
        fgets(s[i].contact, sizeof(s[i].contact), stdin);
        size_t len2 = strlen(s[i].contact);
        if (len2 > 0 && s[i].contact[len2 - 1] == '\n')
        {
            s[i].contact[len2 - 1] = '\0';
        }

        printf("Enter the quantity donated : ");                                    
        scanf("%f",&s[i].quantity);
        getchar();

        printf("Enter Donor donation date (dd mm yyyy): ");                               
        scanf("%d%d%d", &d, &m, &y );

        sprintf(s[i].donation_date,"%02d/%02d/%04d", d, m, y );
        getchar();                                                                      

        fprintf(fp,"%d\t%s\t%s\t%s\t%.2f\t%s\n", s[i].donar_id, s[i].name, s[i].donation_type, s[i].contact, s[i].quantity, s[i].donation_date);
    }
    printf("\nDonor details added successfully!!!\n");
    fclose(fp);
    free(s);
}

void display_donar_list()
{
    printf("\n");
    FILE *fp;
    char line[300];

    struct donar s;
    fp = fopen(DONAR_FILE, "r");
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
        sscanf(line,"%d\t%[^\t]\t%[^\t]\t%[^\t]\t%f\t%[^\n]", &s.donar_id, s.name, s.donation_type, s.contact, &s.quantity, s.donation_date);

    
        printf("%-15d\t%-18s\t%-29s\t%-18s\t%-15.2f\t%s \n", s.donar_id, s.name, s.donation_type, s.contact, s.quantity, s.donation_date);
    }

    fclose(fp);
    printf("\n");
}

void search_donar()
{
    FILE *fp;
    char line[300];
    struct donar s;
    int search_id, file_id, flag=0;
    fp = fopen(DONAR_FILE, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return ;
    }
    printf("Enter the donor id to search: ");
    scanf("%d",&search_id);

    //skip headers
    fgets(line, sizeof(line), fp);
    printf("%s", line);
    fgets(line, sizeof(line), fp);
    printf("%s", line);

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // FIX: Replaced %[\t] with %[^\n]
        sscanf(line,"%d\t%[^\t]\t%[^\t]\t%[^\t]\t%f\t%[^\n]", &file_id, s.name, s.donation_type, s.contact, &s.quantity, s.donation_date);

        if(file_id == search_id)
        {
            printf("%-15d\t%-18s\t%-29s\t%-18s\t%-15.2f\t%s\n", file_id, s.name, s.donation_type, s.contact, s.quantity, s.donation_date);
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("Donor ID not found !!\n");
    }
    fclose(fp);
}

static void change(struct donar *s)
{
    int choice;
    size_t len;

    do
    {
        printf("\nChoose the data that needs to be changed : \n");
        printf("1. Donor name\n");
        printf("2. Donation type\n");
        printf("3. Donor contact\n");
        printf("4. Quantity donated\n");
        printf("5. Donation date\n");
        printf("0. To exit\n");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            char name[20];
            printf("Enter Donor name: ");
            fgets(name, sizeof(name), stdin);
            len = strlen(name);
            if (len > 0 && name[len - 1] == '\n') name[len - 1] = '\0';
            strncpy(s->name, name, sizeof(s->name)-1);
            s->name[sizeof(s->name)-1] = '\0';
            break;
        }
        case 2:
        {
            char donation_type[50];
            printf("Enter Donation type: ");
            fgets(donation_type, sizeof(donation_type), stdin);
            len = strlen(donation_type);
            if (len > 0 && donation_type[len - 1] == '\n') donation_type[len - 1] = '\0';
            strncpy(s->donation_type, donation_type, sizeof(s->donation_type)-1);
            s->donation_type[sizeof(s->donation_type)-1] = '\0';
            break;
        }

        case 3:
        {
            char contact[50];
            printf("Enter Donor contact: ");
            fgets(contact, sizeof(contact), stdin);
            len = strlen(contact);
            if (len > 0 && contact[len - 1] == '\n') contact[len - 1] = '\0';
            strncpy(s->contact, contact, sizeof(s->contact)-1);
            s->contact[sizeof(s->contact)-1] = '\0';
            break;
        }
        case 4:
        {
            float quantity;
            printf("Enter quantity donated: ");
            scanf("%f", &quantity);
            s->quantity = quantity;
            break;
        }
        case 5:
        {
            int d, m, y;
            char new_date[15];
            printf("Enter donation date (dd mm yyyy): ");
            scanf("%d%d%d", &d, &m, &y);
            sprintf(new_date, "%02d/%02d/%04d", d, m, y);
            strncpy(s->donation_date, new_date, sizeof(s->donation_date)-1);
            s->donation_date[sizeof(s->donation_date)-1] = '\0';
            break;
        }
        case 0:
            printf("\nDonor record UPDATED successfully !!\nExiting...\n");
            return;
        }
    } while (choice != 0);
}

void update_donar_details()
{
    FILE *fp, *temp;
    char line[300];
    struct donar s;
    int search_id, file_id;
    int flag = 0;

start:
    printf("\nEnter the id of the Donor to update details: ");
    scanf("%d", &search_id);

    fp = fopen(DONAR_FILE, "r");
    temp = fopen("../data/temp_donar.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fgets(line, sizeof(line), fp);
    fputs(line, temp);
    fgets(line, sizeof(line), fp);
    fputs(line, temp);

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        
        sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%f\t%[^\n]",
               &file_id, s.name, s.donation_type, s.contact, &s.quantity, s.donation_date);

        if (file_id == search_id)
        {
            change(&s);
            fprintf(temp, "%d\t%s\t%s\t%s\t%.2f\t%s\n",
                    file_id, s.name, s.donation_type, s.contact, s.quantity, s.donation_date);
            flag = 1;
        }
        else
        {
            fputs(line, temp);
        }
    }

    if (!flag)
    {
        printf("Donor ID not found !!\n");
        fclose(fp);
        fclose(temp);
        remove("../data/temp_donar.txt");
        goto start;
    }

    fclose(fp);
    fclose(temp);
    remove(DONAR_FILE);
    rename("../data/temp_donar.txt", DONAR_FILE);
}

void delete_donar()
{
    FILE *fp, *temp;
    char line[300];
    int search_id, file_id ;
    int flag=0;

    fp = fopen(DONAR_FILE, "r");
    temp = fopen("../data/temp_donar.txt", "w");
    if (fp == NULL || temp ==NULL)
    {
        printf("Error opening file!\n");
        return ;
    }

    printf("\nEnter the id of the Donor to delete : ");
    scanf("%d",&search_id);
    getchar();

    fgets(line, sizeof(line), fp);
    fputs(line, temp);

    fgets(line, sizeof(line), fp);
    fputs(line, temp);

    while(fgets(line, sizeof(line), fp)!= NULL)
    {
        if (sscanf(line, "%d", &file_id) == 1) 
        {
        
            if(search_id != file_id)
            {
                fputs(line, temp);
            }
            else 
            {
                flag=1; // We found the ID and excluded it from writing to temp!
            }
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    if(flag==0)
    {
        printf("Donor ID not found !!\n");
        remove("../data/temp_donar.txt");
    }
    else 
    {
        remove(DONAR_FILE);
        rename("../data/temp_donar.txt", DONAR_FILE);
        printf("\nDonor details DELETED successfully !!\n");
    }
}