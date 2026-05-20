#ifndef USER_H
#define USER_H

#define MAX_USERS 1000

typedef struct {
    char user_id[128];
    int enabled;
} User;

// 外部変数
extern User g_users[MAX_USERS];
extern int g_user_count;

// 関数
int authenticate_user(const char* user_id);
int load_users_from_csv(const char* csv_path);
int login();

#endif
