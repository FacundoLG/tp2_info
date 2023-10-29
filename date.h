#ifndef DATE_H
#define DATE_H

typedef struct {
    int day;
    int month;
    int year;
} date;

void longToDate(date * d,long ldate);

void dateToLong(long * ldate,date d);

int getAge(date bornDate);
#endif // DATE_H
