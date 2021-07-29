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

char *ArrDisease[9] = {
	"Bersin",
	"Luka Ringan",
	"Penyakit Kulit",
	"Cacingan",
	"Diare",
	"Luka Dalam",
	"Gangguan Kerongkongan yang Berbau Busuk",
	"Penyakit Kuning",
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
	addrNQ P, travel, before, after;
	P = Allocation(data);
	if (IsQueueEmpty(*Q) == 1){
		Front(*Q) = P;
		Rear(*Q) = P;
	}
	else if (P!=Nil && (*Q).Rear->info.FinishingTime < P->info.ArrivalTime){
		(*Q).Rear->next = P;
		(*Q).Rear = P;
	}	
	else if (P != Nil && (*Q).Rear->info.FinishingTime >= P->info.ArrivalTime){
		if((*Q).Front == (*Q).Rear){
			if (P->info.ArrivalTime == (*Q).Front->info.ArrivalTime){
				if ((*Q).Front->info.Priority < P->info.Priority){
					P->next = (*Q).Front;
					(*Q).Front = P;
				}
				else {
					(*Q).Front->next = P;
					(*Q).Rear = P;
				}
			}
			else {
				(*Q).Front->next = P;
				(*Q).Rear = P;
			}
		}
		else{
			if(P->info.ArrivalTime == (*Q).Front->info.ArrivalTime){
				if ((*Q).Front->info.Priority < P->info.Priority){
					P->next = (*Q).Front;
					(*Q).Front = P;
				}
				else if ((*Q).Front->info.Priority <= P->info.Priority){
					travel = (*Q).Front;
					while (P->info.Priority <= travel->info.Priority && travel->next!=NULL){
						before = travel;
						travel = travel->next;
					}
					if (travel->next==NULL){
						travel->next = P;
						(*Q).Rear = P;
					}
					else if (travel->next!=NULL){
						after = travel->next;
						travel->next = P;
						P->next = after;
					}
				}
			}
			else if(P->info.ArrivalTime != (*Q).Front->info.ArrivalTime){
				travel = (*Q).Front;
				while (travel->info.ArrivalTime == (*Q).Front->info.ArrivalTime && travel->next!=NULL){
					before = travel;
					travel = travel->next; 
				}
				if (travel->info.ArrivalTime != (*Q).Front->info.ArrivalTime && travel->next==NULL){
					if (travel->info.Priority < P->info.Priority){
						before->next = P;
						P->next = travel;
					}
					else {
						travel->next = P;
						(*Q).Rear = P;
					}
				}
				else if (travel->next==NULL){
					travel->next = P;
					(*Q).Rear = P;
				}
				else if (travel->info.ArrivalTime != (*Q).Front->info.ArrivalTime){
					if (travel->info.Priority < P->info.Priority){
						before->next = P;
						P->next = travel;
					}
					else {
						while (travel->info.Priority >= P->info.Priority){
							before = travel;
							travel = travel->next;
						}
						if (travel->next!=NULL){
							after = travel->next;
							if (travel->info.Priority < P->info.Priority){
								before->next=P;
								P->next=travel;
							}
							else {
								while (travel->info.Priority <= after->info.Priority){
									if (travel->info.Priority > after->info.Priority){
										P->next=after;
										travel->next = P;
									}
									travel = after;
									after = after->next;
								}
							}
						
						}
						else if (travel->next==NULL){
							before->next = P;
							P->next = travel;
						}
					}
				}
			}
		}
	}
}

