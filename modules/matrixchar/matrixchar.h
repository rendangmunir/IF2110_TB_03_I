/* ********** Definisi TYPE MatrixChar dengan Index dan elemen integer ********** */

#ifndef MATRIXCHAR_H
#define MATRIXCHAR_H

#include "boolean.h"
#include "../wordmachine/charmachine.h"
#include "../wordmachine/wordmachine.h"

/* Ukuran maksimum baris dan kolom */
#define ROW_CAP_MATRIXCHAR 100
#define COL_CAP_MATRIXCHAR 100

typedef int IdxType; /* Index baris, kolom */
typedef char ElTypeMatrixChar;
typedef struct
{
   ElTypeMatrixChar mem[ROW_CAP_MATRIXCHAR][COL_CAP_MATRIXCHAR];
   int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
   int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MatrixChar;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrixChar(int nRows, int nCols, MatrixChar *m);
/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define ROW_EFF_MATRIXCHAR(M) (M).rowEff
#define COL_EFF_MATRIXCHAR(M) (M).colEff
#define ELMT_MATRIXCHAR(M, i, j) (M).mem[(i)][(j)]

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixCharIdxValid(int i, int j);
/* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRowMatrixChar(MatrixChar m);
/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxColMatrixChar(MatrixChar m);
/* Mengirimkan Index kolom terbesar m */
boolean isIdxEffMatrixChar(MatrixChar m, IdxType i, IdxType j);
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
ElTypeMatrixChar getElmtDiagonalMatrixChar(MatrixChar m, IdxType i);
/* Mengirimkan elemen m(i,i) */

/* ********** Assignment  MatrixChar ********** */
void copyMatrixChar(MatrixChar mIn, MatrixChar *mOut);
/* Melakukan assignment mOut <- mIn */

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrixChar(MatrixChar *m, int nRow, int nCol);
/* I.S. isIdxValid(nRow,nCol) */
/* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
/* Proses: Melakukan CreateMatrixChar(m,nRow,nCol) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void displayMatrixChar(MatrixChar m);
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
/* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MatrixChar ********** */
boolean isMatrixCharEqual(MatrixChar m1, MatrixChar m2);
/* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
/* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
/* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
boolean isMatrixCharNotEqual(MatrixChar m1, MatrixChar m2);
/* Mengirimkan true jika m1 tidak sama dengan m2 */
boolean isMatrixCharSizeEqual(MatrixChar m1, MatrixChar m2);
/* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
/* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */

/* ********** Operasi lain ********** */
int countElmtMatrixChar(MatrixChar m);
/* Mengirimkan banyaknya elemen m */

/* ********** KELOMPOK TEST TERHADAP MatrixChar ********** */
boolean isSquareMatrixChar(MatrixChar m);
/* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
boolean isSymmetricMatrixChar(MatrixChar m);
/* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
   dan untuk setiap elemen m, m(i,j)=m(j,i) */
MatrixChar transposeMatrixChar(MatrixChar m);
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
void pTransposeMatrixChar(MatrixChar *m);
/* I.S. m terdefinisi dan IsSquare(m) */
/* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */

#endif