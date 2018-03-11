#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

#include "structs.h"
#include "other.h"

void swap(termList * a, termList * b);

int isFile(const char * path) {
	struct stat s;
	stat(path, &s);
	return S_ISREG(s.st_mode);
}

int isDir(const char *file_path)
{
	struct stat s;
	stat(file_path, &s);
	return S_ISDIR(s.st_mode);
}

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
*/
long fileSize(FILE * file){
    //Position: the variable to be returned, and the position of the end character.
    unsigned long endPosition = 0;
    unsigned long startPosition = 0;

    fflush(file); //Flush the buffer
    startPosition = ftell(file); //Record the start pos.

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file in fileSize().\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    endPosition = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    fseek(file,startPosition,SEEK_SET); //return to start position

    return endPosition;// returns the position of the file offset
}

int isTermContained(char * termSupplied, termList * head){
	while (head != NULL){
		if (strcmp(termSupplied, head->term) == 0){
			return 1;
		}
		head = head->next;
	}
	return 0;
}

/*
	Function void deleteTermList, frees all memory allocated for the list. Takes the head of the list 
	as its only parameter.
*/
void deleteTermList(termList * head){
	//if head is equal to null, then return
	if (head == NULL){
		return;
	}
	
	//sets current equal to head
	termList * current = head;
	termList * next;
	
	//loops through the list, freeing up data for every variable until current hits null
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

/*
	This function finds the first non alphanumeric character in the string and then returns its index 
*/

void printAll(struct termList ** head) {
	termList * current = *head;
	fileCountList * currentFile;
	int i = 1;
	while (current != NULL) {
		printf("\nTerm %d : \"%s\".\n", i, current->term);
		currentFile = current->filesAndCounts;
		while (currentFile != NULL) {
			printf("File %s : %d\n", currentFile->file, currentFile->count);
			currentFile = currentFile->next;
		}
		current = current->next;
		i++;
	}
}

void insertTerm(termList ** head, char * term, char * tempFileName){
	
	termList * current;
	termList * prev;
	termList * newNode;
	fileCountList * newFileCount;
	char * toLowerArg;
	char * toLowerThing;
	
	newNode = malloc(sizeof(termList));
	newNode->term = malloc(strlen(term) * sizeof(char));
	strcpy(newNode->term, term);
	
	newFileCount = malloc(sizeof(fileCountList));
	newFileCount->file = malloc(strlen(tempFileName) * sizeof(char));
	strcpy(newFileCount->file, tempFileName);
	newFileCount->count = 1;
	
	newNode->filesAndCounts = newFileCount;
	
	//Head is equal to null, assign it new node
	if (*head == NULL) {
		printf("HEAD IS NULL "); fflush(stdout);
		*head = newNode;
		return;
	}
	
	if (strcmp(term, (*head)->term) <= 0) {
		printf("HEAD IS LESS THAN FIRST ");
		if (strcmp(term, (*head)->term) == 0) {
			//DO INCREMENT
			printf("INCREMENTING %s on term %s\n", (*head)->term, term);
			fileCountList * current;
			current = (*head)->filesAndCounts;
			
			while(current != NULL) {
				if (strcmp(current->file, newFileCount->file) == 0) {
					current->count++;
					free(newNode->term);
					return;
				}
			}
		} 
		else {
			newNode->next = *head;
			*head = newNode;
			return;
		}
		
	}
	printf("INSERTING INTO BODY ");
	current = (*head);
	while (current != NULL) {
		if (strcmp(term, (current)->term) <= 0) {
		
			if (strcmp(term, (current)->term) == 0) {
				//DO INCREMENT
				printf("INCREMENTING (In Loop) %s on term %s\n", (current->term), term);
				fileCountList * currentFile;
				currentFile = current->filesAndCounts;
				
				while(current != NULL) {
					if (strcmp(currentFile->file, newFileCount->file) == 0) {
						currentFile->count++;
						return;
					}
				}
				
			} 
			else {
				newNode->next = current;
				prev->next = * head;
			}
			
			return;
			
		}
		
		prev = current;
		current = current->next;
	}
	
	prev->next = newNode;

}

isEmpty(char * line) {
	int i;
	for (i = 0; i < strlen(line); i++) {
		if (isalnum(line[i])) {
			return 0;
		}
	}
	return 1;
}

/*
	The function readFromFile returns a pointer to the head of a linked list of termList 
	structs. It accepts one parameter, the input file's absolute path. readFromFile reads through 
	the supplied file, adding the terms to the linked list, the file their from, and the correct count
	(incremented) when required.
*/
termList * readFromFile(char * inputFilePath) {
	
	FILE * inputFile = fopen(inputFilePath, "r"); //inputFile is the unformatted file to be read
	char line[1024]; //Each line of the input file
	char * token;
	int i = 0;
	
	int start = 0; //Start of string
	int end = 0; //end of string
	
	termList * head = NULL;
	
	while(fgets(line, 1024, inputFile) != NULL) {
		
		
		if (isEmpty(line)) { printf("skipping line\n"); continue; }
		
		for (i = 0; i < strlen(line); i++) {
			
			if (!isalnum(line[i])) {
				line[i] = ' ';
			}
			
		}
		
		printf("Line : %s\n", line);
		
		token = strdup(line);
		
		token = strtok(token, " ");
		
		printf("Tokens : ", token);
		
		fflush(stdout);
		
		while(token) {
			
			printf("\"%s\" ", token);
			
			insertTerm(&head, token, inputFilePath);
			
			token = strtok(NULL, " ");
			
		}
		
		printf("\n");
		
	}
	
	printAll(&head);
	
	return head;
	
}

/*
	The function readFromIndex returns a pointer to the head of a linked list of termList 
	structs. It accepts two parameters, the FILE that is to be read from and its name for re-
	opening. readFromIndex reads through the supplied file, adding data in order to the linked 
	list when required.
*/
//termList * readFromIndex(FILE * outputFile, char * outputFileName);

/*
	The function sortTerms returns and takes a pointer to the head of a linked list of termList 
	structs. This function sorts the terms by alphabetical order.
*/
//termList * sortTerms(termList * inputList);

/*
	The function mergeSorted takes a pointer to two head nodes of termList structs, both are already 
	sorted. It then creates and returns a new pointer to the head of a new termList struct that contains values
	from both supplied linked lists in order.s
*/
//termList * mergeSorted(termList * inputList, termList * outputList);

/*
	The function printSorted returns nothing. It takes three parameter: One, a pointer to the head
	of a linked list that is to be printed in the correct format to the output file that is supplied as
	well - Two. Three, the name of the outputFile is supplied for reopening when required.
*/
//void printSorted(termList * inputList, FILE * outputFile, char * outputFileName);


