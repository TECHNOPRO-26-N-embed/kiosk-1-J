#include <stdio.h>
#include <string.h>
#include "globals.h"

int find_book_index(char input_id[]);
void get_date(char date[]);
void save_history(
    char status[],
    char user_id[],
    char book_id[],
    char rent_date[],
    char due_date[],
    char return_date[]
);

void process_return(char user_id[]) {
    char book_id[20];
    char return_date[20];
    int target_index;

    printf("書籍IDを入力してください: ");
    scanf("%19s", book_id);

    target_index = find_book_index(book_id);
    if (target_index < 0) {
        printf("未登録の書籍IDです。\n");
        return;
    }
    if (!is_borrowed[target_index]) {
        printf("この書籍は貸出中ではありません。\n");
        return;
    }

    get_date(return_date);
    is_borrowed[target_index] = 0;

    printf("書籍名: %s\n", book_names[target_index]);
    printf("価格: %s\n", book_prices[target_index]);

    char full_book[150];
    snprintf(full_book, sizeof(full_book), "%s, %s, (%s)",book_id, book_names[target_index], book_prices[target_index]);
    
    save_history(
        "返却済",
        user_id,
        full_book,
        borrowed_rent_dates[target_index],
        borrowed_due_dates[target_index],
        return_date
    );

    borrowed_rent_dates[target_index][0] = '\0';
    borrowed_due_dates[target_index][0] = '\0';

    printf("書籍が返却されました。\n");
}