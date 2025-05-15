#ifndef BOOK_SLL_H
#define BOOK_SLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct BookNode {
    char name[MAX_NAME_LENGTH];
    int stock;
    struct BookNode *next;
} BookNode;

typedef struct {
    BookNode *head;
    int count;
} BookList;

void sll_initBookList(BookList *list);
int sll_addBook(BookList *list, const char *name, int stock);
BookNode* sll_findBook(BookList *list, const char *name);
int sll_updateBookStock(BookList *list, const char *name, int quantity);
void sll_displayBooks(BookList *list);
void sll_freeBookList(BookList *list);
int sll_returnBook(BookList *list, const char *name);

#endif
