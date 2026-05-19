#include <stdio.h>
#include <string.h>
#include <time.h>
#include "globals.h"

int find_book_index(char input_id[]);

int calculate(char due_date[], char return_date[]) {
    if (return_date[0] == '\0') {
        return 0;
    }
    if (strcmp(due_date, return_date) >= 0) {
        return 0;
    }
    return 500;
}

void save_history(
    char status[],
    char user_id[],
    char book_id[],
    char rent_date[],
    char due_date[],
    char return_date[]
) {
    FILE *file = fopen("history.csv", "a");

    if (file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    int late_fee = calculate(due_date, return_date);
    int target_index = find_book_index(book_id);
    char full_book[150];
    snprintf(full_book, sizeof(full_book), "%s %s %s",book_id, book_names[target_index], book_prices[target_index]);

    fprintf(
        file,
        "貸出状況: %s, ユーザーID: %s, 書籍情報: %s, 借用日: %s, 返却期限: %s, 返却日: %s, 延滞料金: %d\n",
        status,
        user_id,
        full_book,
        rent_date,
        due_date,
        return_date,
        late_fee
    );

    fclose(file);
}

void load_history() {
    FILE *file = fopen("history.csv", "r");
    char line[256];

    if (file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    printf("\n=== 履歴 ===\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void get_date(char date[]) {
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
