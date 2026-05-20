#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ai_globals.h"


// ai_book.csvから書籍IDリストを読み込む
static void load_book_ids(void) {
    FILE *file = fopen("ai_book.csv", "r");
    if (!file) return;
    char line[100];
    book_count = 0;
    while (fgets(line, sizeof(line), file) && book_count < MAX_BOOKS) {
        // 1行目のカンマ区切り1列目をIDとして格納
        char *token = strtok(line, ",\n");
        if (token) {
            strncpy(registered_book_ids[book_count], token, 19);
            registered_book_ids[book_count][19] = '\0';
            book_count++;
        }
    }
    fclose(file);
}

int find_book_index(char input_id[]) {
    for (int i = 0; i < book_count; i++) {
        if (strcmp(registered_book_ids[i], input_id) == 0) {
            return i;
        }
    }
    return -1;
}

// 入力バッファクリア（長い入力やバッファ残り対策）
static void clear_input_buffer(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

// 入力IDが登録済みか判定
static int is_registered_book_id(const char *input_id) {
    for (int i = 0; i < book_count; i++) {
        if (strcmp(registered_book_ids[i], input_id) == 0) return 1;
    }
    return 0;
}



// 書籍ID入力＆チェック（book.csv参照・ループ再入力・キャンセル可）
int ai_input_book_id(char *book_id, size_t size) {
    load_book_ids(); // 毎回最新のbook.csvをロード
    while (1) {
        printf("\n【書籍ID入力】（キャンセル: 0 を入力）\n> ");
        if (fgets(book_id, (int)size, stdin) == NULL) {
            clear_input_buffer();
            printf("[エラー] 入力エラーです。再度入力してください。\n");
            continue;
        }
        if (strchr(book_id, '\n') == NULL) clear_input_buffer();
        // 改行除去
        size_t len = strlen(book_id);
        if (len > 0 && book_id[len - 1] == '\n') book_id[len - 1] = '\0';
        // キャンセル
        if (strcmp(book_id, "0") == 0) {
            printf("[INFO] メニューに戻ります。\n");
            return -1;
        }
        // 空文字・不正文字チェック
        int valid = 1;
        if (strlen(book_id) == 0) valid = 0;
        for (size_t i = 0; i < strlen(book_id); ++i) {
            if (!isalnum((unsigned char)book_id[i])) valid = 0;
        }
        if (!valid) {
            printf("[エラー] 書籍IDは英数字のみ入力してください（空欄・記号・全角不可）。\n");
            continue;
        }
        // book.csvに登録されているか
        if (!is_registered_book_id(book_id)) {
            printf("[エラー] その書籍IDは登録されていません。\n");
            continue;
        }
        // 合致したら次の処理へ
        printf("[OK] 書籍ID '%s' を受け付けました。\n", book_id);
        return 0;
    }
}
