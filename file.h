#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#define FILE_PATH_PATIENT "C:\\TP2\\PacientesDatos.dat"
#define FILE_PATH_MEASURES "C:\\TP2\\PacientesTalla.dat"
#define FILE_PATH_SUMMARY "C:\\TP2\\"

typedef struct {
    FILE * fp;
    int err;
} file_res;


int doesFileExists(char * path);
file_res openFile(char * filepath, char * mode);

#endif // FILE_H
