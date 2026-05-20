#ifndef AI_MODULES_H
#define AI_MODULES_H

#include <stddef.h>

/* ai_check.c */
int is_valid_book_id(const char* book_id);
int is_valid_user_id(const char* user_id);
int get_book_stock(const char* book_id);

/* ai_checkout.c */
int checkout_book(const char* user_id, const char* book_id, const char* date);
int can_user_borrow_book(const char* user_id, const char* book_id);
int calculate_rental_fee(const char* book_id);
int save_checkout_log(const char* user_id, const char* book_id, const char* date, const char* action);

/* ai_findBookid.c */
int find_book_index(char input_id[]);
int ai_input_book_id(char *book_id, size_t size);

/* ai_getDate.c */
void get_rent_date(char date[]);
void get_due_date(char due_date[]);
void notify_due_date(const char* user_id, const char* book_id, const char* due_date);

/* ai_history.c */
int check_user_id_for_return(const char* user_id, const char* book_id);
void save_history(const char* status, const char* user_id, const char* book_id, const char* rent_date, const char* due_date, const char* return_date);
void show_history(void);

/* ai_member.c */
int get_user_point(const char* user_id);
int add_user_point(const char* user_id, int points_to_add);

#endif
