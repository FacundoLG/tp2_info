#ifndef GENERATORS_H
#define GENERATORS_H
#include"patient.h"
#define MAX_PATIENTS 500


void gPatient(patient * p,int reset);
void gPatientMeasures(patient_measures * pat_m,patient p);

#endif // GENERATORS_H
