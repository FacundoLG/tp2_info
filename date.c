#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"

void dateToLong(long * ldate,date d){
    *ldate = (d.day & 0xFF)| ((d.month & 0xFF) << 8) | ((d.year & 0xFFFF) << 16) ;
}

void longToDate(date * d,long ldate){
    d->day = ldate & 0xFF;
    d->month = (ldate >> 8) & 0xFF;
    d->year = (ldate >> 16) & 0xFFFF;
}

int getAge(date bornDate){
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    today.tm_year += 1900;
    today.tm_mon += 1;
    int age = today.tm_year - bornDate.year - 1;
    if((today.tm_mon > bornDate.month) || (today.tm_mon == bornDate.month && today.tm_mday >= bornDate.day)){
        age ++;
    }
    return age;
}

