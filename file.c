#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"file.h"
#include"log.h"
#include"date.h"



int doesFileExists(char * path){
    if(fopen(path,"rb") == NULL) return 0;
    return 1;
}

file_res openFile(char * filepath, char * mode){
    file_res fr;
    fr.err = 0;
    fr.fp = fopen(filepath,mode);
    if(fr.fp == NULL){
        char errmsg[200];
        fr.err = 1;
        if(mode[0] == 'r') strcpy(errmsg,"(r) No se pudo leer el archivo en: ");
        if(mode[0] == 'w') strcpy(errmsg,"(w) No se pudo crear el archivo en: ");
        if(mode[0] == 'a') strcpy(errmsg,"(a) No se pudo abrir el archivo en: ");
        strcpy(errmsg,filepath);
        printErr(errmsg);
    }
    return fr;
}

