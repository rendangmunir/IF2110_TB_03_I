#include "listutas.h"
#include <stdlib.h>

Address newNodeUtas(EltypeUtas val){
    Address p = (Address) malloc (sizeof(Utas));
    if (p != NULL){
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l, Kicauan kicau)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    KICAU(*l) = kicau;
    NEXT(*l) = NULL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateUtas(EltypeUtas *utas, Word author, DATETIME datetime, Word text)
/* I.S. sembarang             */
/* F.S. Terbentuk Utas dengan index Undeff */
{
    (utas)->index = IDX_UNDEF;
    (utas)->author = author;
    (utas)->datetime = datetime;
    (utas)->text = text; 
}
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong */
{
    return NEXT(l) == NULL;
}

/****************** GETTER SETTER ******************/
EltypeUtas getUtas(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i = 0;
    Address p = l;
    while(i<idx){
        i++;
        p = NEXT(p);
    }
    return INFO(p);
}

void setUtas(List *l, int idx, EltypeUtas val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

int indexOf(List l, EltypeUtas val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    int i;
    i = 0;
    Address p = l;
    boolean found = false;
    while(p != NULL && !found){
        if(INFO(p) == val){
            found=true;
        }
        else{
            i++;
            p = NEXT(p);
        }
    }
    if(found){
        return i;
    }
    else{
        return IDX_UNDEF;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, EltypeUtas val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
{
    Address p,loc;
    p = newNodeUtas(val);
    if (p != NULL){
        loc = *l;
        NEXT(p) = NEXT(loc);
        NEXT(loc) = p;
    }
}
/* Jika alokasi gagal: I.S.= F.S. */

void insertLast(List *l, EltypeUtas val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(isEmpty(*l)){
        insertFirst(l,val);
    }else{
        Address p = newNodeUtas(val);
        Address last = *l;
        if(p != NULL){
            while(NEXT(last) != NULL){
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(List *l, EltypeUtas val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    int cnt = 0;
    Address p, loc;
    if(idx==0){
        insertFirst(l, val);
    }
    else{
        p = newNodeUtas(val);
        if(p != NULL){
            loc = *l;
            while(cnt<idx-1){
                cnt++;
                loc = NEXT(loc);
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, EltypeUtas *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = *l;
    p = NEXT(p);
    NEXT(*l) = NEXT(p);
    free(p);
}
void deleteLast(List *l, EltypeUtas *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    Address p = *l;
    Address q = NULL;
    while(NEXT(p) != NULL){
        q = p;
        p = NEXT(p);
    }
    if(q==NULL){
        *l = NULL;
    }
    else{
        NEXT(q) = NULL;
    }
    *val = INFO(p);
    free(p);
}

void deleteAt(List *l, int idx, EltypeUtas *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if (idx == 0){
        deleteFirst(l, val);
    }else{
        Address p = *l;
        Address q;
        int i = 0;
        while (i < idx-1){
            p = NEXT(p);
            i++;
        }
        q = NEXT(p);
        *val = INFO(q);
        NEXT(p) = NEXT(q);
        free(q);
    }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l);
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int length(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    if(isEmpty(l)){
        return 0;
    }else{
        int i = 0;
        Address p = l;
        while (NEXT(p) != NULL){
            i++;
            p = NEXT(p);
        }
        return i;
    }
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) ;
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
