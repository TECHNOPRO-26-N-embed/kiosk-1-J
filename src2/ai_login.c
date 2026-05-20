#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"ai_login.h"

#define USERS_CSV "users.csv"
#define LINE_BUF_SIZE 256


User g_users[MAX_USERS];   
int g_user_count = 0;    

int authenticate_user(const char* user_id)
{
    FILE *fp;
    char line[LINE_BUF_SIZE];

    // 1. 引数チェック
    if (user_id == NULL || strlen(user_id) == 0) {
        return -1;
    }

    // CSVオープン
    fp = fopen(USERS_CSV, "r");
    if (fp == NULL) {
        return -6;
    }

    // 2. users.csv検索
    while (fgets(line, sizeof(line), fp) != NULL) {
        char csv_user_id[128];
        int enabled;

        // "user_id,enabled" 形式を解析
        if (sscanf(line, "%127[^,],%d", csv_user_id, &enabled) != 2) {
            continue;  // フォーマット異常行はスキップ
        }

        // user_id 一致チェック
        if (strcmp(user_id, csv_user_id) == 0) {

            // 3. 利用可否確認
            fclose(fp);

            if (enabled == 1) {
                return 0;   // 認証成功
            } else {
                return -1;  // 利用不可は不正扱い
            }
        }
    }

    fclose(fp);

    // ユーザー未登録
    return -2;
}


int load_users_from_csv(const char* csv_path)
{
    FILE *fp;
    char line[LINE_BUF_SIZE];

    // 引数チェック
    if (csv_path == NULL) {
        return -6;
    }

    fp = fopen(csv_path, "r");
    if (fp == NULL) {
        return -6;
    }

    g_user_count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char user_id[128];
        int enabled;

        // CSV解析
        if (sscanf(line, "%127[^,],%d", user_id, &enabled) != 2) {
            fclose(fp);
            return -6;  // フォーマット不正
        }

        // 改行削除
        user_id[strcspn(user_id, "\r\n")] = '\0';

        // 配列に格納
        if (g_user_count >= MAX_USERS) {
            fclose(fp);
            return -6;  // 上限超過
        }

        strcpy(g_users[g_user_count].user_id, user_id);
        g_users[g_user_count].enabled = enabled;
        g_user_count++;
    }

    fclose(fp);

    return 0; // 成功
}

int login(){
char user_id[128];
    int result;
    while (1) {
        printf("ユーザーID:\n");
        scanf("%s", user_id);
        while (getchar() != '\n');

        result = authenticate_user(user_id);

        if (result == 0) {
            printf("ログイン成功\n");
            return 0; 
        } else if (result == -1) {
            printf("無効ユーザーです\n");
        } else if (result == -2) {
            printf("未登録ユーザーです\n");
        } else {
            printf("エラーが発生しました\n");
        }
    }
}