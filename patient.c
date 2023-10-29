#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include <windows.h>

#include"file.h"
#include"log.h"
#include"date.h"
#include"patient.h"
#include"generators.h"

typedef struct{
    int curr_range_idx;
    int start[100]; // c1 = start
    int found;
    int eval_size;
}find_res;

// find: busca palabras detro del string
find_res find(char str[],int str_size,char eval[30],int eval_size){
    int eidx = 0;
    find_res res;
    res.eval_size=eval_size;
    res.curr_range_idx = 0;
    res.found = 0;
    if(eval_size <=0) return res;
    for(int i = 0; i < str_size;i++){
        if(eidx == eval_size){
            res.found = 1;
            res.curr_range_idx++;
            if(res.curr_range_idx >99) break;
            eidx=0;
        }
        //printf("%d %c %c\n",eidx,eval[eidx],str[i]);
        if(str[i] == eval[eidx]){
            if(eidx == 0) res.start[res.curr_range_idx] = i;
            eidx++;
        }
        else if(eidx > 0) {
            i--;
            eidx = 0;
        };
    }
    return res;
}


//Remarca el texto en el string
void highlight(char str[],int str_size,int start[],int start_size,int highlight_len){
    char str_cpy[str_size];
    char aux;
    int print_idx=0;
    strcpy(str_cpy,str);
    for(int i = 0;i < start_size;i++){
        aux = str_cpy[start[i]];
        str_cpy[start[i]] = '\0';
        printf("%s",&(str_cpy[print_idx]));
        str_cpy[start[i]] = aux;
        SetConsoleTextAttribute(hconsole(),10);
        aux = str_cpy[start[i]+highlight_len];
        str_cpy[start[i]+highlight_len] = '\0';
        printf("%s",&str_cpy[start[i]]);
        str_cpy[start[i]+highlight_len] = aux;
        SetConsoleTextAttribute(hconsole(),15);
        print_idx = start[i]+highlight_len;
    }
    printf("%s\n",&(str_cpy[print_idx]));

}



// Ordena los pacientes por orden alfabetico
void sortPatients(patient patients[],int patient_size){
    for(int i = 0 ; i < patient_size-1;i++){
        if(strcmp(patients[i].lastname,patients[i+1].lastname)>0){
            patient aux = patients[i];
            patients[i] = patients[i+1];
            patients[i+1] = aux;
            if(i > 0){
                i-=2;
            }
        }
    }
}

//Inserta un paciente nuevo
void fInstertPatientData(){
    FILE * fpPatient = fopen(FILE_PATH_PATIENT,"rb");
    fseek(fpPatient,0,SEEK_END);
    fseek(fpPatient,(long)(-sizeof(patient)),SEEK_CUR);

    patient lpatient;
    patient newPatient;
    patient_measures newMeasures;
    if(fread(&lpatient,sizeof (lpatient),1,fpPatient)<= 0){
        newPatient.HC = 1;
        newMeasures.HC = 1;
    }

    fclose(fpPatient);
    fpPatient = NULL;


    newPatient.HC = lpatient.HC + 1;
    newMeasures.HC = lpatient.HC + 1;

    if(newPatient.HC >MAX_PATIENTS){
        printMessage("Maxima cantidad de pacientes alcanzada\n");
        return;
    }

    printMessage("[FORMULARIO]\nNombre: ");
    scanf(" %s",newPatient.name);
    fflush(stdin);
    printMessage("Apellido: ");
    scanf(" %s",newPatient.lastname);
    fflush(stdin);
    printMessage("DNI: ");
    scanf(" %ld",&newPatient.DNI);
    fflush(stdin);
    date fnac;
    printMessage("Fecha de nacimiento(dd,mm,aaaa): ");
    scanf(" %d,%d,%d",&fnac.day,&fnac.month,&fnac.year);
    fflush(stdin);
    dateToLong(&newPatient.born_date,fnac);

    newMeasures.born_date = newPatient.born_date;

    printMessage("Obra social: ");
    scanf(" %s",newPatient.health_insurance);
    fflush(stdin);
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    today.tm_year += 1900;
    today.tm_mon += 1;

    date f_app;
    f_app.day = today.tm_mday;
    f_app.month = today.tm_mon;
    f_app.year = today.tm_year;

    dateToLong(&newPatient.f_apointment,f_app);

    printMessage("Peso[KG]: ");
    scanf(" %lf",&newMeasures.weight);
    fflush(stdin);
    printMessage("Altura[M]: ");
    scanf(" %lf",&newMeasures.height);
    fflush(stdin);
    char ans;
    printMessage("Desea guardar los datos?(s/n):");
    fflush(stdin);
    scanf(" %c",&ans);
    if(ans == 's'){
        fpPatient = fopen(FILE_PATH_PATIENT,"ab");
        FILE * fpMeasures = fopen(FILE_PATH_MEASURES,"ab");
        fwrite(&newPatient,sizeof (newPatient),1,fpPatient);
        fwrite(&newMeasures,sizeof (newMeasures),1,fpMeasures);
        system("cls");
        printMessage("Informacion guardada");
    }
    _fcloseall();
}

