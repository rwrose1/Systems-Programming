//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/3/2017
//Course:  	ICSI 402
//Desc:    	This program takes directory full of log files then concatonates them into
//         	a single log file, where the order is based on the time of each log.
//Input:   	The program can take a command line argument specifying the path where the program will execute
//	   	Otherwise, it will execute in the current directory
//Output:  	A .log file and standard output of the printed merge list
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

//headers for standard c library
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//included external header files
#include "structs.h"
#include "headersOne.h"

/*
	Function parseLine construct a logline with 3 fields
	based on the input string. Note that this function allocates memory. Contains a character array named line.
*/
logline_t * parseLine(char line []){
	//Creates a duplicate string before tokenizing
	char str[128];
	strcpy(str, line);
	
	//tokenizes lines to name, time, and message
	char * levelP = strtok(str, ",");
	char * timestampP = strtok(NULL, ",");
	char * messageP = strtok(NULL, ",");
	
	//checks to make sure that line is free to be used
	logline_t * parsed = NULL;
	if((parsed = malloc(sizeof(logline_t))) == NULL){
		fprintf(stderr, "Unable to allocate memory for new parsed structure.\n");
		exit(-1);
	}
  	
	//if there is no end of line character, then it puts one on the end of the string
  	if (strstr(messageP, "\n") == NULL) {
   	 	strcat(messageP, "\n");
  	}
  	
	//copys the tokens onto the line struct
	strcpy(parsed->level , levelP);
	strcpy(parsed->timestamp , timestampP);
	strcpy(parsed->message , messageP);

	return parsed;
}

/*
	Function void deleteList, frees all memory allocated for the list.
*/
void deleteList(loglist_t * head){
	//if head is equal to null, then return
	if (head == NULL){
		return;
	}
	
	//sets current equal to head
	loglist_t * current = head;
	loglist_t * next;
	
	//loops through the list, freeing up data for every variable until current hits null
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

/*
	Function void printLines,  prints all the lines contained in the list. contains a pointer named head in parameters.
*/
void printLines( loglist_t * head){
	
	//if head is equal to null, then it breaks
	if (head == NULL){
		printf("Empty List\n");
		return;
	}
	//initalizes all the temp variables, memory allocation
	loglist_t * temp = malloc(sizeof(loglist_t));
	if (temp == NULL){// if temp variable is equal to null, program is unable to terminate successfully
		fprintf(stderr, "Unable to allocate memory for new temp structure.\n");
		exit(-1);
	}
	temp = head -> next;
	//prints the data elements of the head, which include the level, message, and the timestamp
	
// repeats the same process, but for the rest of the linked list.
	while(temp!=NULL)
    {
    	printf("%s,%s,%s", temp->line.level, temp->line.timestamp, temp->line.message);
      temp=temp->next;
    }
}
