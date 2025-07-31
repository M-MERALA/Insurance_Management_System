#ifndef AUTH_H
#define AUTH_H

#define MAX_USERS 100
#define USERNAME_LEN 50
#define PASSWORD_LEN 50

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int role; // 1=customer, 2=agent, 3=admin
} User;

int login();
void register_user();
int is_admin(const char *username);

#endif