int fGenPatientData(int force,int amount){
    if(!doesFileExists(FILE_PATH_PATIENT)|| force){
        //Archivo PacientesDatos.dat no existe
        printLog("Generando archivo PacientesDatos.dat",0);
        file_res patient_f = openFile(FILE_PATH_PATIENT,"wb");
        //Generamos informacion inicial
        for(int i =0; i < amount;i++){
            patient p;
            gPatient(&p,(i == 0));
            fwrite(&p,sizeof (p),1,patient_f.fp);
        }
        printLog("Archivo PacientesDatos.dat creado",1);
        //Cerramos archivo
        fclose(patient_f.fp);
    }
    if(!doesFileExists(FILE_PATH_MEASURES)|| force){
        printLog("Generando archivo PacientesTalla.dat",0);

        file_res fpMeasures = openFile(FILE_PATH_MEASURES,"wb");
        file_res fpPatient = openFile(FILE_PATH_PATIENT,"rb");
        if(fpMeasures.err || fpPatient.err) return 1;

        for(int i = 0;i < amount;i++){
            //Leer archivo creado anteriormente
            patient p;
            fread(&p,sizeof (p),1,fpPatient.fp);
            patient_measures pm;
            //Generar medidas a partir del paciente
            gPatientMeasures(&pm,p);
            //Guardar medidas en archivo binario
            fwrite(&pm,sizeof (pm),1,fpMeasures.fp);
        }
        printLog("Archivo PacientesTalla.dat creado",1);
        fclose(fpMeasures.fp);
        fclose(fpPatient.fp);
    }
    return 0;
}

int fgenReport(){
    file_res patient_f = openFile(FILE_PATH_PATIENT,"rb");
    file_res measures_f = openFile(FILE_PATH_MEASURES,"rb");
    file_res patientsummary_f = openFile(FILE_PATH_SUMMARY,"w");
    if(patient_f.err || patientsummary_f.err || measures_f.err) return 1;

    int p_idx = 0;
    patient patients[MAX_PATIENTS];

    int avg_age = 0;
    int patient_count = 0;
    patient p;
    patient_measures pm;

    int insurances_len = 0;
    char insurances[MAX_PATIENTS][30];
    int insurance_count[MAX_PATIENTS];

    printLog("Generando archivo PacientesResumen.txt",0);
    fprintf(patientsummary_f.fp,"%3s|%s|%s|%s|%6s|%s\n","HC","EDAD","ALTURA[M]","PESO[KG]","IMC","PRIMERA CITA");
    while (fread(&pm,sizeof (pm),1,measures_f.fp) > 0) {
        patient_count++;
        //Obtiene al fecha de nacimiento a partir del dato long
        date bDate;
        longToDate(&bDate,pm.born_date);
        //Calcula la edad a partir de la fecha de nacimiento
        int age = getAge(bDate);
        avg_age += age;
        //Obtenemos la fecha de la primera cita, este dato solo esta en el archivo de datos del paciente
        fread(&p,sizeof (p),1,patient_f.fp);
        //guardamos los pacientes

        patients[p_idx] = p;
        p_idx++;

        //Compara la obra social del paciente con las contadas
        for(int i = 0;i <= insurances_len;i++){
              //Si ya existia un contador de esa obra social, le suma uno

              //Si ninguna obra social coincidio, se crea una nueva;
              if(i == insurances_len){
                strcpy(insurances[insurances_len],p.health_insurance);
                insurance_count[insurances_len] = 0;
                insurances_len++;
              }
              if(strcmp(insurances[i],p.health_insurance)==0){
                insurance_count[i]++;
                break;
              }
        }
        date fappointment;
        longToDate(&fappointment,p.f_apointment);

        double IMC = pm.weight /(pm.height * pm.height);

        fprintf(patientsummary_f.fp,"%3d:%4d:%9.2f:%8.2f:%6.2f: %2d/%4d\n",pm.HC,age,pm.height,pm.weight,IMC,fappointment.month,fappointment.year);
    }
    _fcloseall();
    //Ordena los pacietes por fecha de primera cita, del mas antiguo al mas reciente
    if(p_idx == 0){
        printMessage("NO es posible hacer un informe, no hay pacientes cargados...\n\n");
        return 1;
    };
    for(int i = 0 ; i < p_idx-1;i++){
        date fa1;
        date fa2;
        longToDate(&fa1,patients[i].f_apointment);
        longToDate(&fa2,patients[i+1].f_apointment);

        if(fa1.year > fa2.year || (fa1.year == fa2.year && (fa1.month > fa2.month || (fa1.month == fa2.month && fa1.day > fa2.day)))){
            patient aux = patients[i];
            patients[i] = patients[i+1];
            patients[i+1] = aux;
            if(i > 0){
                i-=2;
            }
        }
    }

    avg_age/= patient_count;


    printMessage("[DATOS]\n");
    printf(" Cantidad de pacientes: %d\n",patient_count);
    printf(" Edad promedio: %d\n",avg_age);
    printMessage("[OBRAS SOCIALES] Cantidad de pacientes por obra social\n");
    for(int i = 0; i < insurances_len;i++){
        printf(" %-15s %3d\n",insurances[i],insurance_count[i]);
    }
    printMessage("[Pacientes] Pacientes mas antiguos\n");
    for(int i = 0; i < (p_idx >= 10? 10: p_idx);i++){
        date fa;
        longToDate(&fa,patients[i].f_apointment);
        printf("%3d - %-15s %-15s - %9ld - %2d/%2d/%4d\n",patients[i].HC,patients[i].name,patients[i].lastname,patients[i].DNI,fa.day,fa.month,fa.year);
    }

    printMessage("\nArchivo PacientesResumen.txt creado\n\n");
    return 0;
}

