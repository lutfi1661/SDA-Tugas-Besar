/*
	Modified		: Algi Fari Ramdhani & Mochammad Lutfi Faturachman
	Date Modified 	: 19 Juli 2021
	Version			: 1.0
*/
#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#include "list.h"
#include <stdio.h>

#define Info(P) (P)->info
#define Next(P) (P)->next
#define InfoFront(Q) (Q).Front->info
#define InfoRear(Q) (Q).Rear->info
#define Front(Q) (Q).Front
#define Rear(Q) (Q).Rear

typedef struct NodeQueue *addrNQ;

typedef struct{
	char Name[16];
	int ArrivalTime;
	List DiseaseList;
	int StartingTime;
	int InspectionTime;
	int FinishingTime;
	int Priority;
} InfoQueue;
typedef InfoQueue infotype;

typedef struct NodeQueue{
	infotype info;
	addrNQ next;
} NodeQueue;
typedef struct{
	addrNQ Front;
	addrNQ Rear;
} Queue;

/***** Manajemen memori *****/
/* Mengirimkan address hasil alokasi sebuah elemen dengan info X.
* Jika alokasi berhasil, modul mengembalikan P; Info(P) = X,
Next(P) = NULL.
* P adalah pointer yang menunjuk ke node Queue sebagai hasil
alokasi.
* Jika alokasi gagal, modul mengembalikan NULL.
*/
addrNQ Allocation(infotype X);
/* Melakukan dealokasi elemen P (pointer menunjuk ke alamat node
queue).
* I.S.: P terdefinisi.
* F.S.: P dikembalikan ke sistem.
*/
void Deaallocation(addrNQ *P);
/***** Manajemen Queue *****/
/* Membuat sebuah Queue kosong dengan Front(Q) = Nil dan Rear (Q) =
Nil
I.S. Belum terbentuk Queue
F.S. Sudah terbentuk Queue
*/
void CreateQueue(Queue *Q);
/* Mengetahui apakah Queue kosong atau tidak.
mengirimkan 1 jika Queue Kosong yaitu Front(Q) = Nil dan Rear
(Q) = Nil
Sebaliknya 0 (Queue tidak kosong)
*/
int IsQueueEmpty(Queue Q);
/* Memasukkan info baru ke dalam Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */
/* F.S. info baru (data) menjadi Rear yang baru dengan node Rear
yang lama mengaitkan pointernya ke node yang baru */
void enQueue(Queue *Q, infotype data);
/* Proses: Mengambil info pada Front(Q) dan mengeluarkannya dari
Queue dengan aturan FIFO */
/* I.S. Q mungkin kosong atau Q mungkin berisi antrian */
/* F.S. info yang diambil = nilai elemen Front pd I.S. */
/* Front(Q) menunjuk ke next antrian atau diset menjadi NIll, Q
mungkin kosong */
void deQueue(Queue *Q, infotype *data);
/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau
mengirimkan 0 jika Q kosong
*/
int NBElmt(Queue Q);

void PrintDisease();

char *CategoryCheck(int Disease);

int InspectionTimeCheck(int Disease);

int PriorityCount(int Ringan, int Sedang, int Berat);

int InspectionTimeCount(int Ringan, int Sedang, int Berat);

void setTime(Queue *Q, infotype *X);

void Registration(Queue *Q);

void PrintQueue(Queue Q);

#endif // QUEUE_H
