#include <stdio.h>
#include <string.h>
#include "globals.h"

int find_book_index(char input_id[]);
void get_date(char date[]);
void get_due_date(char due_date[]);
void save_history(
    char status[],
    char user_id[],
    char book_id[],
    char rent_date[],
    char due_date[],
    char return_date[]
);

void process_checkout(char user_id[]) {
    char book_id[20];
    char rent_date[20];
    char due_date[20];
    int target_index;

    if (book_count <= 0) {
        printf("登録済みの書籍がありません。\n");
        return;
    }

    printf("書籍IDを入力してください: ");
    scanf("%19s", book_id);

    target_index = find_book_index(book_id);
    if (target_index < 0) {
        printf("未登録の書籍IDです。先に書籍ID登録を行ってください。\n");
        return;
    }
    if (is_borrowed[target_index]) {
        printf("この書籍はすでに貸出中です。\n");
        return;
    }

    get_date(rent_date);
    get_due_date(due_date);

    is_borrowed[target_index] = 1;
    strcpy(borrowed_rent_dates[target_index], rent_date);
    strcpy(borrowed_due_dates[target_index], due_date);

    save_history("貸出中", user_id, book_id, rent_date, due_date, "");
    printf("書籍が貸し出されました。\n");
}