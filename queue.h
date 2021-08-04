/*
	Modified		: Algi Fari Ramdhani, Kevandra Rivaldy Adrianto Putra, & Mochammad Lutfi Faturachman
	Date Modified 	: 19 Juli 2021
	Version			: 5.0
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
	int WaitingTime;
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

/***** Algoritma Program *****/
/* Menampilkan daftar penyakit yang diambil dari variabel global ArrDisease
   dan mengelompokkannya ke dalam kategori
*/
void PrintDisease();
/* Mengembalikan nilai string apakah Ringan, Sedang atau Berat berdasarkan penyakit yang diderita
*/
char *CategoryCheck(int Disease);
/* Mengembalikan nilai integer berupa waktu pemeriksaan setiap penyakit berdasarkan kategori penyakit
*/
int InspectionTimeCheck(int Disease);
/* Proses : Mengembalikan nilai integer berupa perhitungan nilai prioritas berdasarkan jumlah penyakit dan kategori penyakit
   I.S : variabel count bernilai 1
   F.S : Nilai variabel count tetap atau berubah
*/
int PriorityCount(int Ringan, int Sedang, int Berat);
/* Mengembalikan nilai integer untuk waktu pemeriksaan berdasarkan jumlah setiap penyakit yang diderita
*/
int InspectionTimeCount(int Ringan, int Sedang, int Berat);
/* Proses : Menghitung dan mengubah waktu tunggu, waktu mulai, dan waktu selesai jika terjadi
             perubahan urutan antrian
   I.S : Semua waktu belum ada nilai atau tidak sesuai
   F.S : Nilai semua waktu berubah seiring adanya perubahan urutan queue
*/
void setTime(Queue *Q);
/* Proses : Menampilkan menu registrasi dan menerima masukan pengguna yang akan dimasukkan ke dalam Queue
   I.S : Data queue belum dimasukkan
   F.S : Data dari inputan pengguna dimasukkan ke dalam queue dan menampilkan isi daftar antrian
*/
void Registration(Queue *Q);
/* Proses : Memasukkan data-data queue yang terinput ke dalam file daftar-antrian.txt
           dan mengubah seluruh isi file seiring terjadinya perubahan urutan
   I.S : File mungkin kosong atau tidak ada
   F.S : Jika file tersebut tidak ada, program mengirimkan pesan eror
  		 Jika ada, program akan meng-overwrite data-data queue
*/
void EntryQueueFile(Queue *Q);
/* Proses : Memasukkan data-data queue yang terhapus ke dalam file riwayat-antrian.txt
  		   secara berurutan
   I.S : File mungkin kosong atau tidak ada
   F.S : Jika file tersebut tidak ada, program mengirimkan pesan eror
  		 Jika file ada, program akan memasukkan data-data queue yang terhapus tanpa menimpa data
  		 sebelumnya
*/
void EntryHistoryFile(addrNQ P);
/* Proses : Membaca seluruh isi file daftar-antrian.txt
   I.S : File mungkin tidak ada atau mungkin ada
   F.S : Jika file tidak ditemukan, program mengirimkan pesan eror
         Jika file ada, program menampilkan isi dari file daftar-antrian.txt
*/
void PrintQueue(Queue Q);
/* Proses : Membaca seluruh isi file riwayat-antrian.txt
   I.S : File mungkin tidak ada atau mungkin ada
   F.S : Jika file tidak ditemukan, program mengirimkan pesan eror
         Jika file ada, program menampilkan isi dari file riwayat-antrian.txt
*/
void PrintHistory();

#endif // QUEUE_H
