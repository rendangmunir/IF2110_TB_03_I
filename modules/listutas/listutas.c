#include "listutas.h"
#include <stdlib.h>

Address newNodeUtas(){
    Address p = (Address) malloc (sizeof(nodeUtas));
    if (p != NULL){
        NEXT(p) = NULL;
    }
    return p;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
// void CreateList(List *l, Kicauan kicau)
// /* I.S. sembarang             */
// /* F.S. Terbentuk list kosong */
// {
//     KICAU(*l) = kicau;
//     NEXT(*l) = NULL;
// }

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateUtas(EltypeUtas *utas, Word author, DATETIME datetime, Word text)
/* I.S. sembarang             */
/* F.S. Terbentuk Utas dengan index Undeff */
{
    (utas)->index = IDX_UNDEF_UTAS;
    (utas)->author = author;
    (utas)->datetime = datetime;
    (utas)->text = text;
}
/****************** TEST LIST KOSONG ******************/
boolean isEmptyUtas(List l)
/* Mengirim true jika list kosong */
{
    return l == NULL;
}

/****************** GETTER SETTER ******************/
// EltypeUtas getUtas(List l, int idx)
// /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
// /* F.S. Mengembalikan nilai elemen l pada indeks idx */
// {
//     Address p = l;
//     while(INDEX(p)<idx){
//         p = NEXT(p);
//     }
//     return INFO_UTAS(p);
// }

void setUtas(List *l, int idx, EltypeUtas val);
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */

// int indexOfUtas(List l, EltypeUtas val)
// /* I.S. l, val terdefinisi */
// /* F.S. Mencari apakah ada elemen list l yang bernilai val */
// /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
// /* Mengembalikan IDX_UNDEF jika tidak ditemukan */
// {
//     int i;
//     i = 1;
//     Address p = l;
//     boolean found = false;
//     while(p != NULL && !found){
//         if(INFO(p) == val){
//             found=true;
//         }
//         else{
//             i++;
//             p = NEXT(p);
//         }
//     }
//     if(found){
//         return i;
//     }
//     else{
//         return IDX_UNDEF_UTAS;
//     }
// }

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstUtas(List *l, EltypeUtas val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
{
    Address newUtas,p;
    int idx;
    newUtas = newNodeUtas(val);
    if (newUtas != NULL){
        p = *l;
        NEXT(newUtas) = *l;
        *l = newUtas;
        // Set idx
        idx = 1;
        while(p != NULL){
            INDEX(p) = idx;
            p = NEXT(p);
            idx++;
        }
    }
}
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastUtas(List *l, EltypeUtas val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(isEmptyUtas(*l)){
        insertFirstUtas(l,val);
    }else{
        Address p = newNodeUtas(val);
        INDEX(p) = lengthUtas(*l);
        Address last = *l;
        if(p != NULL){
            while(NEXT(last) != NULL){
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAtUtas(List *l, EltypeUtas val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address p, loc;
    int i;
    if(idx==1){
        insertFirstUtas(l, val);
    }
    else{
        p = newNodeUtas(val);
        INDEX(p) = idx;
        if(p != NULL){
            loc = *l;
            while(INDEX(loc) <idx-1){
                loc = NEXT(loc);
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
            loc = NEXT(loc);
            i = idx;
            while(loc != NULL){
                INDEX(loc) = i;
                i++;
                loc = NEXT(loc);
            }
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstUtas(List *l)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = *l;
    NEXT(*l) = NEXT(p);
    free(p);
    p = NEXT(p);
    while(p != NULL){
        INDEX(p)--;
        p = NEXT(p);
    }
}
void deleteLastUtas(List *l)
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
    free(p);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
int lengthUtas(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    if(isEmptyUtas(l)){
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

