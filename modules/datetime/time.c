#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "boolean.h"
#include "time.h"

/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S) {
    int hourValid = (H >= 0) && (H < 24);
    int minuteValid = (M >= 0) && (M < 60);
    int secondValid = (S >= 0) && (S < 60);

    if ((!hourValid) || (!minuteValid) || (!secondValid)) {
        return false;
    } else {
        return true;
    }
    /* Mengirim true jika H,M,S dapat membentuk T yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int HH, int MM, int SS) {
    if (IsTIMEValid(HH, MM, SS)) {
        Hour(*T) = HH;
        Minute(*T) = MM;
        Second(*T) = SS;
    }
    /* Membentuk sebuah TIME dari komponen-komponennya yang valid */
    /* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T) {
    int h, m, s;
    boolean timeValid = false;

    scanf("%d %d %d", &h, &m, &s);
    timeValid = IsTIMEValid(h, m, s);
    while (!timeValid) {
        printf("Jam tidak valid\n");
        scanf("%d %d %d", &h, &m, &s);
        timeValid = IsTIMEValid(h, m, s);
    }

    CreateTime(T, h, m, s);

    /* I.S. : T tidak terdefinisi */
    /* F.S. : T terdefinisi dan merupakan jam yang valid */
    /* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
    /* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
    diulangi hingga didapatkan jam yang valid. */
    /* Contoh: 
    60 3 4
    Jam tidak valid
    1 3 4
    --> akan terbentuk TIME <1,3,4> */
}
   
void TulisTIME (TIME T) {
    int h = Hour(T);
    int m = Minute(T);
    int s = Second(T);

    printf("%.2d:%.2d:%.2d", h, m, s);
    /* I.S. : T sembarang */
    /* F.S. : Nilai T ditulis dg format HH:MM:SS */
    /* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
}

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (TIME T) {
    int hourSec = Hour(T) * 3600;
    int minuteSec = Minute(T) * 60;
    int sec = Second(T);

    return (long) (hourSec + minuteSec + sec);
    /* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
    /* Rumus : detik = 3600*HH + 60*MM + SS */
    /* Nilai maksimum = 3600*23+59*60+59 */
}

TIME DetikToTIME (long N) {
    long newN = N;
    while (newN < 0) {
        newN += 86400;
    }
    int N1 = newN % 86400;

    int sec = N1 % 60;
    int min = ((N1 - sec) / 60) % 60;
    int hour = (N1 / 3600);

    TIME T;
    Hour(T) = hour; 
    Minute(T) = min; 
    Second(T) = sec; 

    return T;
    /* Mengirim  konversi detik ke TIME */
    /* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
    mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
    N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
} 

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2) {
    return (TIMEToDetik(T1) == TIMEToDetik(T2));
    /* Mengirimkan true jika T1=T2, false jika tidak */
}
boolean TNEQ (TIME T1, TIME T2) {
    return !(TIMEToDetik(T1) == TIMEToDetik(T2));
    /* Mengirimkan true jika T1 tidak sama dengan T2 */
}
boolean TLT (TIME T1, TIME T2) {
    return (TIMEToDetik(T1) < TIMEToDetik(T2));
    /* Mengirimkan true jika T1<T2, false jika tidak */
}
boolean TGT (TIME T1, TIME T2) {
    return (TIMEToDetik(T1) > TIMEToDetik(T2));
    /* Mengirimkan true jika T1>T2, false jika tidak */
}
/* *** Operator aritmatika TIME *** */
TIME NextDetik (TIME T) {
    long sec = TIMEToDetik(T);
    TIME newTime = DetikToTIME(sec + 1);

    return newTime;
    /* Mengirim 1 detik setelah T dalam bentuk TIME */
}
TIME NextNDetik (TIME T, int N) {
    long sec = TIMEToDetik(T);
    TIME newTime = DetikToTIME(sec + N);

    return newTime;
    /* Mengirim N detik setelah T dalam bentuk TIME */
}
TIME PrevDetik (TIME T) {
    long sec = TIMEToDetik(T);
    TIME newTime = DetikToTIME(sec - 1);

    return newTime;
    /* Mengirim 1 detik sebelum T dalam bentuk TIME */
}
TIME PrevNDetik (TIME T, int N) {
    long sec = TIMEToDetik(T);
    TIME newTime = DetikToTIME(sec - N);

    return newTime;
    /* Mengirim N detik sebelum T dalam bentuk TIME */
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh) {
    long secStart = TIMEToDetik(TAw);
    long secEnd = TIMEToDetik(TAkh);
    if (secStart <= secEnd) {
        return (secEnd - secStart);
    } else {
        return (86400 - (secStart - secEnd));
    }
    /* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
    /* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
}