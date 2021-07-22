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
		printf("<<| KAL-EL 6 |>>\n");
		puts("MENU UTAMA");
		puts("[1] Registrasi");
		puts("[2] Panggil Antrian");
		puts("[3] Keluar");

		printf("Pilihan : ");
		scanf("%d", &option);

		if (option == 1){
			Registration(&Q);
			PrintQueue(Q);
			getch();
		}
		else if (option == 2){
			
		}else if (option == 3){
			exit(0);
		}else{
			printf("Maaf, masukan Anda salah. Silahkan coba lagi.");
		}
	}while (option != 3);

	return 0;
}
