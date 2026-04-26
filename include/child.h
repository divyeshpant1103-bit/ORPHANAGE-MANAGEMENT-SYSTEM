
struct Orphan{
    int child_id;
    char child_name[100];
    char child_gender[50];
    int child_age;
    char child_BG[20];
    char education[100];
    char health_status[80];
    char medical_report[100];
    char date_of_admission[30];
    char status[20];
};
void child_menu();
void child_add();
void child_display();
void child_update();
void child_search();
void child_delete();
int update_child_Status(int child_id, const char *new_status);
int generate_child_id();
void save_children();
void load_children();
