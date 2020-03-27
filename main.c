#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstructionsHelpers.h"

int main(int argc, char** argv) {

    if(argc != 9){  // If arguments are not 9 then there has been a mistake
        printf("ERROR. Wrong number of arguments.\n");
        return 0;
    }

    char* patientRecordsFile;

    parseArguments(argv, &patientRecordsFile);      // Parse the arguments given

    globalStructsInitialization();                  // Initialize global variables and structs (eg HashTables)

    parseRecords(patientRecordsFile);               // Parse the records given in the file and put them in the hash tables
    if(errorCode == 1)                              // If there has been an error (eg double record id) exit the program
        return 0;

    //printf("Records parsed. Please, give input:\n");

    char* line = NULL;
    size_t length;
    int size;

    size = getline(&line, &length, stdin);          // Read the first instruction from the user
    if(line[strlen(line)-1] == '\n')
        line[strlen(line)-1] = '\0';                    // Remove the line break at the end

    while(strcmp(line, "/exit") != 0){              // While the user doesn't give "exit" run the instruction

        executeInstruction(line);                   // Execute the instruction given

        free(line);

        line = NULL;

        size = getline(&line, &length, stdin);
        if(line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';
    }

    free(line);

    exitInstruction();                              // Free memory from structs

    free(patientRecordsFile);

    return 0;
}
