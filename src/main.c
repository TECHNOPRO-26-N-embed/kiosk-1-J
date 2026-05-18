#include <stdio.h>

void returnBook(){
    char user_id[50];
    char book_id[50];
    char return_date[50];
    int late_fee = 0;

    printf("=== 書籍の返却 ===\n");
    
    printf("ユーザーIDを入力してください: ");
    scanf("%s", user_id);
    printf("書籍IDを入力してください: ");
    scanf("%s", book_id);
    printf("返却日を入力してください (YYYY-MM-DD): ");
    scanf("%s", return_date);
    printf("遅延料金がある場合は入力してください (ない場合は0): ");
    scanf("%d", &late_fee); 
    FILE *fp = fopen("data/return_history.csv", "a");// 返却履歴をCSVファイルに保存

    if (fp == NULL )// ファイルが開けない場合のエラーハンドリング
    {
        printf("CSVファイルを開くことができませんでした。\n");
        return;
    }
    fprintf(fp, "%s,%s,%s,%d\n", user_id, book_id, return_date, late_fee);// CSVファイルに返却情報を書き込む
    fclose(fp);
    printf("書籍の返却が完了しました。\n");
}
void save_history(
    char status[],
    char user_id[],
    char book_id[],
    char rent_date[],
    char due_date[],
    char return_date[]
) {
    // 履歴保存の処理をここに実装
    FILE *file = fopen("history.csv", "a");

    if(file == NULL) {
        printf("履歴ファイルのオープンに失敗しました。\n");
        return;
    }

    fprintf(file, "Status: %s, User ID: %s, Book ID: %s, Rent Date: %s, Due Date: %s, Return Date: %s\n", 
        status, 
        user_id, 
        book_id, 
        rent_date, 
        due_date, 
        return_date);

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

int main() {
    int choice;
    char user_id[10];
    char book_id[10];
    char rent_date[20];
    char due_date[20];
    char return_date[20];


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
                save_history("貸出", "ユーザーID", "書籍ID", "貸出日", "返却予定日", "返却日"); // 例としてユーザーIDと書籍IDを固定値で保存
        } else if(choice == 2) {
                printf("書籍返却が選択されました。\n");
                returnBook(); // 書籍返却処理を呼び出す
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
    
    return 0;
}