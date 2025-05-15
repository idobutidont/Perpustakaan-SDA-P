#include <stdio.h>
#include <stdlib.h>

extern int array_main();
extern int sll_main();
extern int dll_main();

void displayMenu();

int main() {
    int choice;
    
    do {
        system("clear");
        printf("\n===== Perpustakaan di Perguruan Tinggi =====\n");
        displayMenu();
        
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                system("clear");
                array_main();
                break;
            case 2:
                system("clear");
                sll_main();
                break;
            case 3:
                system("clear");
                dll_main();
                break;
            case 0:
                printf("Keluar dari program. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                printf("\nTekan Enter untuk melanjutkan...");
                getchar();
        }
        
        if (choice > 0 && choice <= 3) {
            printf("\nKembali ke menu utama...\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
        }
        
    } while (choice != 0);
    
    return 0;
}

void displayMenu() {
    printf("\nPilih jenis implementasi:\n");
    printf("1. Implementasi Array\n");
    printf("2. Implementasi Single Linked List\n");
    printf("3. Implementasi Doubly Linked List\n");
    printf("0. Keluar\n");
}
