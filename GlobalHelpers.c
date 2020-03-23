#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GlobalHelpers.h"


void parseArguments(char** argv, char** patientRecordsFile){

    int argumentPos;

    if(strcmp(argv[1], "-p") == 0)
        argumentPos = 2;
    else if(strcmp(argv[3], "-p") == 0)
        argumentPos = 4;
    else if(strcmp(argv[5], "-p") == 0)
        argumentPos = 6;
    else if(strcmp(argv[7], "-p") == 0)
        argumentPos = 8;
    else{
        printf("No argument for patientRecordsFile (-p) given.\n");
        errorCode = 1;
        return;
    }

    *patientRecordsFile = malloc(strlen(argv[argumentPos]) * sizeof(char) + 1);
    strcpy(*patientRecordsFile, argv[argumentPos]);

    if(strcmp(argv[1], "-h1") == 0)
        argumentPos = 2;
    else if(strcmp(argv[3], "-h1") == 0)
        argumentPos = 4;
    else if(strcmp(argv[5], "-h1") == 0)
        argumentPos = 6;
    else if(strcmp(argv[7], "-h1") == 0)
        argumentPos = 8;
    else{
        printf("No argument for diseaseHashTableNumOfEntries (-h1) given.\n");
        free(*patientRecordsFile);
        errorCode = 1;
        return;
    }

    diseaseHashTableNumOfEntries = atoi(argv[argumentPos]);

    if(strcmp(argv[1], "-h2") == 0)
        argumentPos = 2;
    else if(strcmp(argv[3], "-h2") == 0)
        argumentPos = 4;
    else if(strcmp(argv[5], "-h2") == 0)
        argumentPos = 6;
    else if(strcmp(argv[7], "-h2") == 0)
        argumentPos = 8;
    else{
        printf("No argument for countryHashTableNumOfEntries (-h2) given.\n");
        free(*patientRecordsFile);
        errorCode = 1;
        return;
    }

    countryHashTableNumOfEntries = atoi(argv[argumentPos]);

    if(strcmp(argv[1], "-b") == 0)
        argumentPos = 2;
    else if(strcmp(argv[3], "-b") == 0)
        argumentPos = 4;
    else if(strcmp(argv[5], "-b") == 0)
        argumentPos = 6;
    else if(strcmp(argv[7], "-b") == 0)
        argumentPos = 8;
    else{
        printf("No argument for bucketSize (-b) given.\n");
        free(*patientRecordsFile);
        errorCode = 1;
        return;
    }

    bucketSize = atoi(argv[argumentPos]);

}

int hashFunction(char *string, int max) {

    int sum = 0;
    int len = strlen(string);

    for(int i=0; i<len; i++)
        sum += string[i];

    return sum % max;
}

void globalStructsInitialization() {

    diseaseHashTable = malloc(diseaseHashTableNumOfEntries * sizeof(bucket*));
    countryHashTable = malloc(countryHashTableNumOfEntries * sizeof(bucket*));

    for(int i=0; i<diseaseHashTableNumOfEntries; i++)
        diseaseHashTable[i] = NULL;

    for(int i=0; i<countryHashTableNumOfEntries; i++)
        countryHashTable[i] = NULL;

    errorCode = 0;

    available_space = bucketSize - sizeof(int) - sizeof(bucket *);
    available_items = available_space / sizeof(bucket_item *);
}

bucket* initializeBucket() {

    bucket* b = malloc(bucketSize);

    b->items_amount = 0;
    b->next = NULL;

    b->items = malloc(available_items * sizeof(bucket_item*));
    for(int i=0; i<available_items; i++)
        b->items[i] = NULL;

    return b;
}

int getTotalDiseases() {

    int sum = 0;

    for(int i=0; i<diseaseHashTableNumOfEntries; i++){

        bucket* ptr = diseaseHashTable[i];

        while(ptr != NULL){

            for(int j=0; j<available_items; j++)
                if(ptr->items[j] != NULL)
                    sum++;

            ptr = ptr->next;
        }

    }

    return sum;
}

int getTotalCountries() {

    int sum = 0;

    for(int i=0; i<countryHashTableNumOfEntries; i++){

        bucket* ptr = countryHashTable[i];

        while(ptr != NULL){

            for(int j=0; j<available_items; j++)
                if(ptr->items[j] != NULL)
                    sum++;

            ptr = ptr->next;
        }

    }

    return sum;

}
