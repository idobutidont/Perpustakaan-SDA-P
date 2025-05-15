#ifndef BOOK_ARRAY_H
#define BOOK_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int stock;
} Book;

typedef struct {
    Book books[MAX_BOOKS];
    int count;
} BookList;

void array_initBookList(BookList *list);
int array_addBook(BookList *list, const char *name, int stock);
int array_findBook(BookList *list, const char *name);
int array_updateBookStock(BookList *list, const char *name, int quantity);
void array_displayBooks(BookList *list);
int array_returnBook(BookList *list, const char *name);

#endif
