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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
	Function loglist* mergeLists(loglist* resultlist, loglist* inlist) to merge
	sorted linked list inlist into resultlist and return a pointer to the head of the
	combined list. 
	
	Resultlist:	A linked list to be merged. This one is returned later.
	inlist:		A linked list to be merged 
*/
loglist_t * mergeLists(loglist_t * resultlist, loglist_t * inlist){
	
	loglist_t * temp;		//A temp loglist used to hold inlist;
	temp = inlist->next;

	/* Find the end of resultList */
	//If temp is null, then the list doesn't merge.
	if (temp == NULL){		
		return resultlist; 
	}
	else{ //else, it loops through and adds each member of inlist too resultlist
		while(temp != NULL){
			logline_t * templine = malloc(sizeof(logline_t));
			if (templine == NULL){
				fprintf(stderr, "Unable to allocate memory for new temp line structure.\n");
				exit(-1);
			}
			* templine = temp->line;
			addLast(resultlist, * templine);
			temp = temp->next;
		}
	}

	
	/* Loop through inlist item by item, adding lines to resultList */

	return resultlist;
}

/*
	Function loglist* sortList(loglist* inlist) to sort the provided linked list inlist
	and return a pointer to the head of the sorted list.
	
	loglist_t inlist: The loglist to be sorted via bubblesort.
*/

//Sorts the list using a bubble sort
loglist_t * sortList(loglist_t * inlist) {
	
	//if inlist is empty, returns NULL
	if (inlist == NULL){
		printf("Empty List\n");
		return NULL;
	}

	//initalizes all the temp variables
	loglist_t * temp = malloc(sizeof(loglist_t)); //a temporary variable to hold a loglist node in the loop.
	if (temp == NULL){
		fprintf(stderr, "Unable to allocate memory for new temp structure.\n");
		exit(-1);
	}

	

	temp = inlist -> next;

	int flag = 0;	//A makeshift boolean variable. Used to determine when to loop.

	do{
		//initializes flag to 0;
		flag = 0;
		temp = inlist;
		while (temp->next != NULL)
		{
			//if temp's data is greater than temp->nexts, tru = 1 and we call swap to swap the two nodes data.
			if(strcmp(temp->line.timestamp, temp->next->line.timestamp) > 0)
			{
				swap(temp, temp->next);
				flag = 1;
			}
			temp = temp->next;
		}
	} while (flag == 1);

}
