#include <stdio.h>
#include <string.h>

// 書籍IDが有効かチェック
int is_valid_book_id(const char* book_id) {
    FILE* file = fopen("books.csv", "r");
    if (!file) {
        printf("books.csvを開けませんでした。\n");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char csv_book_id[20];
        sscanf(line, "%[^,]", csv_book_id);
        if (strcmp(csv_book_id, book_id) == 0) {
            fclose(file);
            return 0; // 有効
        }
    }
    fclose(file);
    return -2; // 未登録
}

// ユーザーIDが有効かチェック
int is_valid_user_id(const char* user_id) {
    FILE* file = fopen("users.csv", "r");
    if (!file) {
        printf("users.csvを開けませんでした。\n");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char csv_user_id[20];
        sscanf(line, "%[^,]", csv_user_id);
        if (strcmp(csv_user_id, user_id) == 0) {
            fclose(file);
            return 0; // 有効
        }
    }
    fclose(file);
    return -2; // 未登録
}

// 書籍IDから在庫冊数を取得
int get_book_stock(const char* book_id) {
    FILE* file = fopen("books.csv", "r");
    if (!file) {
        printf("books.csvを開けませんでした。\n");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char csv_book_id[20];
        int stock = 0;
        // 書籍ID,書籍名,貸出料金,在庫冊数,書籍登録日
        // 例：B001,The Great Gatsby,300,5,2024-01-01
        //     csv_book_id = "B001", stock = 5
        sscanf(line, "%[^,],%*[^,],%*[^,],%d", csv_book_id, &stock);
        if (strcmp(csv_book_id, book_id) == 0) {
            fclose(file);
            return stock; // 在庫数を返す
        }
    }
    fclose(file);
    return -2; // 未登録
}
