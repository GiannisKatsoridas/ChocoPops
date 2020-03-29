#include <stdio.h>
#include <stdlib.h>
#include "InstructionsHelpers.h"

// Depending on the instruction, execute the appropriate function and get the requested results
void executeInstruction(char *line) {

    char *delimeters = " \t\n\0";

    char *num;

    num = strtok(line, delimeters);

    if (strcmp(num, "/globalDiseaseStats") == 0) {

        num = strtok(NULL, delimeters);

        if (num == NULL)
            globalDiseaseStats(NULL, NULL); // get globalDiseaseStats without dates

        else {      // dates have been added, get appropriate results

            char *arg1 = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(arg1, num);
            num = strtok(NULL, delimeters);
            if (num == NULL) {
                printf("ERROR. If one date was given as an argument then please provide another.\n");
                return;
            }
            globalDiseaseStats(arg1, num);

            free(arg1);

        }

    } else if (strcmp(num, "/diseaseFrequency") == 0) {

        num = strtok(NULL, delimeters);             // get the instruction arguments
        char *virusName = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(virusName, num);

        num = strtok(NULL, delimeters);
        char *date1 = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(date1, num);

        num = strtok(NULL, delimeters);
        char *date2 = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(date2, num);

        num = strtok(NULL, delimeters);
        char *country = NULL;
        if (num != NULL) {
            country = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(country, num);
        }

        diseaseFrequency(virusName, date1, date2, country);

        free(virusName);
        free(date1);
        free(date2);
        if (country != NULL)
            free(country);

    } else if (strcmp(num, "/topk-Diseases") == 0) {

        num = strtok(NULL, delimeters);
        int k = atoi(num);

        num = strtok(NULL, delimeters);
        char *country = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(country, num);

        char *date1 = NULL, *date2 = NULL;

        num = strtok(NULL, delimeters);
        if (num != NULL) {
            date1 = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(date1, num);
            num = strtok(NULL, delimeters);
            if (num == NULL) {
                printf("ERROR. If one date was given as an argument then please provide another.\n");
                free(country);
                free(date1);
                return;
            }
            date2 = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(date2, num);
        }

        topk_Diseases(k, country, date1, date2);

        free(country);
        if (date1 != NULL) {
            free(date1);
            free(date2);
        }

    } else if (strcmp(num, "/topk-Countries") == 0) {

        num = strtok(NULL, delimeters);
        int k = atoi(num);

        num = strtok(NULL, delimeters);
        char *disease = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(disease, num);

        char *date1 = NULL, *date2 = NULL;

        num = strtok(NULL, delimeters);
        if (num != NULL) {
            date1 = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(date1, num);
            num = strtok(NULL, delimeters);
            if (num == NULL) {
                printf("ERROR. If one date was given as an argument then please provide another.\n");
                free(disease);
                free(date1);
                return;
            }
            date2 = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(date2, num);
        }

        topk_Countries(k, disease, date1, date2);

        free(disease);
        if (date1 != NULL) {
            free(date1);
            free(date2);
        }

    } else if (strcmp(num, "/insertPatientRecord") == 0) {

        num = strtok(NULL, delimeters);
        char *recordID = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(recordID, num);

        if(searchForRecord(recordID) != NULL){      // there has already been a patient with the same record id
            printf("Patient with given record already exists. Please give a different record ID.\n");
            free(recordID);
            return;
        }

        num = strtok(NULL, delimeters);
        char *patientFirstName = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(patientFirstName, num);

        num = strtok(NULL, delimeters);
        char *patientLastName = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(patientLastName, num);

        num = strtok(NULL, delimeters);
        char *diseaseID = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(diseaseID, num);

        num = strtok(NULL, delimeters);
        char *country = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(country, num);

        num = strtok(NULL, delimeters);
        char *entryDate = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(entryDate, num);

        num = strtok(NULL, delimeters);
        char *exitDate = NULL;

        if (num != NULL) {
            exitDate = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(exitDate, num);
        }

        insertPatientRecord(recordID, patientFirstName, patientLastName, diseaseID, country, entryDate, exitDate);

        free(recordID);
        free(patientFirstName);
        free(patientLastName);
        free(diseaseID);
        free(country);
        free(entryDate);
        if (exitDate != NULL)
            free(exitDate);

    } else if (strcmp(num, "/recordPatientExit") == 0) {

        num = strtok(NULL, delimeters);
        char *recordID = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(recordID, num);

        num = strtok(NULL, delimeters);
        char *exitDate = malloc((strlen(num) + 1) * sizeof(char));
        strcpy(exitDate, num);


        record *rec = searchForRecord(recordID);

        if (rec == NULL) {
            printf("not found\n");
            //printf("No such record ID was found. Please try again with a valid recordID.\n");
            free(recordID);
            free(exitDate);
            return;
        }

        if(compareDates(rec->entryDate, exitDate) == 0){
            printf("error\n");
            //printf("Wrong date. Date of exit is previous to date of entry. Please provide correct dates:\n");
            free(recordID);
            free(exitDate);
            return;
        }

        if (rec->exitDate != NULL)
            free(rec->exitDate);

        rec->exitDate = malloc((strlen(exitDate) + 1) * sizeof(char));

        strcpy(rec->exitDate, exitDate);

        free(recordID);
        free(exitDate);

        printf("Record updated\n");

    } else if (strcmp(num, "/numCurrentPatients") == 0) {

        char *disease = NULL;

        num = strtok(NULL, delimeters);
        if (num != NULL) {
            disease = malloc((strlen(num) + 1) * sizeof(char));
            strcpy(disease, num);
        }

        numCurrentPatients(disease);

        if (disease != NULL)
            free(disease);

    } else
        printf("error\n");
        //printf("ERROR. Not an acceptable instruction.\n");

}

