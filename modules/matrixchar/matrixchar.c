#include <stdio.h>
#include "matrixchar.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrixChar(int nRows, int nCols, MatrixChar *m) {
    ROW_EFF_MATRIXCHAR(*m) = nRows;
    COL_EFF_MATRIXCHAR(*m) = nCols;
    /* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
    /* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
    /* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixCharIdxValid(int i, int j) {
    return ((i < ROW_CAP_MATRIXCHAR) && (j < COL_CAP_MATRIXCHAR) && (i >= 0) && (j >= 0));
    /* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRowMatrixChar(MatrixChar m) {
    return (ROW_EFF(m) - 1);
    /* Mengirimkan Index baris terbesar m */
}
IdxType getLastIdxColMatrixChar(MatrixChar m) {
    return (COL_EFF(m) - 1);
    /* Mengirimkan Index kolom terbesar m */
}
boolean isIdxEffMatrixChar(MatrixChar m, IdxType i, IdxType j) {
    return ((i >= 0) && (i <= getLastIdxRow(m)) && (j >= 0) && (j <= getLastIdxCol(m)));
    /* Mengirimkan true jika i, j adalah Index efektif bagi m */
}
ElType getElmtDiagonalMatrixChar(MatrixChar m, IdxType i) {
    return ELMT_MATRIXCHAR(m, i, i);
    /* Mengirimkan elemen m(i,i) */
}

/* ********** Assignment  MatrixChar ********** */
void copyMatrixChar(MatrixChar mIn, MatrixChar *mOut) {
    createMatrixChar(ROW_EFF(mIn), COL_EFF(mIn), mOut);

    int i, j;
    for (i = 0; i < ROW_EFF(mIn); i++) {
        for (j = 0; j < COL_EFF(mIn); j++) {
            ELMT_MATRIXCHAR(*mOut, i, j) = ELMT_MATRIXCHAR(mIn, i, j);
        }
    }
    /* Melakukan assignment mOut <- mIn */
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrixChar(MatrixChar *m, int nRow, int nCol) {
    createMatrixChar(nRow, nCol, m);

    int i, j;
    for (i = 0; i < nRow; i++) {
        for (j = 0; j < nCol; j++) {
            scanf("%d", &ELMT_MATRIXCHAR(*m, i, j));
        }
    }
    /* I.S. isIdxValid(nRow,nCol) */
    /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
    /* Proses: Melakukan CreateMatrixChar(m,nRow,nCol) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    /* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
    1 2 3
    4 5 6
    8 9 10 
    */
}
void displayMatrixChar(MatrixChar m) {
    int i, j;

    for (i = 0; i < ROW_EFF(m); i++) {
        for (j = 0; j < COL_EFF(m); j++) {
            printf("%d", ELMT_MATRIXCHAR(m, i, j));
            printf("%s", (j == COL_EFF(m) - 1) ? "\n" : " ");
        }
    }
    /* I.S. m terdefinisi */
    /* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
    dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
    /* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
    /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
    1 2 3
    4 5 6
    8 9 10
    */
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MatrixChar ********** */
boolean isMatrixCharEqual(MatrixChar m1, MatrixChar m2) {
    if ((ROW_EFF(m1) != ROW_EFF(m2)) || (COL_EFF(m1) != COL_EFF(m2))) {
        return false;
    } else {
        int eq = true;
        int i, j;
        for (i = 0; i < ROW_EFF(m1); i++) {
            for (j = 0; j < COL_EFF(m1); j++) {
                if (ELMT_MATRIXCHAR(m1, i, j) != ELMT_MATRIXCHAR(m2, i, j)) {
                    return false;
                }
            }
        }
        return true;
    }
    /* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
    /* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
    /* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
}
boolean isMatrixCharNotEqual(MatrixChar m1, MatrixChar m2) {
    return !isMatrixCharEqual(m1, m2);
    /* Mengirimkan true jika m1 tidak sama dengan m2 */
}
boolean isMatrixCharSizeEqual(MatrixChar m1, MatrixChar m2) {
    return ((ROW_EFF(m1) == ROW_EFF(m2)) && (COL_EFF(m1) == COL_EFF(m2)));
    /* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
    /* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
}

/* ********** Operasi lain ********** */
int countElmtMatrixChar(MatrixChar m) {
    return (ROW_EFF(m) * COL_EFF(m));
    /* Mengirimkan banyaknya elemen m */
}

/* ********** KELOMPOK TEST TERHADAP MatrixChar ********** */
boolean isSquareMatrixChar(MatrixChar m) {
    return (ROW_EFF(m) == COL_EFF(m));
    /* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
}
boolean isSymmetricMatrixChar(MatrixChar m) {
    if (!isSquare(m)) {
        return false;
    } else {
        int i, j;
        for (i = 0; i < ROW_EFF(m); i++) {
            for (j = 0; j < COL_EFF(m); j++) {
                if (ELMT_MATRIXCHAR(m, i, j) != ELMT_MATRIXCHAR(m, j, i)) {
                    return false;
                }
            }
        }
        return true;
    }
    /* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
    dan untuk setiap elemen m, m(i,j)=m(j,i) */
}

MatrixChar transposeMatrixChar(MatrixChar m) {
    MatrixChar transpose;
    createMatrixChar(COL_EFF(m), ROW_EFF(m), &transpose);

    int i, j;
    for (i = 0; i < ROW_EFF(transpose); i++) {
        for (j = 0; j < COL_EFF(transpose); j++) {
            ELMT_MATRIXCHAR(transpose, i, j) = ELMT_MATRIXCHAR(m, j, i);
        }
    }

    return transpose;
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
}
void pTransposeMatrixChar(MatrixChar *m) {
    int i, j;
    MatrixChar copy;
    copyMatrixChar(*m, &copy);
    for (i = 0; i < ROW_EFF(*m); i++) {
        for (j = 0; j < COL_EFF(*m); j++) {
            ELMT_MATRIXCHAR(*m, i, j) = ELMT_MATRIXCHAR(copy, j, i);
        }
    }
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
}