#include "GlobalHelpers.h"

void parseRecords(char* patientRecordsFile);

void parseLine(char *line, char *delimeters);

int compareDates(char *entered, char *exit);

void insertRecord(record *rec);

void insertDataToBucket(bucket *ptr, char *data, record* rec);

int checkRecordID(char *recordID);
