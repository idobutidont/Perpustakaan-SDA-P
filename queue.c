#include "queue.h"

void initQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isQueueEmpty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, Borrower borrower) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Alokasi memori gagal untuk operasi queue.\n");
        return;
    }
    newNode->data = borrower;
    newNode->next = NULL;
    if (isQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
        return;
    }
    if (borrower.type < queue->front->data.type) {
        newNode->next = queue->front;
        queue->front = newNode;
    } else {
        QueueNode *current = queue->front;
        QueueNode *previous = NULL;
        while (current != NULL && borrower.type >= current->data.type) {
            previous = current;
            current = current->next;
        }
        newNode->next = current;
        if (current == NULL) {
            queue->rear = newNode;
        }
        previous->next = newNode;
    }
}

int dequeue(Queue *queue, Borrower *borrower) {
    if (isQueueEmpty(queue)) {
        printf("Antrian kosong. Tidak ada peminjam untuk diproses.\n");
        return 0;
    }
    QueueNode *temp = queue->front;
    *borrower = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return 1;
}

void displayQueue(Queue *queue) {
    if (isQueueEmpty(queue)) {
        printf("Tidak ada peminjam dalam antrian.\n");
        return;
    }
    printf("\n=== Antrian Peminjam ===\n");
    QueueNode *current = queue->front;
    int count = 1;
    while (current != NULL) {
        printf("%d. %s (", count, current->data.name);
        switch (current->data.type) {
            case LECTURER:
                printf("Dosen");
                break;
            case STUDENT:
                printf("Mahasiswa");
                break;
            case PUBLIC:
                printf("Umum");
                break;
            default:
                printf("Tidak Diketahui");
        }
        printf(")\n");
        current = current->next;
        count++;
    }
}

int processBookBorrowing(Queue *queue, const char *bookName, int *stock) {
    if (isQueueEmpty(queue)) {
        printf("Tidak ada peminjam dalam antrian untuk buku '%s'.\n", bookName);
        return 0;
    }
    if (*stock <= 0) {
        printf("Maaf, '%s' sedang habis stok. Tidak dapat memproses peminjam.\n", bookName);
        return 0;
    }
    Borrower borrower;
    dequeue(queue, &borrower);
    printf("\nMemproses peminjam: %s (", borrower.name);
    switch (borrower.type) {
        case LECTURER:
            printf("Dosen");
            break;
        case STUDENT:
            printf("Mahasiswa");
            break;
        case PUBLIC:
            printf("Umum");
            break;
        default:
            printf("Tidak Diketahui");
    }
    printf(")\n");
    printf("Buku '%s' telah dipinjam. Sisa stok: %d\n", bookName, --(*stock));
    return 1;
}

void clearQueue(Queue *queue) {
    while (!isQueueEmpty(queue)) {
        Borrower dummy;
        dequeue(queue, &dummy);
    }
}
