#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char book_id[20];
    char book_title[100];
    int is_borrowed;
    char user_id[20];
    char rent_date[20];
    char due_date[20];
} Book;

extern Book library[100];
extern int book_count;

void save_history(char status[], char user_id[], char book_id[], char rent_date[], char due_date[], char return_date[]);

void process_checkout(const char* user_id) {
    char input_book_id[20];
    int book_index = -1;

    printf("書籍IDを入力してください: ");
    scanf("%s", input_book_id);

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].book_id, input_book_id) == 0) {
            book_index = i;
            break;
        }
    }

    if (book_index == -1) {
        printf("該当する書籍IDが存在しません。\n");
        return;
    }

    if (library[book_index].is_borrowed == 1) {
        printf("この書籍は既に貸出中です。\n");
        return;
    }

    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    char rent_date_str[20];
    sprintf(rent_date_str, "%d/%02d/%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);

    time_t future = t + (7 * 24 * 60 * 60);
    struct tm *due = localtime(&future);
    char due_date_str[20];
    sprintf(due_date_str, "%d/%02d/%02d", due->tm_year + 1900, due->tm_mon + 1, due->tm_mday);

    printf("書籍名: %s\n", library[book_index].book_title);
    printf("貸出料金: 500円\n");
    printf("返却期限: %s まで（7泊8日）\n", due_date_str);
    
    int confirm;
    printf("貸出を確定しますか？ (1: はい / 2: いいえ): ");
    scanf("%d", &confirm);

    if (confirm == 1) {
        library[book_index].is_borrowed = 1;
        strcpy(library[book_index].user_id, user_id);
        strcpy(library[book_index].rent_date, rent_date_str);
        strcpy(library[book_index].due_date, due_date_str);
        
        save_history("貸出", (char*)user_id, input_book_id, rent_date_str, due_date_str, "-");
        
        printf("貸出が完了しました。\n");
    } else {
        printf("貸出がキャンセルされました。\n");
    }
}