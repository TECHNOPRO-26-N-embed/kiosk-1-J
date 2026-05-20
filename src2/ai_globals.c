#include "ai_globals.h"

int is_borrowed[MAX_BOOKS] = {0};
int book_count = 0;
char registered_book_ids[MAX_BOOKS][20] = {{0}};
char book_names[MAX_BOOKS][50] = {{0}};
char book_prices[MAX_BOOKS][20] = {{0}};
char borrowed_rent_dates[MAX_BOOKS][20] = {{0}};
char borrowed_due_dates[MAX_BOOKS][20] = {{0}};
char borrowed_user_ids[MAX_BOOKS][20] = {{0}};
