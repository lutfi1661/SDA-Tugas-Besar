#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(){
	Queue Q;
	CreateQueue(&Q);

	int option;

	do{
		system("cls");
		puts("=== SELAMAT DATANG DI KAEL-6 STORE ===");
		puts("MENU UTAMA");
		puts("[1] Registrasi");
		puts("[2] Panggil Antrian");
		puts("[3] Daftar Antrian");
		puts("[4] Keluar");

		printf("Pilih : ");
		scanf("%d", &option);

		if (option == 1){
			Registration(&Q);
			PrintQueue(Q);
			system("pause");
		}
		else if (option == 2){
			deQueue(&Q);
			system("pause");
		}else if (option == 3){
			PrintQueue(Q);
			system("pause");
		}else if (option == 4){
			puts("Terima kasih telah menggunakan Aplikasi Layanan Dokter Hewan");
			exit(0);
		}else{
			printf("Maaf, masukan Anda salah. Silahkan coba lagi.");
		}
	}while (option != 4);

	return 0;
}
