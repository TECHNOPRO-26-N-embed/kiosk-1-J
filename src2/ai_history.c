#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "globals.h"

// ユーザーIDと書籍IDの整合性を確認する関数
int check_user_id_for_return(const char* user_id, const char* book_id) {
    FILE* file = fopen("transactions.csv", "r");
    if (!file) {
        printf("エラー: 取引履歴ファイルを開けませんでした。\n");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char transaction_status[20], file_user_id[20], file_book_id[20];
        // CSVフォーマットに基づいてデータを読み取る
        //例：A,B,C -> transaction_status = "A", file_user_id = "B", file_book_id = "C"
        sscanf(line, "%[^,],%[^,],%[^,]", transaction_status, file_user_id, file_book_id);

        if (strcmp(file_book_id, book_id) == 0) {
            if (strcmp(file_user_id, user_id) == 0) {
                fclose(file);
                return 0; // ユーザーIDが一致
            } else {
                fclose(file);
                return -2; // ユーザーIDが一致しない
            }
        }
    }

    fclose(file);
    return -3; // 書籍IDが見つからない
}

//貸出日を取得する関数
void get_date(char date[]);

//返却期限日を取得する関数
void get_due_date(char due_date[]);


// 履歴を保存する関数
void save_history(const char* status, const char* user_id, const char* book_id, const char* rent_date, const char* due_date, const char* return_date) {
    FILE *file = fopen("history.csv", "a");
    if (file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    // CSV形式で履歴を保存
    fprintf(
        file,
        "%s,%s,%s,%s,%s,%s\n",
        status,
        user_id,
        book_id,
        rent_date,
        due_date,
        return_date
    );
    fclose(file);
}

// 履歴を表示する関数
void show_history() {
    FILE *file = fopen("history.csv", "r");
    char line[256];
    if (file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    // 履歴を表示
    printf("\n=== 履歴 ===\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

