#include <stdio.h>
#include <string.h>

// ユーザーのポイントを取得する関数
int get_user_point(const char* user_id) {
    FILE* file = fopen("users.csv", "r");
    if (!file) {
        printf("users.csvを開けませんでした。\n");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char csv_user_id[20];
        int points;
        // ユーザーID,ユーザー名,ポイント
        sscanf(line, "%[^,],%*[^,],%d", csv_user_id, &points);
        if (strcmp(csv_user_id, user_id) == 0) {
            fclose(file);
            return points; // ポイントを返す
        }
    }
    fclose(file);
    return -2; // ユーザー未登録
}

// ユーザーにポイントを追加する関数
int add_user_point(const char* user_id, int points_to_add) {

    // ファイルを読み書きモードで開く
    FILE* file = fopen("users.csv", "r+");
    if (!file) {
        printf("users.csvを開けませんでした。\n");
        return -1;
    }

    char line[256];
    // ファイルの現在位置を保存
    long pos;

    // ファイルを行単位で読みながらユーザーIDを探す
    while ((pos = ftell(file)) >= 0 && fgets(line, sizeof(line), file)) {
        char csv_user_id[20];
        int points;
        // ユーザーID,ユーザー名,ポイント
        sscanf(line, "%[^,],%*[^,],%d", csv_user_id, &points);
        if (strcmp(csv_user_id, user_id) == 0) {
            points += points_to_add;

            // ファイルの現在位置をユーザーIDの行の先頭に戻す
            // 例：ユーザーIDが行の先頭にある場合、posはその行の先頭を指す
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s,%*[^,],%d\n", csv_user_id, points);
            fclose(file);
            return 0; // 成功
        }
    }
    fclose(file);
    return -2; // ユーザー未登録
}