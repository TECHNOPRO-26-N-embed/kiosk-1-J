#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

// 3.在庫照会関数のプロトタイプ
int get_book_stock(const char* book_id);

// 4.履歴表示関数のプロトタイプ
void show_history();

// 5.必要な関数のプロトタイプ
int get_user_point(const char* user_id);
int add_user_point(const char* user_id, int points_to_add);

int main() {
    setlocale(LC_ALL, "");
    int choice;

    printf("ログインしてください。\n");
    // ログイン機能をここに追加

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
                printf("【書籍返却画面】\n");
                printf("書籍IDを入力してください: \n");
                // 書籍ID入力処理
                printf("返却可否を判定中...\n");
                // 返却可否判定処理
                printf("延滞料金を表示します...\n");
                // 延滞料金表示処理
                break;
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
                printf("【ポイント・会員管理画面】\n");
                char user_id[20];
                printf("ユーザーIDを入力してください: ");
                scanf("%19s", user_id);

                // ユーザーのポイントを取得して表示する処理
                int current_points = get_user_point(user_id);
                if (current_points >= 0) {
                    printf("現在のポイント: %d\n", current_points);
                } else {
                    printf("ユーザーIDが見つかりません。\n");
                }
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