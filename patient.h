#ifndef PATIENT_H
#define PATIENT_H
typedef struct{
    int HC;
    long DNI;
    char lastname[15];
    char name[15];
    long born_date;
    char health_insurance[15];
    long f_apointment;
} patient;

typedef struct{
    int HC;
    long born_date;
    double height;
    double weight;
}patient_measures;



int fGenPatientData(int force,int quantity);
int fgenReport();
void fInstertPatientData();
int findPatient();

#endif // PATIENT_H
