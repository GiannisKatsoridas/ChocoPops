#include "RecordsParsing.h"
#include <string.h>

int getBalance(Node* node);

Node* insert(Node* node, record* rec);

Node* leftLeft(Node* node);

Node* rightRight(Node* node);

Node* leftRight(Node* node);

Node* rightLeft(Node* node);

Node* search(Node* node, char* recordID);

void deleteTree(Node* node);

void deleteTreeAndRecords(Node* node);