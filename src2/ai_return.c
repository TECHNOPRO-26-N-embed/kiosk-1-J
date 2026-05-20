#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ai_return.h"

#define LINE_BUF_SIZE 512
#define STR_SMALL 32
#define STR_BOOK_INFO 192

static int parse_ymd(const char *date, struct tm *out_tm) {
    int y;
    int m;
    int d;

    if (date == NULL || out_tm == NULL) {
        return AI_RETURN_ERR_ARG;
    }
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) {
        return AI_RETURN_ERR_DATE;
    }

    memset(out_tm, 0, sizeof(*out_tm));
    out_tm->tm_year = y - 1900;
    out_tm->tm_mon = m - 1;
    out_tm->tm_mday = d;
    out_tm->tm_isdst = -1;

    if (mktime(out_tm) == (time_t)-1) {
        return AI_RETURN_ERR_DATE;
    }
    return AI_RETURN_OK;
}

static int days_between(const char *from_date, const char *to_date) {
    struct tm from_tm;
    struct tm to_tm;
    time_t from_time;
    time_t to_time;
    double diff_days;

    if (parse_ymd(from_date, &from_tm) != AI_RETURN_OK) {
        return AI_RETURN_ERR_DATE;
    }
    if (parse_ymd(to_date, &to_tm) != AI_RETURN_OK) {
        return AI_RETURN_ERR_DATE;
    }

    from_time = mktime(&from_tm);
    to_time = mktime(&to_tm);
    if (from_time == (time_t)-1 || to_time == (time_t)-1) {
        return AI_RETURN_ERR_DATE;
    }

    diff_days = difftime(to_time, from_time) / (60.0 * 60.0 * 24.0);
    return (int)(diff_days);
}

int ai_calculate_late_fee(const char *due_date, const char *return_date, int daily_fee) {
    int overdue_days;

    if (due_date == NULL || return_date == NULL || daily_fee < 0) {
        return AI_RETURN_ERR_ARG;
    }

    overdue_days = days_between(due_date, return_date);
    if (overdue_days < 0) {
        return AI_RETURN_ERR_DATE;
    }
    if (overdue_days <= 0) {
        return 0;
    }
    return overdue_days * daily_fee;
}

static int extract_book_id(const char *book_info, char *out_book_id, size_t out_size) {
    if (book_info == NULL || out_book_id == NULL || out_size == 0) {
        return AI_RETURN_ERR_ARG;
    }
    if (sscanf(book_info, "%31s", out_book_id) != 1) {
        return AI_RETURN_ERR_NOT_FOUND;
    }
    return AI_RETURN_OK;
}

int ai_return_book(
    const char *history_csv,
    const char *user_id,
    const char *book_id,
    const char *return_date,
    int *out_late_fee
) {
    FILE *src;
    FILE *tmp;
    char line[LINE_BUF_SIZE];
    int found_book = 0;
    int updated = 0;
    int saw_user_mismatch = 0;

    if (history_csv == NULL || user_id == NULL || book_id == NULL || return_date == NULL) {
        return AI_RETURN_ERR_ARG;
    }
    if (parse_ymd(return_date, &(struct tm){0}) != AI_RETURN_OK) {
        return AI_RETURN_ERR_DATE;
    }

    src = fopen(history_csv, "r");
    if (src == NULL) {
        return AI_RETURN_ERR_IO;
    }

    tmp = fopen("history.tmp", "w");
    if (tmp == NULL) {
        fclose(src);
        return AI_RETURN_ERR_IO;
    }

    while (fgets(line, sizeof(line), src) != NULL) {
        char status[STR_SMALL] = {0};
        char file_user_id[STR_SMALL] = {0};
        char file_book_info[STR_BOOK_INFO] = {0};
        char rent_date[STR_SMALL] = {0};
        char due_date[STR_SMALL] = {0};
        char file_return_date[STR_SMALL] = {0};
        int file_late_fee = 0;
        char file_book_id[STR_SMALL] = {0};
        int parsed;

        parsed = sscanf(
            line,
            "貸出状況: %31[^,], ユーザーID: %31[^,], 書籍情報: %191[^,], 借用日: %31[^,], 返却期限: %31[^,], 返却日: %31[^,], 延滞料金: %d",
            status,
            file_user_id,
            file_book_info,
            rent_date,
            due_date,
            file_return_date,
            &file_late_fee
        );

        if (parsed != 7 || updated) {
            fputs(line, tmp);
            continue;
        }

        if (extract_book_id(file_book_info, file_book_id, sizeof(file_book_id)) != AI_RETURN_OK) {
            fputs(line, tmp);
            continue;
        }

        if (strcmp(file_book_id, book_id) != 0 || strcmp(status, "貸出中") != 0) {
            fputs(line, tmp);
            continue;
        }

        found_book = 1;
        if (strcmp(file_user_id, user_id) != 0) {
            saw_user_mismatch = 1;
            fputs(line, tmp);
            continue;
        }

        {
            const int daily_fee = 100;
            int late_fee = ai_calculate_late_fee(due_date, return_date, daily_fee);
            if (late_fee < 0) {
                fclose(src);
                fclose(tmp);
                remove("history.tmp");
                return late_fee;
            }

            fprintf(
                tmp,
                "貸出状況: 返却済, ユーザーID: %s, 書籍情報: %s, 借用日: %s, 返却期限: %s, 返却日: %s, 延滞料金: %d\n",
                file_user_id,
                file_book_info,
                rent_date,
                due_date,
                return_date,
                late_fee
            );
            if (out_late_fee != NULL) {
                *out_late_fee = late_fee;
            }
            updated = 1;
        }
    }

    fclose(src);
    fclose(tmp);

    if (!updated) {
        remove("history.tmp");
        if (saw_user_mismatch) {
            return AI_RETURN_ERR_USER_MISMATCH;
        }
        if (found_book) {
            return AI_RETURN_ERR_NOT_FOUND;
        }
        return AI_RETURN_ERR_NOT_FOUND;
    }

    if (remove(history_csv) != 0) {
        remove("history.tmp");
        return AI_RETURN_ERR_IO;
    }
    if (rename("history.tmp", history_csv) != 0) {
        return AI_RETURN_ERR_IO;
    }

    return AI_RETURN_OK;
}
