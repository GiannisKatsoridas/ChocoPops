#include "Instructions.h"
#include "BinaryHeap.h"

typedef struct pair_struct {

    char* name;
    int number;

} Pair;

int getTreeSize(Node* node);

int getHeapSize(HeapNode* node);

int getTreeSizeBetweenDates(Node* node, char* date1, char* date2);

int getTreeSizeBetweenDatesForCountry(Node *node, char *date1, char *date2, char *country);

HeapNode *getTotalInfectedByCountry(Node *node, char *date1, char *date2);

HeapNode *getTotalInfectedByDisease(Node *node, char *date1, char *date2);

Pair **getInfectedFromNode(Node *node, Pair **infected, char *date1, char *date2);

Pair **getInfectedFromNodeForCountry(Node *node, Pair **infected, char *date1, char *date2);

record* searchForRecord(char* recordID);

record *searchForRecordInTree(Node *node, char *recordID);

int countCurrentPatientsInTree(Node* node);