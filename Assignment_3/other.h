#include <stdlib.h>

#include "structs.h"

int isFile(const char * path);
int isDir(const char * path);
long fileSize(FILE * file);

void printAll(struct termList ** head);
void printSorted(termList * inputList, char * outputFileName);
void printAllCount(fileCountList ** head);

int isTermContained(char * termSupplied, termList * head);

void deleteTermList(termList * head);

void insertFileAndCount(fileCountList ** head, fileCountList * inputList);
void insertTerm(termList ** head, char * term, fileCountList * filesAndCounts);

termList * readFromFile(char * inputFilePath, char * currentFile);
termList * readFromIndex(char * outputFileName);

termList * sortTerms(termList * inputList);

void mergeSorted(termList ** inputList, termList ** outputList);
char * addNumber(char * archiveName, int currentArchive);

int ifFileContained(termList ** head, char * currentFilePath);
