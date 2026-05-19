#include <stdio.h>
#include <string.h>

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
        scanf("%9s", user_id);

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
