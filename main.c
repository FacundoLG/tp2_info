#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "log.h"
#include "patient.h"

int main(int argc, char* argv[])
{
    if(argc < 2){
        printErr("Falta argumento: nombre del archivo");
        return 0;
    }
    char res ;
    do{
        fflush(stdout);
        printMessage("[MENU]\n1) Generar Informe\n2) Buscar paciente\n");
        printMessage("\n[EXTRA]\n3) Generar informacion aleatoria\n4) Insertar informacion\n5) Remover Informacion \n\n0) Salir\n");
        res = getch();
        system("cls");

        switch (res) {
            case '1':
                 fgenReport(argv[1]);
            break;
            case '2':
                 findPatient();
            break;
            case '3':
                {
                    int asw;
                    printf("Cantidad a generar: ");
                    scanf("%d",&asw);
                    if(asw >= 0)
                        fGenPatientData(1,asw);
                }
            break;
            case '4':
                 fInstertPatientData();
            break;
            case '5':
                 fGenPatientData(1,0);
            break;

        }
    }while(res != '0');
   return 0;
}