// Search through all the trees in all the nodes from the diseaseHashTable and get the size of each tree.
// If dates have been given, take them into consideration when counting the tree size.
void globalDiseaseStats(char *date1, char *date2) {

    for (int i = 0; i < diseaseHashTableNumOfEntries; i++) {

        if (diseaseHashTable[i] == NULL)
            continue;

        bucket *ptr = diseaseHashTable[i];

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] == NULL)
                    break;

                if (date1 == NULL)
                    printf("%s %d\n", ptr->items[j]->key,
                           getTreeSize(ptr->items[j]->value));  // count every node as a patient
                else
                    printf("%s %d\n", ptr->items[j]->key,
                           getTreeSizeBetweenDates(ptr->items[j]->value, date1, date2));    // count only nodes inside the given dates

//                if (date1 == NULL)
//                    printf("Disease: %s\t\tNumber of Patients: %d\n", ptr->items[j]->key,
//                           getTreeSize(ptr->items[j]->value));  // count every node as a patient
//                else
//                    printf("Disease: %s\t\tNumber of Patients: %d\n", ptr->items[j]->key,
//                           getTreeSizeBetweenDates(ptr->items[j]->value, date1, date2));    // count only nodes inside the given dates
//
//
            }

            ptr = ptr->next;
        }
    }

}

// Search the diseaseHashTable for given disease. If found get the tree size (from given country if needed)
// whose records are inside the given dates.
void diseaseFrequency(char *virusName, char *date1, char *date2, char *country) {

    int hashPos = hashFunction(virusName, diseaseHashTableNumOfEntries);
    int pos = -1;

    bucket *ptr = diseaseHashTable[hashPos];

    while (ptr != NULL) {       // search all the buckets in the list

        for (int i = 0; i < available_items; i++) {
            if (ptr->items[i] == NULL)
                break;
            if (strcmp(ptr->items[i]->key, virusName) == 0)
                pos = i;
        }

        if (pos >= 0)
            break;

        ptr = ptr->next;
    }

    if (pos < 0) {
        printf("error\n");
        //printf("ERROR. No such disease in given records.\n");
        return;
    }

    if (country == NULL)
        printf("%s %d\n", virusName,
               getTreeSizeBetweenDates(ptr->items[pos]->value, date1, date2));
    else
        printf("%s %d\n", virusName,
               getTreeSizeBetweenDatesForCountry(ptr->items[pos]->value, date1, date2, country));


//    if (country == NULL)
//        printf("Disease frequency for: %s in all countries: %d.\n", virusName,
//               getTreeSizeBetweenDates(ptr->items[pos]->value, date1, date2));
//    else
//        printf("Disease frequency for: %s in %s: %d.\n", virusName, country,
//               getTreeSizeBetweenDatesForCountry(ptr->items[pos]->value, date1, date2, country));

}

// Get the total number of people infected in a given country. Place them in an array and then insert them in
// a heap.
void topk_Diseases(int k, char *country, char *date1, char *date2) {

    int heap_size = getTotalDiseases();

    HeapNode *heap = NULL;

    bucket *ptr = countryHashTable[hashFunction(country, countryHashTableNumOfEntries)];

    int pos = -1;

    while (ptr != NULL) {

        for (int i = 0; i < available_items; i++) {

            if (ptr->items[i] == NULL)
                break;

            if (strcmp(ptr->items[i]->key, country) == 0) {
                pos = i;
                break;
            }
        }

        if (pos >= 0)
            break;

        ptr = ptr->next;
    }

    if (pos == -1) {
        printf("error\n");
        //printf("ERROR. Country given was not found.\n");
        return;
    }

    // Get the people infected in the given country.

    heap = getTotalInfectedByCountry(ptr->items[pos]->value, date1, date2);

    if(heap == NULL){
        //printf("No diseases found in given country.\n");
        return;
    }

    heap_size = getHeapSize(heap);

    if (heap_size < k) {

        //printf("K given is bigger than total diseases of given country. K will change to total diseases.\n");
        k = heap_size;

    }

    // For each Disease in the heap, pop the head of the heap and print it. The heap will balance itself and give the next biggest disease.
    for (int i = 0; i < k; i++) {

        HeapNode *n = heap;

        heap = popFromHeap(heap, heap_size - i);

        printf("%s %d\n", n->name, n->number);
        //printf("Disease: %s\tNumber: %d\n", n->name, n->number);
        free(n->name);
        free(n);
    }

    if (k != heap_size)
        deleteHeap(heap);
}

