typedef struct heap_node_struct {

    char *name;
    int number;
    struct heap_node_struct *left;
    struct heap_node_struct *right;

} HeapNode;

HeapNode *createHeap(char* name, int number);

HeapNode* insertToHeap(HeapNode *node, int cur, int goal, char *name, int number);

HeapNode* heapify(HeapNode *node);

HeapNode *popFromHeap(HeapNode *node, int size);

void printHeap(HeapNode* h);

void deleteHeap(HeapNode* h);