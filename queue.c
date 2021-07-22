/*
	Modified		: Algi Fari Ramdhani & Mochammad Lutfi Faturachman
	Date Modified 		: 19 Juli 2021
	Version			: 1.0
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
* Jika alokasi berhasil, modul mengembalikan P; Info(P) = X,
Next(P) = NULL.
* P adalah pointer yang menunjuk ke node Queue sebagai hasil
alokasi.
* Jika alokasi gagal, modul mengembalikan NULL.
*/

char ArrDisease[9][50] = {
	"Bersin",
	"Luka Ringan",
	"Penyakit Kulit",
	"Cacingan",
	"Diare",
	"Luka Dalam",
	"Gangguan Kerongkongan yang Berbau Busuk",
	"Gangguan Kerongkongan yang Berwarna Kuning",
	"Terkena Virus"
};

addrNQ Allocation(infotype X){
	addrNQ P;
	P = (addrNQ)malloc(sizeof(NodeQueue));
	
	if (P != Nil){
		Info(P) = X;
		Next(P) = Nil;
		return P;
	}else{
		return Nil;
	}
}

/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node
queue).
* I.S.: P terdefinisi.
* F.S.: P dikembalikan ke sistem.
*/
void Deallocation(addrNQ *P){
	free(*P);
}

/***** Manajemen Queue *****/
/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) =
Nil
I.S. Belum terbentuk Queue
F.S. Sudah terbentuk Queue
*/
void CreateQueue(Queue *Q){
	Front(*Q) = Nil;
	Rear(*Q) = Nil;
}

/* Mengetahui apakah Queue kosong atau tidak.
mengirimkan 1 jika Queue Kosong yaitu Front(Q) = Nil dan Rear
(Q) = Nil
Sebaliknya 0 (Queue tidak kosong)
*/
int IsQueueEmpty(Queue Q){
	if ((Front(Q)) == Nil && (Rear(Q) == Nil)){
		return 1;
	}

	return 0;
}

/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear
yang lama mengaitkan pointernya ke node yang baru */

void enQueue(Queue *Q, infotype data){
	addrNQ P;

	P = Allocation(data);

	if (P != Nil){
		if (IsQueueEmpty(*Q) == 1){
			Front(*Q) = P;
			Rear(*Q) = P;
		}else{
			Next(Rear(*Q)) = P;
			Rear(*Q) = P;
		}
	}
}

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari
Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */
/* F.S. info yang diambil = nilai elemen Front pd I.S. */
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q
mungkin kosong */
void deQueue(Queue *Q, infotype *data){
	addrNQ P;

	(*data) = Front(*Q)->info;
	P = Front(*Q);
	Front(*Q) = Next(Front(*Q));

	if (Front(*Q) == Nil){
		Rear(*Q) = Nil;
	}

	Deallocation(&P);
}

/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau
mengirimkan 0 jika Q kosong
*/
int NBElmt(Queue Q){
	addrNQ P;

	int count = 0;

	P = Front(Q);
	while (P != Nil){
		count++;
		P = Next(P);
	}

	return count;
}

void PrintDisease(){
	int i;
	for (i = 0; i < 9; i++){
		printf("[%i] %s\n", i + 1, ArrDisease[i]);
	}
}

char *CategoryCheck(int Disease){
	if (Disease < 4){
		return "Ringan";
	}else if (Disease < 7){
		return "Sedang";
	}else if (Disease < 10){
		return "Berat";
	}
}

int InspectionTimeCheck(int Disease){
	if (Disease < 4){
		return 15;
	}else if (Disease < 7){
		return 30;
	}else if (Disease < 10){
		return 45;
	}
}

int PriorityCount(int Ringan, int Sedang, int Berat){
	int count = 1;
	
	if (Berat >= 1){
		count += 4;
	}
	if (Sedang >= 2){
		count += 3;
	}
	if (Ringan >= 3){
		count += 2;
	}

	return count;
}

int InspectionTimeCount(int Ringan, int Sedang, int Berat){
	return (Ringan * 15) + (Sedang * 30) + (Berat * 45);
}

void Registration(Queue *Q){
	system("cls");
	infotype X;
	CreateList(&X.DiseaseList);
	InfoList Y;

	int tempDisease[9];

	int i, SymptomTotal;

	printf("=== TAMBAH ANTRIAN ===\n");
	printf("Waktu Kedatangan		: ");
	scanf("%d", &X.ArrivalTime);
	fflush(stdin);
	printf("Nama Kucing			: ");
	scanf("%s", &X.Name);
	fflush(stdin);

	puts("Daftar Penyakit,");
	PrintDisease();
	printf("Jumlah Penyakit yang Dialami	: ");
	scanf("%d", &SymptomTotal);
	puts("Penyakit yang Diderita	: ");

	for (i = 0; i < SymptomTotal; i++){
		scanf("%d", &tempDisease[i]);
	}

	int RCount = 0;
	int SCount = 0;
	int BCount = 0;
	for (i = 0; i < SymptomTotal; i++){
		Y.Disease = tempDisease[i];
		strcpy(Y.Category, CategoryCheck(tempDisease[i]));
		Y.InspectionTime = InspectionTimeCheck(tempDisease[i]);
		InsVLast(&X.DiseaseList, Y);

		if ((tempDisease[i] > 0) && (tempDisease[i] < 4)){
			RCount++;
		}
		if ((tempDisease[i] >= 4) && (tempDisease[i] < 7)){
			SCount++;
		}
		if ((tempDisease[i] >= 7) && (tempDisease[i] < 10)){
			BCount++;
		}
	}

	X.Priority = PriorityCount(RCount, SCount, BCount);
	X.InspectionTime = InspectionTimeCount(RCount, SCount, BCount);

	enQueue(Q, X);
}

void PrintQueue(Queue Q){
	addrNQ P;
	address F;

	int i = 1, j, length;

	P = Front(Q);

	puts("========== DAFTAR ANTRIAN ==========");

	while (P != Nil){
		printf("No. Urut Antrian	: %d\n", i++);
		printf("Nama			: %s\n", Info(P).Name);
		printf("Waktu Kedatangan	: %d\n", Info(P).ArrivalTime);
		puts("Penyakit yang Dialami	:");

		F = First(P->info.DiseaseList);
		j = 1;
		while (F != Nil){
			printf("%d. %s (%s)\n", j++, ArrDisease[F->info.Disease - 1], F->info.Category);
			F = Next(F);
		}
		printf("Prioritas		: %d\n", Info(P).Priority);
		printf("Waktu Pemeriksaan	: %d menit\n", Info(P).InspectionTime);
		printf("Waktu Mulai 		: %d \n", Info(P).StartingTime);
		printf("Waktu Selesai		: %d \n", Info(P).FinishingTime);

		puts("------------------------------------");

		P = Next(P);
	}
}
