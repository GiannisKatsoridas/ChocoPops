#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

// Open the file and get line by line.
void parseRecords(char *patientRecordsFile) {

    FILE *f = fopen(patientRecordsFile, "r");

    int size;
    size_t length;
    char *line = NULL;
    char *delimeters = " \t\n\0";

    size = getline(&line, &length, f);

    while (size > 2 && !feof(f)) {

        parseLine(line, delimeters);        // Parse each line exclusively to get the record details

        free(line);
        line = NULL;

        if(errorCode == 1)                  // There has been an error
            return;

        size = getline(&line, &length, f);

    }

    if(size > 2)
        parseLine(line, delimeters);

    free(line);
    line = NULL;

    fclose(f);

}

// Parse each line of the file and split it by the delimeters above to get all the
// fields of the record. Store them in a record* variable and store the pointer
// in each of the hash tables.
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

    int result = compareDates(r->entryDate, r->exitDate);       // if the exit date is smaller than the entry date then 0 will be returned.

    if (result == 0) {
        printf("error\n");
        //printf("ERROR on record: %s. Wrong dates. The record will not be saved.\n", r->recordID);
        return;
    }


    if (!checkRecordID(r->recordID)) {          // if a record id is duplicate then the program will exit.
        printf("error\n");
        //printf("Record with ID: %s is duplicate. Program will now exit.\n", r->recordID);
        errorCode = 1;
        return;
    }

    insertRecord(r);                // insert the record in the hash tables (both of them - pointer to the record to have 0 data deduplication)
}

// Search all the trees to find whether the given record id already exists.
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

    bucket *ptr = diseaseHashTable[diseaseHash];        // find the proper hashTable position for the record to be inserted

   if (available_items <= 0){
        perror("ERROR. Bucket Size too small to host records.\n");
        errorCode = 1;
        return;
    }

    insertDataToBucket(ptr, rec->diseaseID, rec);       // insert the record in the diseases hash table

    // Insert record to countries Hash Table

    if (countryHashTable[countryHash] == NULL)
        countryHashTable[countryHash] = initializeBucket();

    ptr = countryHashTable[countryHash];

    insertDataToBucket(ptr, rec->country, rec);         // insert the record in the countries hash table

}

// First go through all the buckets in the list and through all their items to find if a similar
// disease/country has already been inserted. If true, then insert the record in the given tree.
// Else, create a new bucket item (and perhaps a new bucket as well) and insert them in it.
void insertDataToBucket(bucket *ptr, char *data, record *rec) {

    int pos = -1;

    while (pos < 0) {

        for (int i = 0; i < available_items; i++) {     // go through all the items of this bucket

            if (ptr->items[i] == NULL) {                // if its NULL then there are no more items in this bucket

                pos = i;
                break;

            }

            if (strcmp(ptr->items[i]->key, data) == 0) {    // given disease/country was found

                pos = i;
                break;

            }

        }

        if (pos >= 0)
            break;

        if (ptr->next == NULL)          // this bucket is final and therefore need to initialize a new bucket to place new record
            ptr->next = initializeBucket();

        ptr = ptr->next;
    }

    if (ptr->items[pos] == NULL) {      // there has been no record with the same disease/country so far

        ptr->items[pos] = malloc(sizeof(bucket_item));
        strcpy(ptr->items[pos]->key, data);
        ptr->items[pos]->value = NULL;

    }

    ptr->items[pos]->value = insert(ptr->items[pos]->value, rec);       // insert the record in the tree


}

// Compare two dates. If entered is bigger than exit then 0 is returned. Else 1 is returned.
int compareDates(char *entered, char *exit) {

    int entryDate, entryMonth, entryYear, exitDay, exitMonth, exitYear;

    if (strcmp(exit, "-") == 0 || strcmp(exit, "-\r")==0)       // in some linux computers, a \r is added to the end of the line
        return 1;

    char *entry_copy = malloc((strlen(entered) + 1) * sizeof(char));
    char *exit_copy = malloc((strlen(exit) + 1) * sizeof(char));

    strcpy(entry_copy, entered);
    strcpy(exit_copy, exit);

    char *delimiters = "-\r\0";
    char *num;

    num = strtok(entry_copy, delimiters);           // split both dates be '-' to get the day, month and year and compare them
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