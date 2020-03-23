#include "AVL.h"

void executeInstruction(char* line);

void globalDiseaseStats(char *entry, char *exit);

void diseaseFrequency(char *virusName, char *date1, char *date2, char *country);

void topk_Diseases(int k, char* country, char* date1, char* date2);

void topk_Countries(int k, char* disease, char* date1, char* date2);

void insertPatientRecord(char *recordID, char *patientFirstName, char *patientLastName, char *diseaseID, char *country,
                         char *entryDate, char *exitDate);

void numCurrentPatients(char *disease);

void exitInstruction();
