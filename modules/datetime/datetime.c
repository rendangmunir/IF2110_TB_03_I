#include <stdio.h>
#include <math.h>
#include <time.h>

#include "datetime.h"

int GetMaxDay(int M, int Y){
    if (M <= 7) {
        if (M == 2) {
            if (Y % 400 == 0) {
                return 29;
            } else if (Y % 100 == 0) {
                return 28;
            } else if (Y % 4 == 0) {
                return 29;
            } else {
                return 28;
            }
        } else {
            return ((M % 2) == 0) ? 30 : 31; 
        }
    } else {
        return ((M % 2) == 0) ? 31 : 30;
    }
    /* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
    /* Prekondisi: 1 <= M <= 12*/
    /* Hint: Perhatikan Leap Year. Leap Year adalah tahun dengan 29 hari pada bulan Februari */
    /* Aturan Leap Year: */
    /* 1. Jika angka tahun itu habis dibagi 400, maka tahun itu sudah pasti tahun kabisat. 8*/
    /* 2. Jika angka tahun itu tidak habis dibagi 400 tetapi habis dibagi 100, maka tahun itu sudah pasti bukan merupakan tahun kabisat. */
    /* 3. Jika angka tahun itu tidak habis dibagi 400, tidak habis dibagi 100 akan tetapi habis dibagi 4, maka tahun itu merupakan tahun kabisat. */
    /* 4. Jika angka tahun tidak habis dibagi 400, tidak habis dibagi 100, dan tidak habis dibagi 4, maka tahun tersebut bukan merupakan tahun kabisat. */
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s){
    if (!IsTIMEValid(h, m, s)) {
        return false;
    }
    if ((M > 12) || (M < 1)) {
        return false;
    }
    if ((D < 0) || (D > GetMaxDay(M, Y))) {
        return false;
    }
    return true;
    /* Mengirim true jika D,M,Y,h,m,s dapat membentuk D yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah DATETIME */
}

/* *** Konstruktor: Membentuk sebuah DATETIME dari komponen-komponennya *** */
void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss){
    if (IsDATETIMEValid(DD, MM, YYYY, hh, mm, ss)) {
        TIME t;
        
        Day(*D) = DD;
        Month(*D) = MM;
        Year(*D) = YYYY;
        CreateTime(&t, hh, mm, ss);
        Time(*D) = t;
    }
    /* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
    /* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaDATETIME(DATETIME *D){
    int d, m, y, hour, min, sec;

    scanf("%d %d %d %d %d %d", &d, &m, &y, &hour, &min, &sec);
    while (!IsDATETIMEValid(d, m, y, hour, min, sec)) {
        printf("DATETIME tidak valid\n");
        scanf("%d %d %d %d %d %d", &d, &m, &y, &hour, &min, &sec);
    }

    CreateDATETIME(D, d, m, y, hour, min, sec);
    /* I.S. : D tidak terdefinisi */
    /* F.S. : D terdefinisi dan merupakan DATETIME yang valid */
    /* Proses : mengulangi membaca komponen DD, MM, YY, h, m, s sehingga membentuk D */
    /* yang valid. Tidak mungkin menghasilkan D yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen DD, MM, YY, h, m, s
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika DATETIME tidak valid maka diberikan pesan: "DATETIME tidak valid", dan pembacaan
        diulangi hingga didapatkan DATETIME yang valid. */
    /* Contoh:
        32 13 2023 12 34 56
        DATETIME tidak valid
        31 12 2023 12 34 56
        --> akan terbentuk DATETIME <31,12,2023,12,34,56> */
}