int findPatient(){
    patient_measures patients_measures[MAX_PATIENTS];
    patient patients[MAX_PATIENTS];
    int patient_size = 0;
    file_res fpatientsmeasures = openFile(FILE_PATH_MEASURES,"rb");
    file_res fpatients = openFile(FILE_PATH_PATIENT,"rb");
    while (fread(&patients[patient_size],sizeof (patient),1,fpatients.fp) > 0) {
        fread(&patients_measures[patient_size],sizeof(patient_measures),1,fpatientsmeasures.fp);
        patient_size++;
    }

    sortPatients(patients,patient_size);

    char find_str[100];
    for(int i = 0; i < 39;i++) find_str[i] = ' ';
    find_str[99] = '\0';

    int fidx=0;
    int c = 0;
    int matches;
    do {
        matches = 0;
        if((c >= 48 && c <= 57) || c == 8 || (c >=65 && c<=90) || (c >=97 && c<=122) || c == 32) {
            if (c == '\b' && fidx > 0){
                fidx--;
                find_str[fidx] = '|';
                find_str[fidx+1] = '\0';
            }
            else if(fidx < 99 && c != '\b'){
                find_str[fidx] = c;
                find_str[fidx+1] = '|';
                fidx++;
            }
        }
        system("cls");
        SetConsoleTextAttribute(hconsole(),14);
        printf(" Buscar: ");
        SetConsoleTextAttribute(hconsole(),10);
        printf("%s",find_str);
        SetConsoleTextAttribute(hconsole(),14);
        printf("\n");
        printf(" %-15s%-15s| %3s| %8s| %15s| %4s| %10s| %10s\n","Apellido","Nombre","HC","DNI","Obra social","IMC","Fnac","Primera cita");
        SetConsoleTextAttribute(hconsole(),WHITE);

        for (int i = 0; i < patient_size;i++){
            char str[200];
            date born_date;
            date f_appointment;
            longToDate(&born_date,patients[i].born_date);
            longToDate(&f_appointment,patients[i].f_apointment);
            double IMC = patients_measures[i].weight /(patients_measures[i].height * patients_measures[i].height);

            sprintf(str," %-15s%-15s| %3d| %ld| %15s| %2.1f| %2d/%2d/%4d| %2d/%2d/%4d",patients[i].lastname,patients[i].name,
                    patients[i].HC,patients[i].DNI,patients[i].health_insurance,IMC,born_date.day,born_date.month,born_date.year,
                    f_appointment.day,f_appointment.month,f_appointment.year);
            find_res founded = find(str,100,find_str,fidx);
            if(founded.found){
                highlight(str,100,founded.start,founded.curr_range_idx,fidx);
                matches++;
            }
            if(fidx == 0){
                printf("%s\n",str);
                matches = patient_size;
            }
        }
        printf(" Pacientes: %d de %d   Salir[-]\n",matches,patient_size);
    }while ((c = _getch()) != 45 );
    system("cls");
    return 0;
}
