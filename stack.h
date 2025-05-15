#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char bookName[MAX_NAME_LENGTH];
    char borrowerName[MAX_NAME_LENGTH];
} HistoryItem;

typedef struct StackNode {
    HistoryItem data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

void initStack(Stack *stack);
int isStackEmpty(Stack *stack);
void push(Stack *stack, HistoryItem item);
int pop(Stack *stack, HistoryItem *item);
void displayHistory(Stack *stack);

#endif
