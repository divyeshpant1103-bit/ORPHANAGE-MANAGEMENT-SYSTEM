

#define FILE_NAME "data/staff.txt"
struct staff
{
    int staff_id;
    char name[20];
    char role[20];
    char contact[15];
    char joining_date[15];
    int salary;
    char feedback[40];
};
int generate_prev_staff_id();
void add_staff();
void search_staff();
void display_staff_list();
void delete_staff();
void update_staff_details();
void staff_menu();

