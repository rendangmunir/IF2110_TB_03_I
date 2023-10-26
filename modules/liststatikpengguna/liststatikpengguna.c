#include <stdio.h>
#include "liststatikpengguna.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatikPengguna(ListStatikPengguna *l) {
    l->Neff = 0;
}
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
/* Proses: Inisialisasi semua elemen List l dengan MARK */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthPengguna(ListStatikPengguna l) {
    return l.Neff;
}
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  

// /* *** Selektor INDEKS *** */
// IdxType getFirstIdxPengguna(ListStatikPengguna l) {

// }
// /* Prekondisi : List l tidak kosong */
// /* Mengirimkan indeks elemen l pertama */
// IdxType getLastIdxPengguna(ListStatikPengguna l) {

// }
// /* Prekondisi : List l tidak kosong */
// /* Mengirimkan indeks elemen l terakhir */

// /* ********** Test Indeks yang valid ********** */
// boolean isIdxValidPengguna(ListStatikPengguna l, IdxType i);
// /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
// /* yaitu antara indeks yang terdefinisi utk container*/
// boolean isIdxEffPengguna(ListStatikPengguna l, IdxType i);
// /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
// /* yaitu antara 0..length(l)-1 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyPengguna(ListStatikPengguna l) {
    return (l.Neff == 0);
}
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isFullPengguna(ListStatikPengguna l) {
    return (l.Neff == CAPACITYPENGGUNA);
}
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
// void readList(ListStatik *l) {
//     int n;
//     do {
//         scanf("%d", &n);
//     } while (!((n >= 0) && (n <= CAPACITY)));

//     CreateListStatik(l);
//     int i;
//     for (i = 0; i < n; i++) {
//         ElType x;
//         scanf("%d", &x);

//         ELMT(*l, i) = x; 
//     }
//     /* I.S. l sembarang */
//     /* F.S. List l terdefinisi */
//     /* Proses: membaca banyaknya elemen l dan mengisi nilainya */
//     /* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
//     /*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
//     /*    Jika n tidak valid, tidak diberikan pesan kesalahan */
//     /* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
//             Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
//     /*    Jika n = 0; hanya terbentuk List kosong */
// }
// void printList(ListStatik l) {
//     if (listLength(l) == 0) {
//         printf("[]");
//     } else {
//         printf("[");
//         int i;
//         for (i = 0; i < listLength(l) - 1; i++) {
//             printf("%d,", ELMT(l, i));
//         }
//         printf("%d]", ELMT(l, (listLength(l) - 1)));
//     }
//     /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
//     siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
//     karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
//     /* I.S. l boleh kosong */
//     /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
//     /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
//     /* Jika List kosong : menulis [] */
// }

// /* ********** OPERATOR ARITMATIKA ********** */
// /* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
// ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus) {
//     if ((listLength(l1) == listLength(l2)) && (listLength(l1) != 0)) {
//         ListStatik l3;
//         CreateListStatik(&l3);
        
//         int i;
//         for (i = 0; i < listLength(l1); i++) {
//             ELMT(l3, i) = (plus) ? ELMT(l1, i) + ELMT(l2, i) : ELMT(l1, i) - ELMT(l2, i);
//         }

//         return l3;
//     }
//     /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
//     /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
//         indeks yang sama dijumlahkan */
//     /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
//         elemen l2 pada indeks yang sama */
// }

// /* ********** OPERATOR RELASIONAL ********** */
// /* *** Operasi pembandingan List: *** */
// boolean isListEqual(ListStatik l1, ListStatik l2) {
//     int isEqual = true;
//     if (listLength(l1) == listLength(l2)) {
//         int i = 0;
//         while ((isEqual) && (i < listLength(l1))) {
//             if (ELMT(l1, i) != ELMT(l2, i)) {
//                 isEqual = false;
//             }
//             i += 1;
//         }
//     } else {
//         isEqual = false;
//     }

//     return isEqual;
//     /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
//     elemennya sama */
// }

// /* ********** SEARCHING ********** */
// /* ***  Perhatian : List boleh kosong!! *** */
// int indexOf(ListStatikPengguna l, ElType val) {
//     int i = 0;
//     int found = false;
//     int index = -1;

//     while ((found == false) && (i < listLength(l))) {
//         if (ELMT(l, i) == val) {
//             index = i;
//             found = true;
//         }
//         i += 1;
//     }

//     return (found) ? index : IDX_UNDEF;

//     /* Search apakah ada elemen List l yang bernilai val */
//     /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
//     /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
//     /* Skema Searching yang digunakan bebas */
// }

int indexOfUser(ListStatikPengguna l, Word name) {
    int i = 0;
    boolean found = false;

    while (i < listLengthPengguna(l) && !found) {
        ElTypePengguna el = ELMTPengguna(l, i);
        if (WordEqual(name, el.Nama)) {
            found = true;
        } else {
            i += 1;
        }
    }

    if (found) {
        return i;
    } else {
        return IDX_UNDEF;
    }
}

// /* ********** NILAI EKSTREM ********** */
// void extremeValues(ListStatik l, ElType *max, ElType *min) {
//     *max = ELMT(l, 0);
//     *min = ELMT(l, 0);

