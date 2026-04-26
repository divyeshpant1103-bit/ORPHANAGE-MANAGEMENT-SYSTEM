
struct donar
{
    int donar_id;
    char name[20];
    char donation_type[30];
    char contact[15];
    float quantity;
    char donation_date[15];
};

int generate_prev_donar_id();
void add_donar();
void search_donar();
void display_donar_list();
void delete_donar();
void update_donar_details();
void donar_menu();


