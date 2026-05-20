#ifndef AI_GLOBALS_H
#define AI_GLOBALS_H

#define MAX_BOOKS 100

extern int is_borrowed[MAX_BOOKS];
extern int book_count;
extern char registered_book_ids[MAX_BOOKS][20];
extern char book_names[MAX_BOOKS][50];
extern char book_prices[MAX_BOOKS][20];
extern char borrowed_rent_dates[MAX_BOOKS][20];
extern char borrowed_due_dates[MAX_BOOKS][20];
extern char borrowed_user_ids[MAX_BOOKS][20];

// エラー表示用
void print_error(const char* message);

#endif // AI_GLOBALS_H