//     int i;
//     for (i = 0; i < listLength(l); i++) {
//         if (ELMT(l, i) > *max) {
//             *max = ELMT(l, i);
//         }

//         if (ELMT(l, i) < *min) {
//             *min = ELMT(l, i);
//         }
//     }
//     /* I.S. List l tidak kosong */
//     /* F.S. Max berisi nilai terbesar dalam l;
//             Min berisi nilai terkecil dalam l */
// }

// /* ********** MENAMBAH ELEMEN ********** */
// /* *** Menambahkan elemen terakhir *** */
// void insertFirst(ListStatik *l, ElType val) {
//     if (!isFull(*l)) {
//         int i;
//         for (i = listLength(*l) - 1; i >= 0; i--) {
//             ELMT(*l, i + 1) = ELMT(*l, i);
//         }

//         ELMT(*l, 0) = val;
//     }
//     /* Proses: Menambahkan val sebagai elemen pertama List */
//     /* I.S. List l boleh kosong, tetapi tidak penuh */
//     /* F.S. val adalah elemen pertama l yang baru */
// }
// /* *** Menambahkan elemen pada index tertentu *** */
// void insertAt(ListStatik *l, ElType val, IdxType idx) {
//     if ((!isFull(*l)) && (isIdxValid(*l, idx))) {
//         int i;
//         for (i = listLength(*l) - 1; i >= idx; i--) {
//             ELMT(*l, i + 1) = ELMT(*l, i);
//         }

//         ELMT(*l, idx) = val;
//     }
//     /* Proses: Menambahkan val sebagai elemen pada index idx List */
//     /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
//     /* F.S. val adalah elemen yang disisipkan pada index idx l */
// }
/* *** Menambahkan elemen terakhir *** */
void insertLastPengguna(ListStatikPengguna *l, ElTypePengguna user) {
    if ((!isFullPengguna(*l))) {
        ELMTPengguna(*l, listLengthPengguna(*l)) = user;
        l->Neff += 1;
    }
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
}

// /* ********** MENGHAPUS ELEMEN ********** */
// /* *** Menghapus elemen pertama *** */
// void deleteFirst(ListStatik *l, ElType *val) {
//     int n = listLength(*l);
//     int temp = ELMT(*l, 0); 
//     ELMT(*l, 0) = MARK;

//     if (!isEmpty(*l)) {
//         *val = temp;

//         int i;
//         for (i = 1; i < n; i++) {
//             ELMT(*l, i - 1) = ELMT(*l, i);
//         }

//         ELMT(*l, n - 1) = MARK;
//     }
//     /* Proses : Menghapus elemen pertama List */
//     /* I.S. List tidak kosong */
//     /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
//     /*      Banyaknya elemen List berkurang satu */
//     /*      List l mungkin menjadi kosong */
// }
// /* *** Menghapus elemen pada index tertentu *** */
// void deleteAt(ListStatik *l, ElType *val, IdxType idx) {
//     if (isIdxValid(*l, idx)) {
//         int temp = ELMT(*l, idx);
//         int n = listLength(*l);
//         ELMT(*l, idx) = MARK;
//         if ((!isEmpty(*l))) {
//             *val = temp;
//             int i;
//             for (i = idx + 1; i < n; i++) {
//                 ELMT(*l, i - 1) = ELMT(*l, i);
//             }
//             ELMT(*l, n - 1) = MARK;
//         }
//     }
    
//     /* Proses : Menghapus elemen pada index idx List */
//     /* I.S. List tidak kosong, idx adalah index yang valid di l */
//     /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
//     /*      Banyaknya elemen List berkurang satu */
//     /*      List l mungkin menjadi kosong */
// }
// /* *** Menghapus elemen terakhir *** */
// void deleteLast(ListStatik *l, ElType *val) {
//     if (!isEmpty(*l)) {
//         *val = ELMT(*l, listLength(*l) - 1); 
//         ELMT(*l, listLength(*l) - 1) = MARK;
//     }
//     /* Proses : Menghapus elemen terakhir List */
//     /* I.S. List tidak kosong */
//     /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
//     /*      Banyaknya elemen List berkurang satu */
//     /*      List l mungkin menjadi kosong */
// }

// /* ********** SORTING ********** */
// void sortList(ListStatik *l, boolean asc) {
//     int i;
//     for (i = 1; i < listLength(*l); i++) {
//         int j = i;
//         while ((j > 0) && (ELMT(*l, j - 1) > ELMT(*l, j))) {
//             int temp = ELMT(*l, j - 1);
//             ELMT(*l, j - 1) = ELMT(*l, j);
//             ELMT(*l, j) = temp;

//             j += -1;
//         }
//     }

//     if (!asc) {
//         ListStatik lRev;
//         int k;
//         for (k = 0; k < listLength(*l); k++) {
//             ELMT(lRev, k) = ELMT(*l, k);
//         }
//         int m;
//         for (m = 0; m < listLength(*l); m++) {
//             ELMT(*l, m) = ELMT(lRev, (listLength(*l) - m - 1));
//         }
//     }
//     /* I.S. l boleh kosong */
//     /* F.S. Jika asc = true, l terurut membesar */
//     /*      Jika asc = false, l terurut mengecil */
//     /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
//     algoritma bebas */
// }
