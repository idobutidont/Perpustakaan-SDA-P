#include "book_sll.h"

void sll_initBookList(BookList *list) {
    list->head = NULL;
    list->count = 0;
}

int sll_addBook(BookList *list, const char *name, int stock) {
    BookNode *existing = sll_findBook(list, name);
    if (existing != NULL) {
        existing->stock += stock;
        printf("Stok diperbarui untuk '%s'. Stok baru: %d\n", name, existing->stock);
        return 1;
    }
    BookNode *newNode = (BookNode *)malloc(sizeof(BookNode));
    if (newNode == NULL) {
        printf("Alokasi memori gagal untuk operasi buku.\n");
        return 0;
    }
    strcpy(newNode->name, name);
    newNode->stock = stock;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
    printf("Buku '%s' ditambahkan dengan stok %d\n", name, stock);
    return 1;
}

BookNode* sll_findBook(BookList *list, const char *name) {
    BookNode *current = list->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int sll_updateBookStock(BookList *list, const char *name, int quantity) {
    BookNode *book = sll_findBook(list, name);
    if (book == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", name);
        return 0;
    }
    book->stock += quantity;
    printf("Stok diperbarui untuk '%s'. Stok baru: %d\n", name, book->stock);
    return 1;
}

void sll_displayBooks(BookList *list) {
    if (list->count == 0) {
        printf("Tidak ada buku yang tersedia di perpustakaan.\n");
        return;
    }
    printf("\n=== Buku yang Tersedia ===\n");
    BookNode *current = list->head;
    int count = 1;
    while (current != NULL) {
        printf("%d. %s (Stock: %d)\n", count, current->name, current->stock);
        current = current->next;
        count++;
    }
}

void sll_freeBookList(BookList *list) {
    BookNode *current = list->head;
    BookNode *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->count = 0;
}

int sll_returnBook(BookList *list, const char *name) {
    BookNode *book = sll_findBook(list, name);
    if (book == NULL) {
        printf("Buku '%s' tidak ditemukan dalam inventaris perpustakaan.\n", name);
        return 0;
    }
    book->stock++;
    printf("Buku '%s' telah dikembalikan. Stok baru: %d\n", name, book->stock);
    return 1;
}
