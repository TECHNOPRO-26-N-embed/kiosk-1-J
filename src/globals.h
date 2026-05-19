#ifndef GLOBALS_H
#define GLOBALS_H

#define MAX_BOOKS 100

extern int is_borrowed[MAX_BOOKS];
extern int book_count;
extern char registered_book_ids[MAX_BOOKS][20];
extern char borrowed_rent_dates[MAX_BOOKS][20];
extern char borrowed_due_dates[MAX_BOOKS][20];

#endif