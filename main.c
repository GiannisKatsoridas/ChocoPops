#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstructionsHelpers.h"

int main(int argc, char** argv) {

    if(argc != 9){
        printf("ERROR. Wrong number of arguments.\n");
        return 0;
    }

    char* patientRecordsFile;

    parseArguments(argv, &patientRecordsFile);
    if(errorCode == 1)
        return 0;

    globalStructsInitialization();

    parseRecords(patientRecordsFile);

    bucket* a = diseaseHashTable[0];

    printf("Records parsed. Please, give input:\n");

    /*HeapNode* h = NULL;
    for(int i=0; i<20; i++){
        h = insertToHeap(h, 0, i+1, "-", rand() % 100);
    }

    printHeap(h);

    printf("/////////////////////////////////\n");

    h = popFromHeap(h, 20);
    h = popFromHeap(h, 19);
    h = popFromHeap(h, 18);
    h = popFromHeap(h, 17);

    printHeap(h);
*/

    char* line = NULL;
    size_t length;
    int size;

    size = getline(&line, &length, stdin);
    line[strlen(line)-1] = '\0';        // Remove the line break at the end

    while(strcmp(line, "/exit") != 0){

        executeInstruction(line);

        free(line);

        line = NULL;

        size = getline(&line, &length, stdin);
        line[strlen(line)-1] = '\0';
    }

    free(line);

    exitInstruction();

    free(patientRecordsFile);

    return 0;
}
