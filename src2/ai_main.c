#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ai_return.h"

void get_rent_date(char date[]);

void displayMenu() {
    printf("============================\n");
    printf("    AI_図書館セルフ貸出メニュー  \n");
    printf("============================\n");
    printf("1. 書籍貸出\n");
    printf("2. 書籍返却\n");
    printf("3. 在庫照会\n");
    printf("4. ログ参照\n");
    printf("0. ログアウト\n");
    printf("============================\n");
    printf("選択肢を入力してください: ");
}

int main() {
    setlocale(LC_ALL, "");
    int choice;
    char user_id[32];

    printf("ログインしてください。\n");
    printf("ユーザーIDを入力してください: ");
    scanf("%31s", user_id);

    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("無効な入力です。数字を入力してください。\n");
            // 入力バッファをクリア
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("【書籍貸出画面】\n");
                printf("書籍IDを入力してください: \n");
                // 書籍ID入力処理
                printf("貸出可否を判定中...\n");
                // 貸出可否判定処理
                printf("料金計算と支払いを行います...\n");
                // 料金計算・支払い処理
                printf("貸出を確定し、CSVに保存しました。\n");
                break;
            case 2:
            {
                char book_id[32];
                char today[16];
                int late_fee = 0;
                int result;

                printf("【書籍返却画面】\n");
                printf("書籍IDを入力してください: ");
                scanf("%31s", book_id);

                get_rent_date(today);
                result = ai_return_book("history.csv", user_id, book_id, today, &late_fee);

                if (result == AI_RETURN_OK) {
                    printf("返却が完了しました。\n");
                    printf("延滞料金: %d円\n", late_fee);
                } else if (result == AI_RETURN_ERR_USER_MISMATCH) {
                    printf("返却不可: 貸出した本人のみ返却できます。\n");
                } else if (result == AI_RETURN_ERR_NOT_FOUND) {
                    printf("返却不可: 貸出中の対象書籍が見つかりません。\n");
                } else if (result == AI_RETURN_ERR_DATE) {
                    printf("返却不可: 日付データが不正です。\n");
                } else {
                    printf("返却処理に失敗しました (code=%d)。\n", result);
                }
                break;
            }
            case 3:
                printf("【在庫照会画面】\n");
                printf("書籍IDを入力してください: \n");
                // 書籍ID入力処理
                printf("在庫数を表示します...\n");
                // 在庫数表示処理
                break;
            case 4:
                printf("【操作ログ画面】\n");
                printf("ログ一覧を表示します...\n");
                // ログ一覧表示処理
                break;
            case 0:
                printf("ログアウトします...\n");
                // ログアウト処理
                exit(0);
            default:
                printf("無効な選択肢です。もう一度試してください。\n");
        }

        printf("メインメニューに戻ります...\n");
    }

    return 0;
}