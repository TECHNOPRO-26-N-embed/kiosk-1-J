#include <stdio.h>
#include <string.h>
#include <time.h>

// 現在日付（貸出日）を取得
void get_rent_date(char date[]) {
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    sprintf(
        date,
        "%04d-%02d-%02d",
        local->tm_year + 1900,
        local->tm_mon + 1,
        local->tm_mday
    );
}

// 返却期限日を取得（7日後）
void get_due_date(char due_date[]) {
    time_t t = time(NULL) + (7 * 24 * 60 * 60);
    struct tm *local = localtime(&t);
    sprintf(
        due_date,
        "%04d-%02d-%02d",
        local->tm_year + 1900,
        local->tm_mon + 1,
        local->tm_mday
    );
}

// 返却期限が明日のユーザーに通知する関数
void notify_due_date(const char* user_id, const char* book_id, const char* due_date) {
    char tomorrow[11];
    time_t t = time(NULL) + (24 * 60 * 60);
    struct tm *local = localtime(&t);

    sprintf(
        tomorrow,
        "%04d-%02d-%02d",
        local->tm_year + 1900,
        local->tm_mon + 1,
        local->tm_mday
    );

    if (strcmp(due_date, tomorrow) == 0) {
        printf("[通知] ユーザーID: %s / 書籍ID: %s は明日が返却期限です（期限: %s）\n", user_id, book_id, due_date);
    }
}
