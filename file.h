#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#define FILE_PATH_PATIENT "C:\\Users\\facu-\\Documents\\PacientesDatos.dat"
#define FILE_PATH_MEASURES "C:\\Users\\facu-\\Documents\\PacientesTalla.dat"
#define FILE_PATH_SUMMARY "C:\\Users\\facu-\\Documents\\PacientesResumen.txt"

typedef struct {
    FILE * fp;
    int err;
} file_res;


int doesFileExists(char * path);
file_res openFile(char * filepath, char * mode);

#endif // FILE_H
