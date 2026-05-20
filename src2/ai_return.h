#ifndef AI_RETURN_H
#define AI_RETURN_H

#define AI_RETURN_OK 0
#define AI_RETURN_ERR_ARG -1
#define AI_RETURN_ERR_NOT_FOUND -2
#define AI_RETURN_ERR_IO -6
#define AI_RETURN_ERR_DATE -7
#define AI_RETURN_ERR_USER_MISMATCH -4

int ai_calculate_late_fee(const char *due_date, const char *return_date, int daily_fee);
int ai_return_book(
    const char *history_csv,
    const char *user_id,
    const char *book_id,
    const char *return_date,
    int *out_late_fee
);

#endif
