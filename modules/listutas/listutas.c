#include "listutas.h"
#include <stdlib.h>

Address newNodeUtas(Word author, int index, DATETIME time, Word text){
    Address p = (Address) malloc (sizeof(nodeUtas));
    if (p != NULL){
        p->author = author;
        p->index = index;
        p->datetime = time;
        p->text = text;
        p->next = NULL;
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
void insertFirstUtas(List *l, EltypeUtas* node)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
{
    Address newUtas,p;
    int idx;
    // if (newUtas != NULL){
    //     }
    p = *l;
    node->next = *l;
    *l = node;

    // Set idx
    p = NEXT(node);
    idx = 2;
    while(p != NULL){
        INDEX(p) = idx;
        p = NEXT(p);
        idx++;
    }
}
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastUtas(List *l, EltypeUtas* node)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if(isEmptyUtas(*l)){
        insertFirstUtas(l, node);
    }else{
        INDEX(node) = lengthUtas(*l) + 1;
        Address last = *l;

        while(NEXT(last) != NULL){
            last = NEXT(last);
        }
        NEXT(last) = node;
    }
}

void insertAtUtas(List *l, EltypeUtas* node, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    Address loc;
    int i;
    if(idx==1){
        insertFirstUtas(l, node);
    }
    else{
        INDEX(node) = idx;
        loc = *l;
        while(INDEX(loc) < idx-1){
            loc = NEXT(loc);
        }
        NEXT(node) = NEXT(loc);
        NEXT(loc) = node;

        i = idx + 1;
        loc = NEXT(node);
        while(loc != NULL){
            INDEX(loc) = i;
            i++;
            loc = NEXT(loc);
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
    *l = NEXT(p);
    free(p);

    Address node = *l;
    while(node != NULL){
        INDEX(node)--;
        node = NEXT(node);
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

void deleteAtUtas(List *l, int idx)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if(idx==1){
        deleteFirstUtas(l);
    }
    else{
        Address p = *l;
        Address del;
        while (INDEX(p) < idx-1){
            p = NEXT(p);
        }
        del = NEXT(p);
        NEXT(p) = NEXT(del);
        free(del);

        Address node = NEXT(p);
        while(node != NULL){
            INDEX(node)--;
            node = NEXT(node);
        }
    }
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
        while (p != NULL){
            i++;
            p = NEXT(p);
        }
        return i;
    }
}

/****************** PROSES TERHADAP LIST ******************/

int IDUtasTerakhir(ListDinKicauan listKicau)
/*Mengirim idUtasTerakhir dari list kicauan*/
{
    int neff =  listKicau.nEff;
    int count = 1;
    for(int i =0; i <neff;i++){
        if(listKicau.buffer[i].idUtas > count){
            count = listKicau.buffer[i].idUtas;
        }
    }
    return count;
}