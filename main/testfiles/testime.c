#include <stdio.h>
#include <time.h>
#include "includeADT.h"

// int main() {
//     time_t rawtime;
//     struct tm *timeinfo;

//     time(&rawtime);             // Get the current time
//     timeinfo = localtime(&rawtime);  // Convert to local time

//     // Access individual components
//     int seconds = timeinfo->tm_sec;   // Seconds (0-59)
//     int minutes = timeinfo->tm_min;   // Minutes (0-59)
//     int hours = timeinfo->tm_hour;    // Hours (0-23)
//     int day = timeinfo->tm_mday;      // Day of the month (1-31)
//     int month = timeinfo->tm_mon + 1; // Month (0-11, add 1 for January-December)
//     int year = timeinfo->tm_year + 1900; // Year (since 1900)

//     printf("Current time: %02d:%02d:%02d\n", hours, minutes, seconds);
//     printf("Date: %04d-%02d-%02d\n", year, month, day);

//     return 0;
// }


// int main() {
//     time_t rawtime;
//     struct tm *timeinfo;

//     time(&rawtime);             
//     timeinfo = localtime(&rawtime);  

//     // Access individual components
//     int seconds = timeinfo->tm_sec;   
//     int minutes = timeinfo->tm_min;   
//     int hours = timeinfo->tm_hour;    
//     int day = timeinfo->tm_mday;      
//     int month = timeinfo->tm_mon + 1; // Month (0-11, add 1 for January-December)
//     int year = timeinfo->tm_year + 1900; // Year (since 1900)

//     DATETIME t;
//     CreateDATETIME(&t, day, month, year, hours, minutes, seconds);

//     return 0;
// }

int main() {
    DATETIME t = GetDateTime();
    printf("Success\n");
    TulisDATETIME(t);

    return 0;
}