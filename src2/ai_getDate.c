#include <stdio.h>
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
