#include <stdio.h>
#include <string.h>
#include <time.h>   

char user[][3][50] = {
    {"B0101", "ファム チュンクオン","090-1111-2222"},
    {"B0102", "高木 歩夢","090-2222-3333"},
    {"B0103", "瀬戸 雅也","090-3333-4444"},
    {"B0104", "張 芸超","090-4444-5555"},
    {"B0105", "キム ミンギュ","090-5555-6666"}
};

void check_user_id(char user_id[]) {
    //ユーザーID確認画面
    while (1){
        printf("ユーザーIDを入力してください\n");
        //ユーザーID取得
        scanf("%s",user_id);

        for(int i = 0; i < 5; i++){
            if(strcmp(user_id, user[i][0]) == 0){
                printf("ユーザーIDが確認されました。ようこそ、%sさん！\n", user[i][1]);
                return ;
            }
        }
        printf("ユーザーIDが見つかりませんでした。もう一度入力してください。\n");
        strcpy(user_id, ""); // ユーザーIDを空にして再入力を促す
    }
}

int calculate(char due_date[], char return_date[]) {
    // 返却予定日と返却日の差を計算する処理をここに実装
    if(strcmp(due_date, return_date) >= 0) {
        return 0; // 期限内
    } else {
        return 500; // 遅延
    }
}

void save_history(
    char status[],
    char user_id[],
    char book_id[],
    char rent_date[],//貸出日
    char due_date[],//返却予定日
    char return_date[]//返却日
) {
    // 履歴保存の処理をここに実装
    FILE *file = fopen("history.csv", "a");

    if(file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    int late_fee = calculate(due_date, return_date);

    fprintf(file, "Status: %s, User ID: %s, Book ID: %s, Rent Date: %s, Due Date: %s, Return Date: %s\n", 
        status, 
        user_id, 
        book_id, 
        rent_date, 
        due_date, 
        return_date,
        late_fee);

    fclose(file);
}

void load_history() {
    // 履歴読み込みの処理をここに実装
    FILE *file = fopen("history.csv", "r");
    char line[256];

    if(file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    printf("\n=== 履歴 ===\n");
    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void get_date(char date[]) {
    // 日付を取得する処理をここに実装
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    sprintf(date, "%04d-%02d-%02d", 
        local->tm_year + 1900, 
        local->tm_mon + 1, 
        local->tm_mday);
}

void get_due_date(char due_date[]) {
    // 返却予定日を取得する処理をここに実装
    time_t t = time(NULL);
    struct tm *due_date_tm = localtime(&t);
    sprintf(due_date, "%04d-%02d-%02d", 
        due_date_tm->tm_year + 1900, 
        due_date_tm->tm_mon + 1, 
        due_date_tm->tm_mday + 7); // 例として7日後を返却予定日に設定
}


int main() {
    int choice;
    char user_id[10];
    char book_id[10];
    char rent_date[20];
    char due_date[20];
    char return_date[20];

    while (1){
        check_user_id(user_id);

    while (1){
        printf("\n==============================\n");
        printf("    図書館セルフ貸出メニュー\n");
        printf("==============================\n");
        printf("1. 書籍貸出\n");
        printf("2. 書籍返却\n");
        printf("3. 履歴\n");
        printf("0. ログアウト\n");
        printf("------------------------------\n");
        printf("選択してください (0-3): ");
        scanf("%d", &choice);

        if(choice == 1) {
                printf("書籍貸出が選択されました。\n");
                get_date(rent_date);
                get_due_date(due_date);
                save_history(
                    "貸出中", 
                    user_id, 
                    book_id, 
                    rent_date, 
                    due_date, 
                    ""); 
                printf("書籍が貸し出されました。\n");

        } else if(choice == 2) {
                printf("書籍返却が選択されました。\n");
                get_date(return_date);
                save_history(
                    "返却済", 
                    user_id, 
                    book_id, 
                    rent_date, 
                    due_date, 
                    return_date);
                printf("書籍が返却されました。\n");

        } else if(choice == 3) {
                printf("履歴が選択されました。\n");
                load_history();

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