//Project: 	Prog4
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/15/2017
//Course:  	ICSI 402
/*Desc:    this file contains the implemented functions that correspond to the prototypes in hashHeaders
it contains the following functions newHashNode, insertHash, printHashTable
*/
/*Output: the output for the functions associated with the hash table include 
the contents of the hash table, in the form of one array element per line.
Each array element is represented as a list of nodes at the specified index and each node displays the symbol and LC value.
Each line specified in the form:  index: listNode1 → listNode2 → · · · → listNodeN → NULL.
*/



//standard c libraries
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//include external header files containing the prototypes for the corresponding functions in this file
#include "hashHeaders.h"

/*
    This function takes the attributes of a hashNode struct as parameters. Allocating memory for and 
    assigning for a newHashNode struct. Finally it returns a pointer to the new struct.
*/
hashNode * newHashNode(char symbol[11], int address){

    //Allocate memory for the new struct and checks if null, if NULL, prints errors and terminates
    hashNode * newHashNode = (hashNode *)malloc(sizeof(hashNode));
    if(newHashNode == NULL){
        fprintf(stderr, "Could not allocate memory for newInstructionSet.\n");
        exit(1);
	}

    //Copy the supplied string 
	strcpy(newHashNode->symbol, symbol);

    //Assign the supplied number
	newHashNode->address = address;
    
    //Initialize the next pointers to NULL
    newHashNode->next = NULL;

    //Return the new struct
    return newHashNode;
}

/* the insertHash function takes parameters of of head and newNode that are pointers to the hashNode struct
it inserts symbols into the array of linked lists.
*/
void insertHash(hashNode ** head, hashNode * newNode) {
	//prints the symbol that in being attempted to be inserted in newNode
	//printf("\tAttempting insert on symbol : \"%s\"\n", newNode->symbol); fflush(stdout);
	//pointers for current and previous
	hashNode * current;
	hashNode * prev;
	
	//if head == NULL set head = to new node
	if ((*head) == NULL) {
		//printf("\t\tHead is null...\n"); fflush(stdout);
		*head = newNode;
		return;
	}
	
	//printf("\t\thead is not null...\n"); fflush(stdout);
	//If head is not null, insert head at the end of the list
	current = (*head);
	while (current != NULL) {
		//printf("looping...\n"); fflush(stdout);
		prev = current;
		//printf("This is the seg fault?\n"); fflush(stdout);
		prev = current;
		current = current->next;
	}
	//printf("\t\tHit end...\n"); fflush(stdout);
	prev->next = newNode;
	
}

/*
This function takes a array of linked lists (hashTable) and its array size as parameter and returns nothing. It prints each inner 
linked list in the form:
    index: listNode1 → listNode2 → · · · → listNodeN → NULL.
*/
void printHashTable(int size, hashNode * hashTable[]){
    int i = 0; //Index needed for the loop
    
    //Loop through every element in the array
    for(i; i < size; i++){
        
        //if the head of the linked list is null
        if(hashTable[i] == NULL){
            //printf("\n%d:\n", i);
        }
        //else the linked list has values
        else{
            printf("\n%d: ", i);
            hashNode * tempNode; //a tempNode used for traversal
            tempNode = hashTable[i]; //assign the tempNode to the current head of the linked list at index i
            //loop through and print the entire linked list
            while(tempNode != NULL){
                printf("%s - %d → ", tempNode->symbol, tempNode->address);
                tempNode = tempNode->next;// assigns tempNode equal to a pointer to the next of tempNode
            }
            printf("NULL");
        }
    }
}

/*
The deleteHashTable function returns nothing. It accepts the size of the hashNode array and supplied hashNode array.
The function loops through the array and each index (linked list), freeing all allocated memory.
*/
void deleteHashTable(int size, hashNode * hashTable[]){
    int i = 0; //A count for the loop on the array
    for(i; i < size; i++){
        if(hashTable[i] == NULL){
            //The linked list is empty
            continue;
        }
        else{
            //The linked list is not empty
            hashNode * tempNode; //a tempNode used for traversal
            hashNode * previous; //a previous node used for freeing
            tempNode = hashTable[i]; //assign the tempNode to the current head of the linked list at index i
            //loop through and print the enture linked list
            while(tempNode != NULL){
                //Assign nodes (traverse)
                previous = tempNode;
                tempNode = tempNode->next;
                //printf("\nDeleted: %s.\n", previous->symbol);
                free(previous); //Free the previous node 
            }
        }
    }
}
