/*
	Modified		: Algi Fari Ramdhani, Mochammad Lutfi Faturachman & Kevandra Rivaldy Adrianto Putra
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
void deQueue(Queue *Q);
/* Mengirimkan banyaknya elemen queue jika Q berisi atrian atau
mengirimkan 0 jika Q kosong
*/
int NBElmt(Queue Q);

/*	
  Menampilkan daftar penyakit yang diambil dari variabel global ArrDisease
*/
void PrintDisease();

/*
  Mengembalikan nilai string apakah Ringan, Sedang atau Berat berdasarkan penyakit yang diderita
*/
char *CategoryCheck(int Disease);

/*
  Mengembalikan nilai integer berupa waktu pemeriksaan berdasarkan kategori penyakit
*/
int InspectionTimeCheck(int Disease);

/*
  Mengembalikan nilai integer berupa perhitungan nilai prioritas berdasarkan jumlah penyakit dan kategori penyakit
*/
int PriorityCount(int Ringan, int Sedang, int Berat);

/*
  Mengembalikan nilai integer untuk waktu pemeriksaan berdasarkan setiap penyakit yang diderita
*/
int InspectionTimeCount(int Ringan, int Sedang, int Berat);

/*	
  Menentukan dan mengubah waktu mulai dan waktu selesai jika terjadi perubahan urutan antrian berdasarkan nilai prioritas
*/
void setTime(Queue *Q, infotype *X);

/*	
  Menampilkan menu registrasi dan menerima masukan pengguna yang akan dimasukkan ke dalam Queue
*/
void Registration(Queue *Q);

/*	
  Menampilkan daftar antrian yang memuat informasi total antrian, no urut antrian, nama, waktu kedatangan, 
  daftar penyakit, prioritas, waktu pemeriksaan, waktu mulai dan waktu selesai
*/
void PrintQueue(Queue Q);

#endif // QUEUE_H
