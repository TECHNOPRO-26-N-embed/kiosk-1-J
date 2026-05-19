#include <stdio.h>
#include <string.h>
#include "globals.h"


int find_book_index(char input_id[]) {
    for (int i = 0; i < book_count; i++) {
        if (strcmp(registered_book_ids[i], input_id) == 0) {
            return i;
        }
    }
    return -1;
}

void book_id_registration() {
    char input_id[20];

    if (book_count >= MAX_BOOKS) {
        printf("これ以上書籍を登録できません。\n");
        return;
    }

    printf("書籍IDを入力してください: ");
    scanf("%19s", input_id);

    if (find_book_index(input_id) >= 0) {
        printf("書籍ID %s は既に登録されています。\n", input_id);
        return;
    }

    strcpy(registered_book_ids[book_count], input_id);
    is_borrowed[book_count] = 0;
    borrowed_rent_dates[book_count][0] = '\0';
    borrowed_due_dates[book_count][0] = '\0';
    book_count++;
    printf("新規書籍ID登録しました。\n");
}