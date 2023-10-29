#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include"generators.h"
#include "date.h"

char names[][30]={
    "Facundo",
    "Agustin",
    "Carla",
    "Agustina",
    "Alejandro",
    "Rocio",
    "Martina",
    "Juan",
    "Fernando",
    "Sofia",
    "Maria",
    "Elena",
    "Luciano",
    "Zoe",
    "Valentina",
    "Emiliano",
    "Tomas",
    "Nicolas",
    "Pedro",
    "Joel",
    "Jose",
    "Franco",
    "Ana",
    "Silvia",
    "Rosa",
    "Norma",
    "Marta",
    "Claudia",
    "Susana",
    "Patricia",
    "Fransisco",
    "Geremias",
    "Marcos",
    "Laura",
    "Walter",
    "Javier",
    "Horacio",
    "David",
};
char lastnames[][30] = {
    "Gonzalez",
    "Rodriguez",
    "Gomez",
    "Gimenez",
    "Perez",
    "Martinez",
    "Sanchez",
    "Diaz",
    "Polez",
    "Ferzandez",
    "Garcia",
    "Torres",
    "Ramirez",
    "Acosta",
    "Herrera",
    "Suarez",
    "Pereyra",
    "Rojas",
    "Molina",
    "Castro",
    "Luna",
    "Rios",
    "Cabrera",
    "Moreno",
    "Pereyra",
    "Peralta",
    "Castillo",
    "Ledesma",
    "Quiroga",
    "Vega",
    "Vera",
    "Villalba",
    "Vazquez",
    "Arias"
};
char health_insurance[][30] = {
    "OSDE",
    "Swiss Medical",
    "Galeno",
    "Medicus",
    "IOMA",
    "PAMI",
    "OSECAC",
    "SANCOR Salud",
    "UOM",
};

void gStart(){
     srand(time(NULL));
}
void gName(char * name){
    int size = sizeof(names)/(sizeof(char)*30);
    strcpy(name,names[rand()%size]);
}
void gLastname(char *lname){
    int size = sizeof (lastnames)/(sizeof (char)*30);
    strcpy(lname,lastnames[rand()%size]);
}

void gHealthInsurance(char * insurance){
    int size = sizeof (health_insurance)/(sizeof (char)*30);
    strcpy(insurance,health_insurance[rand()%size]);
}

int gHC(int reset){
    static int count = 1;
    if(reset){
        count = 1;
    }
    return count++;

}

int gDNI(int reset){
    static int bDNI = 35000000;
    if(reset){
        bDNI = 35000000;
    }
    bDNI+= rand()%500000;
    bDNI+= rand()%10000;
    return bDNI;
}

long gBornDate(){
    date d;
    d.year = (rand()%20) + 1980;
    d.month =(rand()%11)+1;
    d.day = (rand()%29)+1;

    long date;
    dateToLong(&date,d);
    return  date;
}

long gFirstApointment(long bornDate){
    date d;
    longToDate(&d,bornDate);
    d.day = (rand()%30)+1;
    d.month = (rand()%11)+1;
    d.year += (rand()%15) + 5;
    long apointment;
    dateToLong(&apointment,d);
    return apointment;
}

void f_call(){
    static int f_call = 0;
    if(f_call) return;
    gStart();
    f_call = 1;
}

void gPatient(patient * p,int reset){
    f_call();
    p->HC = gHC(reset);
    p->DNI = gDNI(reset);
    gName(p->name);
    gLastname(p->lastname);
    gHealthInsurance(p->health_insurance);
    p->born_date = gBornDate();
    p->f_apointment = gFirstApointment(p->born_date);
}

void gPatientMeasures(patient_measures * pat_m,patient p){
    f_call();
    pat_m->HC = p.HC;
    pat_m->born_date = p.born_date;
    pat_m->height = 1.0 + (double)(rand() % 130)/100.0;
    pat_m->weight = (double)(50.0) + (double)(rand() % 60);

}
