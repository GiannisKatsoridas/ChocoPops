cmake_minimum_required(VERSION 3.14)
project(SYSPRO_2020_PROJECT1 C)

set(CMAKE_C_STANDARD 99)

add_executable(SYSPRO_2020_PROJECT1 main.c RecordsParsing.c RecordsParsing.h GlobalHelpers.c GlobalHelpers.h Instructions.c Instructions.h InstructionsHelpers.c InstructionsHelpers.h BinaryHeap.c BinaryHeap.h AVL.c AVL.h)