// Same as above with only difference being the hash table and the value compared (disease, not country)
void topk_Countries(int k, char *disease, char *date1, char *date2) {

    int heap_size;

    HeapNode *heap = NULL;

    bucket *ptr = diseaseHashTable[hashFunction(disease, diseaseHashTableNumOfEntries)];

    int pos = -1;

    while (ptr != NULL) {

        for (int i = 0; i < available_items; i++) {

            if (ptr->items[i] == NULL)
                break;

            if (strcmp(ptr->items[i]->key, disease) == 0) {
                pos = i;
                break;
            }
        }

        if (pos >= 0)
            break;

        ptr = ptr->next;
    }

    if (pos == -1) {
        printf("error\n");
        //printf("ERROR. Country given was not found.\n");
        return;
    }

    heap = getTotalInfectedByDisease(ptr->items[pos]->value, date1, date2);

    if (heap == NULL) {
        //printf("No countries found with given disease.\n");
        return;
    }

    heap_size = getHeapSize(heap);

    if (heap_size < k) {

        //printf("K given is bigger than total countries of given disease. K will change to total diseases.\n");
        k = heap_size;

    }

    for (int i = 0; i < k; i++) {

        HeapNode *n = heap;

        heap = popFromHeap(heap, heap_size - i);

        //printf("Disease: %s\tNumber: %d\n", n->name, n->number);
        printf("%s %d\n", n->name, n->number);
        free(n->name);
        free(n);

    }

    if (k != heap_size)
        deleteHeap(heap);
}

// Similar to the records parsing, insert a record * in the appropriate tree
void insertPatientRecord(char *recordID, char *patientFirstName, char *patientLastName, char *diseaseID, char *country,
                         char *entryDate, char *exitDate) {

    record *rec = malloc(sizeof(record));

    rec->recordID = malloc((strlen(recordID) + 1) * sizeof(char));
    strcpy(rec->recordID, recordID);

    rec->patientFirstName = malloc((strlen(patientFirstName) + 1) * sizeof(char));
    strcpy(rec->patientFirstName, patientFirstName);

    rec->patientLastName = malloc((strlen(patientLastName) + 1) * sizeof(char));
    strcpy(rec->patientLastName, patientLastName);

    rec->diseaseID = malloc((strlen(diseaseID) + 1) * sizeof(char));
    strcpy(rec->diseaseID, diseaseID);

    rec->country = malloc((strlen(country) + 1) * sizeof(char));
    strcpy(rec->country, country);

    rec->entryDate = malloc((strlen(entryDate) + 1) * sizeof(char));
    strcpy(rec->entryDate, entryDate);

    if (exitDate == NULL) {
        rec->exitDate = malloc(2 * sizeof(char));
        strcpy(rec->exitDate, "-");
    } else {
        rec->exitDate = malloc((strlen(exitDate) + 1) * sizeof(char));
        strcpy(rec->exitDate, exitDate);
    }

    insertRecord(rec);      // same as RecordsParsing

    printf("Record added\n");
}

// For every tree in every bucket count the patients whose exitDate is '-'.
// Count only the records from one hash table as they both point to same data.
void numCurrentPatients(char *disease) {

    int flag = 0;

    for (int i = 0; i < diseaseHashTableNumOfEntries; i++) {

        bucket *ptr = diseaseHashTable[i];

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] == NULL)
                    break;

                if (disease != NULL && strcmp(disease, ptr->items[j]->key) != 0)
                    continue;

                int sum = countCurrentPatientsInTree(ptr->items[j]->value);

                printf("%s %d\n", ptr->items[j]->key, sum);
                //printf("Number of current patients for disease: %s, is: %d\n", ptr->items[j]->key, sum);
                flag = 1;
            }

            ptr = ptr->next;
        }
    }

    if(flag == 0 && disease != NULL)        // Disease given was not found so print 0
        printf("%s 0\n", disease);
}

// Free all structs
void exitInstruction() {

    printf("exiting\n");

    for (int i = 0; i < diseaseHashTableNumOfEntries; i++) {

        if (diseaseHashTable[i] == NULL)
            continue;

        bucket *ptr = diseaseHashTable[i];
        bucket *next;

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] != NULL) {
                    deleteTree(ptr->items[j]->value);
                    free(ptr->items[j]);
                }
            }

            next = ptr->next;
            free(ptr->items);
            free(ptr);
            ptr = next;
        }
    }

    free(diseaseHashTable);

    for (int i = 0; i < countryHashTableNumOfEntries; i++) {

        if (countryHashTable[i] == NULL)
            continue;

        bucket *ptr = countryHashTable[i];
        bucket *next;

        while (ptr != NULL) {

            for (int j = 0; j < available_items; j++) {

                if (ptr->items[j] != NULL) {
                    deleteTreeAndRecords(ptr->items[j]->value);
                    free(ptr->items[j]);
                }
            }

            next = ptr->next;
            free(ptr->items);
            free(ptr);
            ptr = next;
        }
    }

    free(countryHashTable);

}