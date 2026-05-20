#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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