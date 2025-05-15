#include "book_array.h"

void array_initBookList(BookList *list) {
    list->count = 0;
}

int array_addBook(BookList *list, const char *name, int stock) {
    if (list->count >= MAX_BOOKS) {
        printf("Tidak dapat menambahkan buku lagi. Kapasitas maksimum tercapai.\n");
        return 0;
    }
    int index = array_findBook(list, name);
    if (index != -1) {
        list->books[index].stock += stock;
        printf("Stok diperbarui untuk '%s'. Stok baru: %d\n", name, list->books[index].stock);
        return 1;
    }
    strcpy(list->books[list->count].name, name);
    list->books[list->count].stock = stock;
    list->count++;
    printf("Buku '%s' ditambahkan dengan stok %d\n", name, stock);
    return 1;
}

int array_findBook(BookList *list, const char *name) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->books[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int array_updateBookStock(BookList *list, const char *name, int quantity) {
    int index = array_findBook(list, name);
    if (index == -1) {
        printf("Buku '%s' tidak ditemukan.\n", name);
        return 0;
    }
    list->books[index].stock += quantity;
    printf("Stok diperbarui untuk '%s'. Stok baru: %d\n", name, list->books[index].stock);
    return 1;
}

void array_displayBooks(BookList *list) {
    if (list->count == 0) {
        printf("Tidak ada buku yang tersedia di perpustakaan.\n");
        return;
    }
    printf("\n=== Buku yang Tersedia ===\n");
    for (int i = 0; i < list->count; i++) {
        printf("%d. %s (Stock: %d)\n", i + 1, list->books[i].name, list->books[i].stock);
    }
}

int array_returnBook(BookList *list, const char *name) {
    int index = array_findBook(list, name);
    if (index == -1) {
        printf("Buku '%s' tidak ditemukan dalam inventaris perpustakaan.\n", name);
        return 0;
    }
    list->books[index].stock++;
    printf("Buku '%s' telah dikembalikan. Stok baru: %d\n", name, list->books[index].stock);
    return 1;
}
