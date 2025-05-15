#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack.h"
#include "../queue.h"
#include "book_sll.h"

void sll_displayMenu();
void sll_processAddBook(BookList *books);
void sll_processAddBorrower(Queue *borrowers, Stack *history);
void sll_processBorrowing(BookList *books, Queue *borrowers, Stack *history);
void sll_processCancelLastRequest(Stack *history);
void sll_processReturnBook(BookList *books, Stack *history);

int sll_main() {
    BookList bookList;
    Queue borrowersQueue;
    Stack history;
    
    sll_initBookList(&bookList);
    initQueue(&borrowersQueue);
    initStack(&history);
    
    int choice;
    
    printf("\n===== Perpustakaan di Perguruan Tinggi (Implementasi Single Linked List) =====\n");
    
    do {
        sll_displayMenu();
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                sll_processAddBook(&bookList);
                break;
            case 2:
                sll_processAddBorrower(&borrowersQueue, &history);
                break;
            case 3:
                sll_processBorrowing(&bookList, &borrowersQueue, &history);
                break;
            case 4:
                sll_processCancelLastRequest(&history);
                break;
            case 5:
                sll_processReturnBook(&bookList, &history);
                break;
            case 6:
                sll_displayBooks(&bookList);
                break;
            case 7:
                displayQueue(&borrowersQueue);
                break;
            case 8:
                displayHistory(&history);
                break;
            case 0:
                printf("Keluar dari program. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        system("clear");
        
    } while (choice != 0);
    
    sll_freeBookList(&bookList);
    clearQueue(&borrowersQueue);
    
    return 0;
}

void sll_displayMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Tambahkan Buku\n");
    printf("2. Pinjam Buku\n");
    printf("3. Proses Antrian Peminjaman\n");
    printf("4. Batalkan Peminjaman Terakhir\n");
    printf("5. Pengembalian Buku\n");
    printf("6. List Semua Buku\n");
    printf("7. List Antrian Peminjam\n");
    printf("8. List Riwayat Pinjaman\n");
    printf("0. Exit\n");
}

void sll_processAddBook(BookList *books) {
    char name[MAX_NAME_LENGTH];
    int stock;
    
    printf("\n=== Tambah Stok Buku ===\n");
    printf("Masukkan nama buku: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0;
    
    printf("Masukkan jumlah stok: ");
    scanf("%d", &stock);
    getchar();
    
    if (stock <= 0) {
        printf("Jumlah stok tidak valid. Harus positif.\n");
        return;
    }
    
    sll_addBook(books, name, stock);
}

void sll_processAddBorrower(Queue *borrowers, Stack *history) {
    Borrower newBorrower;
    int memberType;
    
    printf("\n=== Tambah Peminjam ke Antrian ===\n");
    printf("Masukkan nama peminjam: ");
    fgets(newBorrower.name, MAX_NAME_LENGTH, stdin);
    newBorrower.name[strcspn(newBorrower.name, "\n")] = 0;
    
    printf("Masukkan tipe anggota (1: Dosen, 2: Mahasiswa, 3: Umum): ");
    scanf("%d", &memberType);
    getchar();
    
    if (memberType < LECTURER || memberType > PUBLIC) {
        printf("Tipe anggota tidak valid. Menggunakan Umum sebagai default.\n");
        newBorrower.type = PUBLIC;
    } else {
        newBorrower.type = (MemberType)memberType;
    }
    
    printf("Masukkan nama buku untuk dipinjam: ");
    char bookName[MAX_NAME_LENGTH];
    fgets(bookName, MAX_NAME_LENGTH, stdin);
    bookName[strcspn(bookName, "\n")] = 0;
    
    enqueue(borrowers, newBorrower);
    
    HistoryItem item;
    strcpy(item.bookName, bookName);
    strcpy(item.borrowerName, newBorrower.name);
    push(history, item);
    
    printf("Peminjam '%s' ditambahkan ke antrian untuk buku '%s'.\n", newBorrower.name, bookName);
}

void sll_processBorrowing(BookList *books, Queue *borrowers, Stack *history) {
    char bookName[MAX_NAME_LENGTH];
    
    printf("\n=== Proses Peminjaman ===\n");
    printf("Masukkan nama buku untuk memproses peminjaman: ");
    fgets(bookName, MAX_NAME_LENGTH, stdin);
    bookName[strcspn(bookName, "\n")] = 0;
    
    BookNode *book = sll_findBook(books, bookName);
    if (book == NULL) {
        printf("Buku '%s' tidak ditemukan di perpustakaan.\n", bookName);
        return;
    }
    
    if (book->stock <= 0) {
        printf("Maaf, '%s' sedang habis stok.\n", bookName);
        return;
    }
    
    if (isQueueEmpty(borrowers)) {
        printf("Tidak ada peminjam dalam antrian.\n");
        return;
    }
    
    Borrower borrower;
    dequeue(borrowers, &borrower);
    
    printf("Buku '%s' telah dipinjam oleh %s (", bookName, borrower.name);
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
    printf(").\n");
    
    book->stock--;
    printf("Sisa stok: %d\n", book->stock);
    
    HistoryItem item;
    strcpy(item.bookName, bookName);
    strcpy(item.borrowerName, borrower.name);
    push(history, item);
}

void sll_processCancelLastRequest(Stack *history) {
    printf("\n=== Batalkan Permintaan Peminjaman Terakhir ===\n");
    
    HistoryItem item;
    if (pop(history, &item)) {
        printf("Permintaan peminjaman terakhir untuk buku '%s' dibatalkan.\n", item.bookName);
    } else {
        printf("Tidak ada riwayat untuk dibatalkan.\n");
    }
}

int sll_verifyBorrower(Stack *history, const char *bookName, const char *borrowerName) {
    if (isStackEmpty(history)) {
        return 0;
    }
    
    Stack tempStack;
    initStack(&tempStack);
    int found = 0;
    
    while (!isStackEmpty(history)) {
        HistoryItem item;
        pop(history, &item);
        
        if (strcmp(item.bookName, bookName) == 0 && 
            strcmp(item.borrowerName, borrowerName) == 0) {
            found = 1;
        }
        
        push(&tempStack, item);
    }
    
    while (!isStackEmpty(&tempStack)) {
        HistoryItem item;
        pop(&tempStack, &item);
        push(history, item);
    }
    
    return found;
}

void sll_processReturnBook(BookList *books, Stack *history) {
    char bookName[MAX_NAME_LENGTH];
    char borrowerName[MAX_NAME_LENGTH];
    
    printf("\n=== Pengembalian Buku ===\n");
    printf("Masukkan nama buku untuk dikembalikan: ");
    fgets(bookName, MAX_NAME_LENGTH, stdin);
    bookName[strcspn(bookName, "\n")] = 0;
    
    printf("Masukkan nama peminjam yang mengembalikan: ");
    fgets(borrowerName, MAX_NAME_LENGTH, stdin);
    borrowerName[strcspn(borrowerName, "\n")] = 0;
    
    BookNode *book = sll_findBook(books, bookName);
    if (book == NULL) {
        printf("Buku '%s' tidak ditemukan dalam inventaris perpustakaan.\n", bookName);
        return;
    }
    
    if (!sll_verifyBorrower(history, bookName, borrowerName)) {
        printf("Verifikasi gagal. '%s' tidak tercatat meminjam buku '%s'.\n", borrowerName, bookName);
        return;
    }
    
    book->stock++;
    printf("Buku '%s' telah dikembalikan oleh '%s'. Stok baru: %d\n", 
           bookName, borrowerName, book->stock);
}
