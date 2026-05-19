#include <stdio.h>
#include <string.h>
#include <time.h>   
#include "globals.h"    

int is_borrowed[MAX_BOOKS] = {0};
int book_count = 0;
char registered_book_ids[MAX_BOOKS][20];
char borrowed_rent_dates[MAX_BOOKS][20];
char borrowed_due_dates[MAX_BOOKS][20];

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

//login.c
void check_user_id(char user_id[]);

//findBookId.c
int find_book_index(char input_id[]);
void book_id_registration();

//checkout.c
void process_checkout(char user_id[]);

//returnBook.c
void process_return(char user_id[]);

//history.c
int calculate(char due_date[], char return_date[]);
void save_history(char status[],char user_id[],char book_id[],char rent_date[],char due_date[],char return_date[]);
void load_history();
void get_date(char date[]);
void get_due_date(char due_date[]);


int main() {
    int choice;
    char user_id[10];

    while (1){
        check_user_id(user_id);

    while (1){
        printf("\n==============================\n");
        printf("    図書館セルフ貸出メニュー\n");
        printf("==============================\n");
        printf("1. 書籍貸出\n");
        printf("2. 書籍返却\n");
        printf("3. 履歴\n");
        printf("4. 書籍ID登録\n");
        printf("0. ログアウト\n");
        printf("------------------------------\n");
        printf("選択してください (0-4): ");
        if (scanf("%d", &choice) != 1) {
            printf("無効な入力です。もう一度入力してください。\n");
            clear_input_buffer();
            continue;
        }

        if(choice == 1) {
                printf("書籍貸出が選択されました。\n");
                process_checkout(user_id);

        } else if(choice == 2) {
                printf("書籍返却が選択されました。\n");
                process_return(user_id);

        } else if(choice == 3) {
                printf("履歴が選択されました。\n");
                load_history();

        } else if(choice == 4) {
            book_id_registration();

        } else if(choice == 0) {
                printf("ログアウトします。\n");
                break;
        } else {
                printf("無効な選択です。もう一度入力してください。\n");
        }
    }
}
    return 0;
}
