OBJS	= AVL.o BinaryHeap.o GlobalHelpers.o Instructions.o InstructionsHelpers.o main.o RecordsParsing.o
SOURCE	= AVL.c BinaryHeap.c GlobalHelpers.c Instructions.c InstructionsHelpers.c main.c RecordsParsing.c
HEADER	= AVL.h BinaryHeap.h GlobalHelpers.h Instructions.h InstructionsHelpers.h RecordsParsing.h
OUT	= diseaseMonitor
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

AVL.o: AVL.c
	$(CC) $(FLAGS) AVL.c 

BinaryHeap.o: BinaryHeap.c
	$(CC) $(FLAGS) BinaryHeap.c 

GlobalHelpers.o: GlobalHelpers.c
	$(CC) $(FLAGS) GlobalHelpers.c 

Instructions.o: Instructions.c
	$(CC) $(FLAGS) Instructions.c 

InstructionsHelpers.o: InstructionsHelpers.c
	$(CC) $(FLAGS) InstructionsHelpers.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 

RecordsParsing.o: RecordsParsing.c
	$(CC) $(FLAGS) RecordsParsing.c 


clean:
	rm -f $(OBJS) $(OUT)
