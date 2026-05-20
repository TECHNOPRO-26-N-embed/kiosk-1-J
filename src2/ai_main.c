#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "ai_return.h"
#include "ai_login.h"
#include "ai_modules.h"

static void setup_console_encoding(void) {
#ifdef _WIN32
    SetConsoleOutputCP(932);
    SetConsoleCP(932);
#endif
    setlocale(LC_ALL, "");
}

void displayMenu() {
    printf("============================\n");
    printf("    AI_図書館セルフ貸出メニュー  \n");
    printf("============================\n");
    printf("1. 書籍貸出\n");
    printf("2. 書籍返却\n");
    printf("3. 在庫照会\n");
    printf("4. ログ参照\n");
    printf("5. 会員管理\n");
    printf("0. ログアウト\n");
    printf("============================\n");
    printf("選択肢を入力してください: ");
}

int main() {
    setup_console_encoding();
    int choice;
    char user_id[32];

     // ===== CSVロード =====
    if (load_users_from_csv("ai_users.csv") != 0) {
        printf("ユーザーCSV読み込み失敗\n");
        return -1;
    }
    
    // ===== ログイン =====
    if (login() != 0) {
    return -1;
    }

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
            {
                char book_id[32];
                char today[16];
                int result;

                printf("【書籍貸出画面】\n");
                printf("書籍IDを入力してください: ");
                scanf("%31s", book_id);

                get_rent_date(today);
                result = checkout_book(user_id, book_id, today);
                if (result == 0) {
                    printf("貸出が完了しました。\n");
                } else {
                    printf("貸出に失敗しました (code=%d)。\n", result);
                }
                break;
            }
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
                printf("書籍IDを入力してください: ");
                char stock_book_id[20];
                scanf("%19s", stock_book_id);

                // 在庫数を取得して表示する処理
                int stock = get_book_stock(stock_book_id);

                // 在庫数の表示
                if (stock >= 0) {
                    printf("在庫数: %d\n", stock);
                } else if (stock == -2) {
                    printf("書籍IDが存在しません。\n");
                } else {
                    printf("在庫情報の取得に失敗しました。\n");
                }
                break;
            case 4:
                printf("【操作ログ画面】\n");
                show_history();
                break;
            case 5:
            {
                printf("【ポイント・会員管理画面】\n");
                char member_user_id[20];
                printf("ユーザーIDを入力してください: ");
                scanf("%19s", member_user_id);

                // ユーザーのポイントを取得して表示する処理
                int current_points = get_user_point(member_user_id);
                if (current_points >= 0) {
                    printf("現在のポイント: %d\n", current_points);
                } else {
                    printf("ユーザーIDが見つかりません。\n");
                }
                break;
            }
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