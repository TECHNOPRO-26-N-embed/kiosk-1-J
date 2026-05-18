#include <stdio.h>
#include <time.h>
void returnBook() {
    char book_id[50];
    int due_year, due_month, due_day;
    int late_days;
    int late_fee = 0;
    printf("\n=== 書籍返却 ===\n");
    printf("書籍IDを入力してください: ");
    scanf("%s", book_id);
    printf("返却予定日を入力してください（例：2026 05 20）: ");
    scanf("%d %d %d", &due_year, &due_month, &due_day);
    time_t now = time(NULL);
    struct tm due_date = {0};
    due_date.tm_year = due_year - 1900;
    due_date.tm_mon = due_month - 1;
    due_date.tm_mday = due_day;
    time_t due_time = mktime(&due_date);
    late_days = (int)((now - due_time) / (60 * 60 * 24));
    if (late_days > 0) {
        late_fee = late_days * 100;
        printf("返却期限を%d日超えています。\n", late_days);
        printf("延滞料金は%d円です。\n", late_fee);
    } else {
        printf("延滞料金はありません。\n");
    }
    printf("書籍ID: %s\n", book_id);
    printf("返却処理が完了しました。\n");
}