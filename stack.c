#include "stack.h"

void initStack(Stack *stack) {
    stack->top = NULL;
}

int isStackEmpty(Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, HistoryItem item) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Alokasi memori gagal untuk operasi stack.\n");
        return;
    }
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack, HistoryItem *item) {
    if (isStackEmpty(stack)) {
        printf("Riwayat kosong. Tidak ada aktivitas untuk dibatalkan.\n");
        return 0;
    }
    StackNode *temp = stack->top;
    *item = temp->data;
    stack->top = temp->next;
    free(temp);
    return 1;
}

void displayHistory(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("Tidak ada riwayat peminjaman yang tersedia.\n");
        return;
    }
    printf("\n=== Riwayat Peminjaman ===\n");
    printf("Peminjaman terakhir:\n");
    StackNode *current = stack->top;
    int count = 1;
    while (current != NULL) {
        printf("%d. Peminjam: %s, Buku: %s\n", count, current->data.borrowerName, current->data.bookName);
        current = current->next;
        count++;
    }
}
