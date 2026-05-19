#include <stdio.h>
#include <string.h>
#include <time.h>   

#define MAX_BOOKS 100

int is_borrowed[MAX_BOOKS] = {0};
int book_count = 0;
char registered_book_ids[MAX_BOOKS][20];
char borrowed_rent_dates[MAX_BOOKS][20];
char borrowed_due_dates[MAX_BOOKS][20];

//login.c
void check_user_id(char user_id[]);

//history.c
int calculate(char due_date[], char return_date[]);
void save_history(char status[],char user_id[],char book_id[],char rent_date[],char due_date[],char return_date[]);
void load_history();
void get_date(char date[]);
void get_due_date(char due_date[]);

void process_checkout(char user_id[]);
void process_return(char user_id[]);

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

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
