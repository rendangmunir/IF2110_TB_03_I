/* File : listutas.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* EltypeUtas adalah integer */

#ifndef listutas_H
#define listutas_H

#include "boolean.h"
#include "../wordmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"
#include "../datetime/datetime.h"
#include "../listdinkicauan/listdinkicauan.h"

/* Definisi Utas : */
// typedef struct nodeUtas* Address;

// typedef struct nodeUtas {
//     int index;
//     Word author;
//     DATETIME datetime;
//     Word text;

//     Address next;
// } nodeUtas;
// typedef nodeUtas EltypeUtas;

// #define INDEX(p) (p)->index
// #define AUTHOR(P) (P)->author
// #define DATETIME(p) (p)->datetime
// #define TEXT(P) (P)->text
// #define NEXT(p) (p)->next

Address newNodeUtas();

// typedef Address List;
/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

#define IDX_UNDEF_UTAS (-1)
// #define FIRST(l) (l)
// #define KICAU(l) (l)->kicau
/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
// void CreateList(List *l, Kicauan kicau);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** TEST LIST KOSONG ******************/
boolean isEmptyUtas(List l);
/* Mengirim true jika list kosong */

/****************** GETTER SETTER ******************/
EltypeUtas getUtas(List l, int idx);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */

void setUtas(List *l, int idx, EltypeUtas val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOfUtas(List l, EltypeUtas val);
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstUtas(List *l, EltypeUtas val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastUtas(List *l, EltypeUtas val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void insertAtUtas(List *l, EltypeUtas val, int idx);
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstUtas(List *l);
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
void deleteLastUtas(List *l);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */

void deleteAtUtas(List *l, int idx);
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */


/****************** PROSES SEMUA ELEMEN LIST ******************/
int lengthUtas(List l);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

int IDUtasTerakhir(ListDinKicauan listKicau);
/*Mengirim idUtasTerakhir dari list kicauan*/
/****************** PROSES TERHADAP LIST ******************/
#endif
