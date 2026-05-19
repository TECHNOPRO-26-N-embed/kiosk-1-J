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

void load_book_ids() {
    FILE *file = fopen("book.csv", "r");
    if (file == NULL) {
        return;
    }

    char line[100];
    char name[50]  = "";
    char price[20] = "";
    while (fgets(line, sizeof(line), file) != NULL && book_count < MAX_BOOKS) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        if (token != NULL && find_book_index(token) < 0) {
            strcpy(registered_book_ids[book_count], token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(name, token);
            }
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(price, token);
            }
            is_borrowed[book_count] = 0;
            borrowed_rent_dates[book_count][0] = '\0';
            borrowed_due_dates[book_count][0] = '\0';
            strcpy(book_names[book_count], name);
            strcpy(book_prices[book_count], price);
            book_count++;
        }
    }
    fclose(file);
}