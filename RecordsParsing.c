#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"


int checkRecordID(char *recordID);

void parseRecords(char *patientRecordsFile) {

    FILE *f = fopen(patientRecordsFile, "r");

    int size, pointer = 0;
    size_t length;
    char *line = NULL;
    char *line_copy;
    char *num;
    char *delimeters = " \t\n\0";

    size = getline(&line, &length, f);

    while (size >= 0 && !feof(f)) {

        parseLine(line, delimeters);

        free(line);
        line = NULL;

        if(errorCode == 1)
            return;

        size = getline(&line, &length, f);

    }
    parseLine(line, delimeters);


    free(line);
    line = NULL;

    fclose(f);

}

void parseLine(char *line, char *delimeters) {

    record *r = malloc(sizeof(record));

    char *num;

    num = strtok(line, delimeters);

    r->recordID = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->recordID, num);

    num = strtok(NULL, delimeters);

    r->patientFirstName = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->patientFirstName, num);

    num = strtok(NULL, delimeters);

    r->patientLastName = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->patientLastName, num);

    num = strtok(NULL, delimeters);

    r->diseaseID = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->diseaseID, num);

    num = strtok(NULL, delimeters);

    r->country = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->country, num);

    num = strtok(NULL, delimeters);

    r->entryDate = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->entryDate, num);

    num = strtok(NULL, delimeters);

    r->exitDate = malloc((strlen(num) + 1) * sizeof(char));
    strcpy(r->exitDate, num);

    int result = compareDates(r->entryDate, r->exitDate);

    if (result == 0) {
        printf("ERROR on record: %s. Wrong dates. The record will not be saved.\n", r->recordID);
        return;
    }


    if (!checkRecordID(r->recordID)) {
        printf("Record with ID: %s is duplicate. Program will now exit.\n", r->recordID);
        errorCode = 1;
        return;
    }

    insertRecord(r);
}

int checkRecordID(char *recordID) {

    for (int i = 0; i < diseaseHashTableNumOfEntries; i++) {

        bucket *ptr = diseaseHashTable[i];

        if (ptr == NULL)
            continue;

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] == NULL)
                    continue;

                Node *n = search(ptr->items[j]->value, recordID);

                if (n != NULL)
                    return 0;

            }

            ptr = ptr->next;
        }

    }

    return 1;
}

void insertRecord(record *rec) {

    int diseaseHash = hashFunction(rec->diseaseID, diseaseHashTableNumOfEntries);
    int countryHash = hashFunction(rec->country, countryHashTableNumOfEntries);

    // Insert record to Diseases Hash Table

    if (diseaseHashTable[diseaseHash] == NULL)
        diseaseHashTable[diseaseHash] = initializeBucket();

    bucket *ptr = diseaseHashTable[diseaseHash];

   if (available_items <= 0){
        perror("ERROR. Bucket Size too small to host records.\n");
        errorCode = 1;
    }

    insertDataToBucket(ptr, rec->diseaseID, rec);

    // Insert record to countries Hash Table

    if (countryHashTable[countryHash] == NULL)
        countryHashTable[countryHash] = initializeBucket();

    ptr = countryHashTable[countryHash];

    insertDataToBucket(ptr, rec->country, rec);

    //printf("Inserted disease: %s and country: %s\n", rec->diseaseID, rec->country);


}

void insertDataToBucket(bucket *ptr, char *data, record *rec) {

    int pos = -1;

    while (pos < 0) {

        for (int i = 0; i < available_items; i++) {

            if (ptr->items[i] == NULL) {

                pos = i;
                break;

            }

            if (strcmp(ptr->items[i]->key, data) == 0) {

                pos = i;
                break;

            }

        }

        if (pos >= 0)
            break;

        if (ptr->next == NULL)
            ptr->next = initializeBucket();

        ptr = ptr->next;
    }

    if (ptr->items[pos] == NULL) {

        ptr->items[pos] = malloc(sizeof(bucket_item));
        strcpy(ptr->items[pos]->key, data);
        ptr->items[pos]->value = NULL;

    }

    ptr->items[pos]->value = insert(ptr->items[pos]->value, rec);


}

int compareDates(char *entered, char *exit) {

    int entryDate, entryMonth, entryYear, exitDay, exitMonth, exitYear;

    if (strcmp(exit, "-") == 0 || strcmp(exit, "-\r")==0)
        return 1;

    char *entry_copy = malloc((strlen(entered) + 1) * sizeof(char));
    char *exit_copy = malloc((strlen(exit) + 1) * sizeof(char));

    strcpy(entry_copy, entered);
    strcpy(exit_copy, exit);

    char *delimiters = "-\0";
    char *num;

    num = strtok(entry_copy, delimiters);
    entryDate = atoi(num);
    num = strtok(NULL, delimiters);
    entryMonth = atoi(num);
    num = strtok(NULL, delimiters);
    entryYear = atoi(num);

    num = strtok(exit_copy, delimiters);
    exitDay = atoi(num);
    num = strtok(NULL, delimiters);
    exitMonth = atoi(num);
    num = strtok(NULL, delimiters);
    exitYear = atoi(num);

    free(entry_copy);
    free(exit_copy);

    if (exitYear < entryYear)
        return 0;

    if (exitYear == entryYear && exitMonth < entryMonth)
        return 0;

    if (exitYear == entryYear && exitMonth == entryMonth && exitDay < entryDate)
        return 0;

    // Equality return 1.

    return 1;
}