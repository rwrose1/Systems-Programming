#include <stdlib.h>

#include "structs.h"

int isFile(const char * path);
int isDir(const char * path);
long fileSize(FILE * file);

int isTermContained(char * termSupplied, termList * head);
void deleteTermList(termList * head);

termList * readFromFile(char * inputFilePath);
termList * readFromIndex(FILE * outputFile, char * outputFileName);
termList * sortTerms(termList * inputList);
termList * mergeSorted(termList * inputList, termList * outputList);
void printSorted(termList * inputList, FILE * outputFile, char * outputFileName);


//char * addNumber(char * archiveName, int currentArchive);

/*
void insertAtFirst(char * term, termList * head);
void addTerm(termList * head, char * term);
void printAll(struct termList * head);
*/