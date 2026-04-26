
#define DATA_MANAGEMENT_H

struct record {
    int record_id;
    char record_type[10];   /* child / staff / donor */
    char name[100];
    char action[10];        /* update / delete */
};

void add_record();
void display_records();
void data_management_menu();


