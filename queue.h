#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef enum {
    LECTURER = 1,
    STUDENT = 2,
    PUBLIC = 3
} MemberType;

typedef struct {
    char name[MAX_NAME_LENGTH];
    MemberType type;
} Borrower;

typedef struct QueueNode {
    Borrower data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void initQueue(Queue *queue);
int isQueueEmpty(Queue *queue);
void enqueue(Queue *queue, Borrower borrower);
int dequeue(Queue *queue, Borrower *borrower);
void displayQueue(Queue *queue);
int processBookBorrowing(Queue *queue, const char *bookName, int *stock);
void clearQueue(Queue *queue);

#endif