/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari
Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */
/* F.S. info yang diambil = nilai elemen Front pd I.S. */
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q
mungkin kosong */
void deQueue(Queue *Q){
	if(IsQueueEmpty(*Q)==1) printf("\nMaaf Antrian Kosong.\n");
	else {
		addrNQ P;
		P = (*Q).Front;
		if ((*Q).Front==(*Q).Rear){
			(*Q).Front=NULL;
			(*Q).Rear=NULL;
		}
		else{
			(*Q).Front = (*Q).Front->next;
		}
		P->next=NULL;
		Deallocation(&P);
		printf("Antrian Dipanggil...\n");
	}
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

/*
  Menampilkan daftar penyakit yang diambil dari variabel global ArrDisease
*/
void PrintDisease(){
	int i;
	for (i = 0; i < 9; i++){
		printf("[%i] %s\n", i + 1, ArrDisease[i]);
	}
}

/*
  Mengembalikan nilai string apakah Ringan, Sedang atau Berat berdasarkan penyakit yang diderita
*/
char *CategoryCheck(int Disease){
	if (Disease < 4){
		return "Ringan";
	}else if (Disease < 7){
		return "Sedang";
	}else if (Disease < 10){
		return "Berat";
	}
}

/*
  Mengembalikan nilai integer berupa waktu pemeriksaan berdasarkan kategori penyakit
*/
int InspectionTimeCheck(int Disease){
	if (Disease < 4){
		return 15;
	}else if (Disease < 7){
		return 30;
	}else if (Disease < 10){
		return 45;
	}
}

/*
  Mengembalikan nilai integer berupa perhitungan nilai prioritas berdasarkan jumlah penyakit dan kategori penyakit
*/
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

/*
  Mengembalikan nilai integer untuk waktu pemeriksaan berdasarkan setiap penyakit yang diderita
*/
int InspectionTimeCount(int Ringan, int Sedang, int Berat){
	return (Ringan * 15) + (Sedang * 30) + (Berat * 45);
}

int WaitingTimeCount(addrNQ P, int ArrivalTime){
	if(P == Nil){
		return 0;
	}else{
		if(ArrivalTime < Info(P).FinishingTime){
			return Info(P).FinishingTime - ArrivalTime;
		}else{
			return 0;
		}
	}
}

/*	
  Menentukan dan mengubah waktu mulai dan waktu selesai jika terjadi perubahan urutan antrian berdasarkan nilai prioritas
*/
void setTime(Queue *Q, infotype *X){
	addrNQ P, R;
	
	if(IsQueueEmpty(*Q)){
		X->StartingTime = X->ArrivalTime;
		X->FinishingTime = X->ArrivalTime + X->InspectionTime;
	}else if(Front(*Q)==Rear(*Q)){
		X->StartingTime = Info(Front(*Q)).FinishingTime;
		X->FinishingTime = X->StartingTime + X->InspectionTime;
	} else {
		P = Next(Front(*Q));
		if(X->Priority > Info(P).Priority){
			X->StartingTime = Info(P).StartingTime;
			X->FinishingTime = X->StartingTime + X->InspectionTime;
			Info(P).StartingTime = X->FinishingTime;
			Info(P).FinishingTime = Info(P).StartingTime + Info(P).InspectionTime;
			while(Next(P) != Nil){
				Next(P)->info.StartingTime = Info(P).FinishingTime;
				Next(P)->info.FinishingTime = Info(P).FinishingTime + Next(P)->info.InspectionTime;
				P = Next(P);
			}
		}else if(X->Priority <= Info(P).Priority){
			while(P != Nil){
				if(X->Priority <= Info(P).Priority ){
					R = P;
					P = Next(P);
				} else {
					break;
				}
			}
			
			if(P == Nil){
				if(X->ArrivalTime > Info(R).FinishingTime){
					X->StartingTime = X->ArrivalTime;
				} else {
					X->StartingTime = Info(R).FinishingTime;
				}
				X->FinishingTime = X->StartingTime + X->InspectionTime;
			} else {
				if(X->Priority == Info(R).Priority){
					if(X->ArrivalTime > Info(R).FinishingTime){
						X->StartingTime = X->ArrivalTime;
					} else {
						X->StartingTime = Info(R).StartingTime;
					}
					
					X->FinishingTime = X->StartingTime + X->InspectionTime;
					Info(P).StartingTime = X->FinishingTime;
					Info(P).FinishingTime = Info(P).StartingTime + Info(P).InspectionTime;
					while(Next(P) != Nil){
						Next(P)->info.StartingTime = Info(P).FinishingTime;
						Next(P)->info.FinishingTime = Info(P).FinishingTime + Next(P)->info.InspectionTime;
						P = Next(P);
					}
				} else {
					if(X->ArrivalTime > Info(R).FinishingTime){
						X->StartingTime = X->ArrivalTime;
					} else {
						X->StartingTime = Info(P).StartingTime;
					}
					
					X->StartingTime = Info(P).StartingTime;
					X->FinishingTime = X->StartingTime + X->InspectionTime;
					Info(P).StartingTime = X->FinishingTime;
					Info(P).FinishingTime = Info(P).StartingTime + Info(P).InspectionTime;
					while(Next(P) != Nil){
						Next(P)->info.StartingTime = Info(P).FinishingTime;
						Next(P)->info.FinishingTime = Info(P).FinishingTime + Next(P)->info.InspectionTime;
						P = Next(P);
					}
				}
			}
			
		}
	}
}

/*
  Menampilkan menu registrasi dan menerima masukan pengguna yang akan dimasukkan ke dalam Queue
*/
void Registration(Queue *Q){
	system("cls");
	infotype X;
	CreateList(&X.DiseaseList);
	InfoList Y;

	int tempDisease[9];

	int i, SymptomTotal;

	printf("========== REGISTRASI ==========\n");
	printf("Waktu Kedatangan		: ");
	scanf("%d", &X.ArrivalTime);
	fflush(stdin);
	printf("Nama Kucing			: ");
	scanf("%s", &X.Name);
	fflush(stdin);

	puts("Daftar Penyakit");
	PrintDisease();
	printf("Jumlah Penyakit yang Diderita	: ");
	scanf("%d", &SymptomTotal);
	puts("Penyakit yang Diderita		: ");
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
	setTime(*(&Q),&X);
	
	enQueue(Q, X);
}

/*	
  Menampilkan daftar antrian yang memuat informasi total antrian, no urut antrian, nama, waktu kedatangan, 
  daftar penyakit, prioritas, waktu pemeriksaan, waktu mulai dan waktu selesai
*/
void PrintQueue(Queue Q){
	addrNQ P;
	address F;

	int i = 1, j, length;

	P = Front(Q);

	puts("========== DAFTAR ANTRIAN ==========");
	
	if(P == Nil){
		puts("\nSaat ini belum ada antrian yang masuk");
	}else{
		printf("Total Antrian		: %d\n", NBElmt(Q));
		puts("------------------------------------");
		while (P != Nil){
			printf("No. Urut Antrian	: %d\n", i++);
			printf("Nama			: %s\n", Info(P).Name);
			printf("Waktu Kedatangan	: %d\n", Info(P).ArrivalTime);
			puts("Penyakit yang Diderita	:");
	
			PrintInfo(Info(P).DiseaseList, ArrDisease);
			
			printf("Prioritas		: %d\n", Info(P).Priority);
			printf("Waktu Pemeriksaan	: %d\n", Info(P).InspectionTime);
			printf("Waktu Mulai 		: %d\n", Info(P).StartingTime);
			printf("Waktu Selesai		: %d\n", Info(P).FinishingTime);
	
			puts("------------------------------------");
	
			P = Next(P);
		}
	}
}
