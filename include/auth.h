
#define AUTH_FILE "data/users.dat"
struct user{
    int user_id;
    char username[50];
    char password[50];
    char role[20];
    int is_active;
};

struct user login(char username[],char password[]);
void logout(struct user u);
void create_user();
int save_user(struct user u,char filename[]);
struct user load_user(char filename[],char username[]);
void login_display(struct user u);

