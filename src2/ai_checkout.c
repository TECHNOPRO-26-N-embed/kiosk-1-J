#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "ai_globals.h"

int is_valid_book_id(const char* book_id);
int get_book_stock(const char* book_id);
int can_user_borrow_book(const char* user_id, const char* book_id);
int calculate_rental_fee(const char* book_id);
int save_checkout_log(const char* user_id, const char* book_id, const char* date, const char* action);
int find_book_index(char input_id[]);

int can_user_borrow_book(const char* user_id, const char* book_id) {
    if (user_id == NULL || user_id[0] == '\0' || book_id == NULL || book_id[0] == '\0') {
        return -1;
    }
    if (is_valid_book_id(book_id) != 0) {
        return -2;
    }
    if (get_book_stock(book_id) <= 0) {
        return -3;
    }
    return 0;
}

int calculate_rental_fee(const char* book_id) {
    FILE* file = fopen("ai_books.csv", "r");
    if (!file) {
        return -6;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char csv_book_id[20];
        char price_str[20];
        if (sscanf(line, "%19[^,],%*[^,],%19[^,]", csv_book_id, price_str) == 2) {
            if (strcmp(csv_book_id, book_id) == 0) {
                fclose(file);
                return atoi(price_str);
            }
        }
    }

    fclose(file);
    return -2;
}

int save_checkout_log(const char* user_id, const char* book_id, const char* date, const char* action) {
    FILE* file = fopen("ai_history.csv", "a");
    if (!file) {
        return -6;
    }
    fprintf(file, "%s,%s,%s,%s\n", action, user_id, book_id, date);
    fclose(file);
    return 0;
}

int checkout_book(const char* user_id, const char* book_id, const char* date) {
    if (user_id == NULL || user_id[0] == '\0' || book_id == NULL || book_id[0] == '\0' || date == NULL || date[0] == '\0') {
        print_error("引数不正エラーが発生しました。");
        return -1;
    }

    int v_res = is_valid_book_id(book_id);
    if (v_res != 0) {
        print_error("未登録の書籍IDです。処理を中断します。");
        return -2;
    }

    int c_res = can_user_borrow_book(user_id, book_id);
    if (c_res == -3) {
        print_error("在庫不足のため、貸出できません。");
        return -3;
    } else if (c_res != 0) {
        print_error("貸出可否判定でエラーが発生しました。");
        return c_res;
    }

    int fee = calculate_rental_fee(book_id);
    if (fee < 0) {
        print_error("料金計算に失敗しました。");
        return fee;
    }

    struct tm tm_date = {0};
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) {
        if (sscanf(date, "%d/%d/%d", &year, &month, &day) != 3) {
            print_error("日付形式が不正です。");
            return -7;
        }
    }
    
    tm_date.tm_year = year - 1900;
    tm_date.tm_mon = month - 1;
    tm_date.tm_mday = day;
    tm_date.tm_isdst = -1;

    time_t t = mktime(&tm_date);
    if (t == (time_t)-1) {
        print_error("日付処理に失敗しました。");
        return -7;
    }

    time_t future = t + (7 * 24 * 60 * 60);
    struct tm *due = localtime(&future);
    if (due == NULL) {
        print_error("返却期限の計算に失敗しました。");
        return -7;
    }
    
    char due_date_str[20];
    snprintf(due_date_str, sizeof(due_date_str), "%d-%02d-%02d", due->tm_year + 1900, due->tm_mon + 1, due->tm_mday);

    printf("書籍名: ");
    int book_index = find_book_index((char*)book_id);
    if (book_index >= 0) {
        printf("%s\n", book_names[book_index]);
    } else {
        printf("不明な書籍\n");
    }
    printf("貸出料金: %d円\n", fee);
    printf("返却期限: %s まで（7泊8日）\n", due_date_str);
    
    int confirm = 0;
    printf("貸出を確定しますか？ (1: はい / 2: いいえ): ");
    if (scanf("%d", &confirm) != 1) {
        print_error("無効な入力です。支払いおよび貸出をキャンセルします。");
        while (getchar() != '\n');
        return -5;
    }

    if (confirm != 1) {
        printf("貸出がキャンセルされました。\n");
        return -5;
    }

    if (book_index >= 0) {
        is_borrowed[book_index] = 1;
        
        strncpy(borrowed_user_ids[book_index], user_id, 19);
        borrowed_user_ids[book_index][19] = '\0';
        
        strncpy(borrowed_rent_dates[book_index], date, 19);
        borrowed_rent_dates[book_index][19] = '\0';
        
        strncpy(borrowed_due_dates[book_index], due_date_str, 19);
        borrowed_due_dates[book_index][19] = '\0';
    }

    int log_res = save_checkout_log(user_id, book_id, date, "CHECKOUT");
    if (log_res != 0) {
        print_error("操作履歴の保存に失敗しました。");
        return -6;
    }

    printf("貸出が完了しました。\n");
    return 0;
}