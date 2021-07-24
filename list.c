/* File :  list1.c   					*/
/* Desk :  body list  berkait dgn representasi fisik    */
/*         pointer; 					*/
/* 	   Representasi address dgn pointer 		*/
/*	   InfoList adalah integer			*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* body dari List1.h   */

#ifndef list1_C
#define list1_C 

#include "boolean.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List  L)                        
{  /*  Mengirim true jika List kosong  */

   	return(First(L)==Nil);	
}

/* Pembuatan  List Kosong  */
void CreateList(List *L)
{  /* I.S  :  Sembarang    		*/
   /* F.S  :  Terbentuk  List kosong  	*/
   First(*L)=Nil;
}

/* ********  MANAJEMEN MEMORY  ********* */
address Alokasi(InfoList  X)
{/* Mengirimkan  address  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
   address P;
   P=(address)malloc(sizeof(ElmtList));
   if(P!=Nil) { /* Berhasil  */
         Info(P)=X;
	 Next(P)=Nil;
   }
   return P;	   
}

void Dealokasi(address *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian address P */
    Next(*P)=Nil; 	
    free(*P);	
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

void InsVLast(List *L, InfoList X)
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen list di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */	
  /*	    Jika alokasi gagal: I.S = F.S		       */
      	
     address P=Alokasi(X);
     if(P!=Nil)
     {  InsertLast(&(*L),P);
         }
}

/* *** Penghapusan Elemen  ***  */

void DelVFirst(List *L, InfoList *X)
{ /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  address  P;
  
  DelFirst(&(*L),&P); /* Hapus elemem pertama, blm didealokasi */
  *X=Info(P); 		/* info dari First disimpan di X       */
  Dealokasi(&P);	  
}	

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirst(List *L, address P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-address P, sebagai  */
  /*         elemen pertama				*/
    Next(P)=First(*L);
    First(*L)=P;
}

void InsertLast(List  *L, address P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

      address Last;
      if(ListEmpty(*L)) { /* Jika kosong, Insert elemen pertama */
	   InsertFirst(&(*L),P);     
      }
      else { /* tdk kosong */
	    Last=First(*L);  
            while(Next(Last)!=Nil)  { /* menuju ke last */
	          Last=Next(Last);
	    } /* Next(Last)==Nil */
	  
	  Next(Last)=P;	  
      }
}

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirst (List *L, address *P)
{ /* I.S   : List tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
  /*         Elemen List berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */
          
      *P=First(*L);
      First(*L)=Next(First(*L));
      Next(*P)=Nil;
    
 }

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(List L, char **A)
{ /* I.S   : List mungkin kosong 	*/
  /* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
  /*         elemen list di-print			  	   */
  /*         Jika list kosong, hanya menuliskan "List Kosong"	   */
  address P=First(L);
  
  if( P==Nil) { 
  	  printf("List Kosong !\n");
  } else { /* List tidak kosong */
  		int j = 1;
	    do {
		 	printf("  %d. %s (%s)\n", j++, A[Info(P).Disease - 1], P->info.Category);
			P = Next(P);
	    } while(P != Nil);
	 }
}

#endif
