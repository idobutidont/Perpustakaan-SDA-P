#ifndef BOOK_DLL_H
#define BOOK_DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct BookNode {
    char name[MAX_NAME_LENGTH];
    int stock;
    struct BookNode *prev;
    struct BookNode *next;
} BookNode;

typedef struct {
    BookNode *head;
    BookNode *tail;
    int count;
} BookList;

void dll_initBookList(BookList *list);
int dll_addBook(BookList *list, const char *name, int stock);
BookNode* dll_findBook(BookList *list, const char *name);
int dll_updateBookStock(BookList *list, const char *name, int quantity);
void dll_displayBooks(BookList *list);
void dll_displayBooksReverse(BookList *list);
void dll_freeBookList(BookList *list);
int dll_returnBook(BookList *list, const char *name);

#endif
