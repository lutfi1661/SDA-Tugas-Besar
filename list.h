/* File :  list1.h   					*/
/* Desk :  deklarasi list  berkait dgn representasi     */
/* 	   fisik pointer; 				*/
/* 	   Representasi address dgn pointer 		*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/

/* List :  */

#ifndef list1_H
#define list1_H

#include "boolean.h"
#include <stdlib.h>

#define Nil  NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

typedef struct{
	int Disease;
	char Category[10];
	int InspectionTime;
}InfoList;

typedef struct tElmtlist *address;
typedef struct  tElmtlist   {
	InfoList info;
	address next;
}ElmtList;

/* Definisi  List                   */
/* List Kosong  :  First(L) = Nil   */
/* Setiap elemen dengan address P dapat diacu Info(P),Next(P)       */
/* Elemen terakhir  List :jika addressnya Last, maka next(Last)=Nil */

typedef struct {
	address First;
}List;

/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List  L);
/*  Mengirim true jika List kosong  */

/* Pembuatan  List Kosong  */
void CreateList(List *L);
/* I.S  :  Sembarang    		*/
/* F.S  :  Terbentuk  List kosong  	*/

/* Manajeman  memory  			*/
address Alokasi(InfoList  X);
 /* Mengirimkan  address  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Nest(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */

void Dealokasi(address *P);
/* I.S  :   P  terdefinisi         	*/
/* F.S  :   P dikembalikan ke  sistem 	*/
/*   	    Melakukan  dealokasi, pengembalian address  P */

/* ** PRIMITIF BERDASARKAN NILAI ** */

void InsVLast(List *L, InfoList X);
/* I.S  : L mungkin kosong          */
/* F.S  : Melakukan alokasi sebuah elemen dan                */
/*        menambahkan elemen list di akhir; elemen terakhir  */
/*        yang baru bernilai X jika alokasi berhasil, 	     */
/*	  Jika alokasi gagal: I.S = F.S			     */

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertLast(List  *L, address P);
/* I.S   : Sembarang, P sudah dialokasi				*/
/* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

#endif