void TulisDATETIME(DATETIME D){
    int d = Day(D);
    int m = Month(D);
    int y = Year(D);

    int hour = Hour(Time(D));
    int min = Minute(Time(D));
    int sec = Second(Time(D));
    printf("%d/%d/%d %d:%d:%d", d, m, y, hour, min, sec);
    /* I.S. : D sembarang */
    /* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */
    /* Proses : menulis nilai setiap komponen D ke layar dalam format DD/MM/YYYY HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok operasi relasional terhadap DATETIME *** */
boolean DEQ(DATETIME D1, DATETIME D2){
    int sameDay = (Day(D1) == Day(D2));
    int sameMonth = (Month(D1) == Month(D2));
    int sameYear = (Year(D1) == Year(D2));

    int sameHour = (Hour(Time(D1)) == Hour(Time(D2)));
    int sameMin = (Minute(Time(D1)) == Minute(Time(D2)));
    int sameSec = (Second(Time(D1)) == Second(Time(D2)));

    return (sameDay && sameMonth && sameYear && sameHour && sameMin && sameSec);
    /* Mengirimkan true jika D1=D2, false jika tidak */
}
boolean DNEQ(DATETIME D1, DATETIME D2){
    int sameDay = (Day(D1) == Day(D2));
    int sameMonth = (Month(D1) == Month(D2));
    int sameYear = (Year(D1) == Year(D2));

    int sameHour = (Hour(Time(D1)) == Hour(Time(D2)));
    int sameMin = (Minute(Time(D1)) == Minute(Time(D2)));
    int sameSec = (Second(Time(D1)) == Second(Time(D2)));

    return !(sameDay && sameMonth && sameYear && sameHour && sameMin && sameSec);
    /* Mengirimkan true jika D1 tidak sama dengan D2 */
}
boolean DLT(DATETIME D1, DATETIME D2){
    int d1 = Day(D1);
    int m1 = Month(D1);
    int y1 = Year(D1);

    int d2 = Day(D2);
    int m2 = Month(D2);
    int y2 = Year(D2);

    if (y1 < y2) {
        return true;
    } else if (y1 > y2) {
        return false;
    } else {
        if (m1 < m2) {
        return true;
        } else if (m1 > m2) {
            return false;
        } else {
            if (d1 < d2) {
                return true;
            } else if (d1 > d2) {
                return false;
            } else {
                return TLT(Time(D1), Time(D2));
            }
        }
    }

    /* Mengirimkan true jika D1<D2, false jika tidak */
}
boolean DGT(DATETIME D1, DATETIME D2){
    return !(DLT(D1, D2));
    /* Mengirimkan true jika D1>D2, false jika tidak */
}
DATETIME DATETIMENextNDetik(DATETIME D, int N){
    int d = Day(D);
    int m = Month(D);
    int y = Year(D);

    int hour = Hour(Time(D));
    int min = Minute(Time(D));
    int sec = Second(Time(D));

    // Algorithm
    int changeDay = (N > (86400 - TIMEToDetik(Time(D))));
    if (changeDay) {
        N += - (86400 - TIMEToDetik(Time(D)));
        if ((m == 12) && (d == 31)) {
            m = 1;
            d = 0;
            y += 1;
        } else if (d == GetMaxDay(m, y)) {
            d = 0;
            m += 1;
        }

        d += 1;
        hour = 0;
        min = 0;
        sec = 0;

        while (N > 0) {
            if (N >= 86400) {
                N += - 86400;
                if ((m == 12) && (d == 31)) {
                    m = 1;
                    d = 0;
                    y += 1;
                } else if (d == GetMaxDay(m, y)) {
                    d = 0;
                    m += 1;
                }

                d += 1;
                hour = 0;
                min = 0;
                sec = 0;
            } else {
                TIME t = DetikToTIME(N); 
        
                DATETIME dt;
                CreateDATETIME(&dt, d, m, y, Hour(t), Minute(t), Second(t));
                return dt; 
            }
        }
    } else {
        TIME t = DetikToTIME(TIMEToDetik(Time(D)) + N); 
        
        DATETIME dt;
        CreateDATETIME(&dt, d, m, y, Hour(t), Minute(t), Second(t));
        return dt;    
    }
    /* Mengirim salinan D dengan detik ditambah N */
}

void addDay(int *d, int *m, int *y, int *hour, int *min, int *sec) {
    if ((*m == 12) && (*d == 31)) {
        *m = 1;
        *d = 0;
        *y += 1;
    } else if (*d == GetMaxDay(*m, *y)) {
        *d = 0;
        *m += 1;
    }

    *d += 1;
    *hour = 0;
    *min = 0;
    *sec = 0;
}
DATETIME DATETIMEPrevNDetik(DATETIME D, int N){
    int d = Day(D);
    int m = Month(D);
    int y = Year(D);

    int hour = Hour(Time(D));
    int min = Minute(Time(D));
    int sec = Second(Time(D));

    // Algorithm
    int changeDay = (N > TIMEToDetik(Time(D)));
    if (changeDay) {
        N += - (TIMEToDetik(Time(D)) + 1);
        if ((m == 1) && (d == 1)) {
            m = 12;
            d = 32;
            y += -1;
        } else if (d == GetMaxDay(m, y)) {
            d = GetMaxDay(m - 1, y) + 1;
            m += -1;
        }

        d += -1;
        hour = 23;
        min = 59;
        sec = 59;

        while (N > 0) {
            if (N >= 86400) {
                N += - 86400;
                if ((m == 1) && (d == 1)) {
                    m = 12;
                    d = 32;
                    y += -1;
                } else if (d == GetMaxDay(m, y)) {
                    d = GetMaxDay(m - 1, y) + 1;
                    m += -1;
                }

                d += -1;
                hour = 23;
                min = 59;
                sec = 59;
            } else {
                TIME t = DetikToTIME(86399 - N); 
        
                DATETIME dt;
                CreateDATETIME(&dt, d, m, y, Hour(t), Minute(t), Second(t));
                return dt; 
            }
        }
    } else {
        TIME t = DetikToTIME(TIMEToDetik(Time(D)) - N); 
        
        DATETIME dt;
        CreateDATETIME(&dt, d, m, y, Hour(t), Minute(t), Second(t));
        return dt;    
    }
    /* Mengirim salinan D dengan detik dikurang N */
}
/* *** Kelompok Operator Aritmetika terhadap DATETIME *** */
long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh){
    int d1 = Day(DAw);
    int m1 = Month(DAw);
    int y1 = Year(DAw);

    int d2 = Day(DAkh);
    int m2 = Month(DAkh);
    int y2 = Year(DAkh);

    long int seconds = 0;
    if (DGT(DAw, DAkh)) {
        return 0;
    }

    if (y1 < y2) {
        // First year
        seconds += (86400 - TIMEToDetik(Time(DAw))); // Remaining seconds in day
        seconds += ((GetMaxDay(m1, y1) - d1) * 86400); // Remaining seconds in month

        int i;
        for (i = m1 + 1; i <= 12; i++) {
            seconds += (GetMaxDay(i, y1) * 86400); // Remaining seconds in year
        }

        // Years in between
        int j = y1 + 1;
        for (j = j; j < y2; j++) {
            if (GetMaxDay(2, j) == 28) {
                seconds += 31536000; // Seconds in a normal year
            } else {
                seconds += 31622400; // Seconds in a leap year
            }
        }

        // Last year
        int k;
        for (k = 1; k < m2; k++) {
            seconds += (GetMaxDay(k, y2) * 86400); // Total seconds in months before final month
        }

        seconds += (d2 - 1) * 86400; // Total seconds in days before final day
        seconds += TIMEToDetik(Time(DAkh));
    } else {
        if (m1 == m2) {
            if (d1 == d2) {
                seconds += Durasi(Time(DAw), Time(DAkh));
            } else {
                // Remaining seconds in first day
                seconds += (86400 - TIMEToDetik(Time(DAw)));

                // Remaining seconds in days between
                seconds += (((d2 - 1) - d1) * 86400); // Remaining seconds in days between
                
                // Remaining seconds in final day
                seconds += TIMEToDetik(Time(DAkh)); 
            }
        } else {
            // First month
                // Remaining seconds in first day
                seconds += (86400 - TIMEToDetik(Time(DAw)));

                // Remaining seconds in month            
                seconds += ((GetMaxDay(m1, y1) - d1) * 86400); 

            // Remaining seconds in months before final month
                int i;
                for (i = m1 + 1; i < m2; i++) {
                    seconds += (GetMaxDay(i, y1) * 86400); 
                }
            
            // Final month
                // Total seconds in days before final day
                seconds += (d2 - 1) * 86400; 
                
                // Remaining seconds in final day
                seconds += TIMEToDetik(Time(DAkh));
        }
    }

    return seconds;

    /* Mengirim DAkh-DAw dlm Detik, dengan kalkulasi */
    /* Prekondisi: DAkh > DAw */
}

DATETIME GetDateTime() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);             
    timeinfo = localtime(&rawtime);  

    // Access individual components
    int seconds = timeinfo->tm_sec;   
    int minutes = timeinfo->tm_min;   
    int hours = timeinfo->tm_hour;    
    int day = timeinfo->tm_mday;      
    int month = timeinfo->tm_mon + 1; // Month (0-11, add 1 for January-December)
    int year = timeinfo->tm_year + 1900; // Year (since 1900)

    DATETIME t;
    CreateDATETIME(&t, day, month, year, hours, minutes, seconds);

    return t;
}