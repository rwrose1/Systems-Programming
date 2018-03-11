//Project: 	Prog4
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/15/2017
//Course:  	ICSI 402
/* Desc:    
the main functions,contains basic error checking that checks if the correct number of arguments are supplied. It also checks if 
any file names that are supplied whether the files exists and if it is readable. 
*/

/* Output: the outputs for the main file include the in-order traversal of the BST. 
In each node, the instruction names are outputted, for the example opcode. The height of the BST is also printed out, the height of the BST
is considered to be the longest path starting from the root to the deepest node. 
The last thing that is outputted is the contents of the hash table, that contains one array element per line. 
Each element is a list of nodes at that specified index and each node displays the symbol and LC value. 
Each line is represented in the form: index: listNode1 → listNode2 →···→ listNodeN → NULL.   
*/

//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//included headers
#include "other.h"
#include "BSTheaders.h"
#include "hashHeaders.h"

//Constants
#define LINESIZE 100
#define WORD 3
#define BYTE 1

//main method
int main( int argc, char *argv[] )  {
	//variables
	int hashTableSize = 0; //an integer to hold the hash table size supplied
	int address = 0; //an integer to help figure out the address of each variable
	FILE * instructionSetFile; //A FILE type for the instructionSet input file
	FILE * programFile; //A FILE type for the program input file
	char line [LINESIZE]; //A char pointer that will store each line in the instructionSet input file
	char tempInstruction [6]; //The temp five character long instruction
	unsigned char tempOpcode; //The temp unsigned char to hold the opcode integer 
	unsigned char tempFormat; //The temp unsigned char to hold the format integer
	char * token; //A char pointer used when tokenizing a line in the instructionSetFile
	instructionSet * head = NULL; //A instructionSet pointer to the head node of the used BST
	instructionSet * tempNode; //A instructionSet pointer to the head node of the temp BST node
	char hashInstruction[6]; //The buffer for the Instruction to be used in the searchFunctionBST
	char symbol[11]; //the symbol buffer to be inserted into the hash table.
	hashNode * tempHashNode; //The node we assign the symbol and address to to add to the hash table.
	char * potentialReserveSize; //A char * to hold the potential size of the bytes/words reserved in the program file.
	int reserveSize; //The reserve size (to be converted from potentialReserveSize)
	
	//Check number of arguments
	if(argc < 4){
		fprintf(stderr, "There were only %d arguments supplied. Expected 4.\nExiting...\n", argc);
		exit(-1);
	}
	else if(argc > 4){
		fprintf(stderr, "There were %d arguments supplied. Expected 4.\nExiting...\n", argc);
		exit(-1);
	}
	else{
		//Print out supplied arguments
		//printf("\nfirstpass has been called.\n");
		//printf("The supplied instructionset filename: \"%s\".\n", argv[1]);
		//printf("The supplied programfile filename: \"%s\".\n", argv[2]);
		//printf("The supplied hashtablesize: %s.\n", argv[3]);
	}
	
	//Check if the supplied hashtablesize is not a number
	if(atoi(argv[3]) == 0){
		fprintf(stderr, "\nThe supplied hashtablesize is not a number.\nExiting...\n");
		exit(-1);
	}

	//Assign int to converted command line arg.
	hashTableSize = atoi(argv[3]);
	hashNode * hashTable[hashTableSize];
	
	//Initialize every index in the hashTable to NULL
	int i = 0; //counter for the initialization loop
	for (i = 0; i < hashTableSize; i++) {
		hashTable[i] = NULL;
	}
	
	//Check if the instructionset file doesn't exists or is unreadable
	if(fileExists(argv[1])==0){
		fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", does not exist.\nExiting...\n", argv[1]);
		exit(-1);
	}
	if(fileReadable(argv[1])==0){
		fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", cannot be read.\nExiting...\n", argv[1]);
		exit(-1);
	}

	//Check if the programfile file doesn't exists or is unreadable
	if(fileExists(argv[2])==0){
		fprintf(stderr, "\nThe supplied programfile filename, \"%s\", does not exist.\nExiting...\n", argv[2]);
		exit(-1);
	}
	if(fileReadable(argv[2])==0){
		fprintf(stderr, "\nThe supplied programfile filename, \"%s\", cannot be read.\nExiting...\n", argv[2]);
		exit(-1);
	}

	//Check if the supplied hashtablesize is not atleast 2
	if(hashTableSize < 2){
		fprintf(stderr, "\nThe supplied hashtablesize is not atleast 2.\nExiting...\n");
		exit(-1);
	}

	//Open and check the instructionset filename
	instructionSetFile = fopen(argv[1], "r");
	if(instructionSetFile == NULL){
        	fprintf(stderr, "Could not allocate memory for instructionSetFile.\nExiting...\n");
        	exit(1);
	}

	//printf("\n");
	//Parse line by line, inserting into BST
 	while (fgets(line, LINESIZE, instructionSetFile)) {
		tempNode = NULL; //Set the tempNode to NULL at every loop

		//Parse (and print) the lines of the instructionSetFile
		//printf("%s", line);
		token = strdup(line);

		//The instruction is the line up to the first space
		token = strtok(token, " ");
		strcpy(tempInstruction, token);
		//printf("%s ", tempInstruction);

		//The opcode is the rest of the line up to the second space
		token = strtok(NULL, " ");
		tempOpcode = atoi(token);
		//printf("%d ", tempOpcode);

		//The format is the rest of the line up to the newline char
		token = strtok(NULL, "\n");
		tempFormat = atoi(token);
		//printf("%d\n", tempFormat);

		//create tempNode
		tempNode = newInstructionSet(tempInstruction, tempOpcode, tempFormat);

		//print attributes of tempNode
		///printf("%s ", tempNode->instruction);
		///printf("%d ", tempNode->opcode);
		///printf("%d\n", tempNode->format);
		
		//Insert tempNode into head
		insertBST(&head, tempNode);
	}

	//Print the BST (in-order)
	printf("In-order traversal of BST: \n");
	printInOrder(head);
	printf("\b\b \n");
	
	//Print the max height
	int maxheight = 0; //The integer to store the max height of the tree
	if (head != NULL) {
		//if the left and right nodes of head are null, then max height is equal to null
		if (head->left == NULL && head->right == NULL) {
			maxheight = 0;
		} 
		//else maxheight the returned value of maxHeight()
		else {
			maxheight = maxHeight(head);
		}
	}
	printf("\nMax Height: \"%d\"\n", maxheight);
	
	//Open program file
	programFile = fopen(argv[2], "r");
	if(programFile == NULL){
    		fprintf(stderr, "Could not allocate memory for programFile.\nExiting...\n");
    		exit(1);
	}
	
	//printf("\n"); //newline
	hashInstruction[0] = '\0'; //makes sure this instruction is empty
	
	//Start parsing
	while(fgets(line, LINESIZE, programFile)) {
		
		//deletes the \n character from the line
		line[strlen(line) - 1] = '\0';
		
		//set token equal to line, so that we can modify it
		token = strdup(line);
		//printf("ADDRESS #%d : %s\n", address, token);
		
		//first split of the line
		token = strtok(token, " ");
		
		//If the first character of the first token is equal to tab, then
		//the token MUST be the symbol.
		if (token[0] != '\t') {
			strcpy(symbol, token);
		}
		
		//counter to help determine where the instruction is.
		int counter = 1;
		while(token) {
			//if the token is equal to a tab, increment the pointer up to eliminate it, and this
			//tells us the instruction is in this token
			//else, if the counter is equal to two then we know the hash instruction is in this token.
			if (token[0] == '\t') {
				//printf("\nThere's a tab\n");
				token++;
				strcpy(hashInstruction, token);
			} 
			else if ((counter % 2 == 0) && hashInstruction[0] == '\0') {
				strcpy(hashInstruction, token);
			} 
			
			//Saves a POTENTIAL reserve size
			if ((counter % 3 == 0)) {
				potentialReserveSize = strdup(token);
			}
			
			//printf("\"%s\" ", token);
			counter++;
			//next token
			token = strtok(NULL, " ");
		}
		
		//if the symbol is NOT empty, then we can insert it and the address into the hashtable.
		if (symbol[0] != '\0') {
			//create new node here
			tempHashNode = newHashNode(symbol, address);
			//printf("Symbol : \"%s\", Address : %d\n", tempHashNode->symbol, tempHashNode->address); fflush(stdout);
			//insert into the hash function here
			int hashIndex = hashFunction(tempHashNode->symbol, hashTableSize);
			//printf("Has index = %d\n", hashIndex);
			//Insert into the hashTable at the calculated index
			insertHash(&hashTable[hashIndex], tempHashNode);
		}
		
		//If the BST does not contain the supplied hashInstruction
		if ((int) searchFormatBST(head, hashInstruction) == 0) {
			
			//If it is word, then we increment the address by WORD
			if (strcmp(hashInstruction, "word") == 0) {
				address += WORD;
				//printf("\tReserving WORD bytes\n");
			} 
			//If it is resb, then we increment the address by reserveSize BYTEs
			else if (strcmp(hashInstruction, "resb") == 0) {
				if ((reserveSize = atoi(potentialReserveSize)) == 0) {
					fprintf(stderr, "\nReserve size isn't a number.\n exiting...\n");
					exit(-1);
				}
				address += reserveSize * BYTE;
				//printf("Reserving n BYTE bytes\n");
			} 
			//If it is resw, then we increment the address by reserveSize WORDSs
			else if (strcmp(hashInstruction, "resw") == 0) {
				if ((reserveSize = atoi(potentialReserveSize)) == 0) {
					fprintf(stderr, "\nReserve size isn't a number.\n exiting...\n");
					exit(-1);
				}
				address += reserveSize * WORD;
				//printf("Reserving n WORD bytes\n");
			}
				
		} 
		else {
			address += (int) searchFormatBST(head, hashInstruction);
		}
		//Erase the hashInstruction and symbol
		hashInstruction[0] = '\0';
		symbol[0] = '\0';
		//printf("\n\n");		
	}

	//print the hashtable
	printf("\nHash Table:");
	printHashTable(hashTableSize, hashTable);
	printf("\n");
	
	//Close opened files
	fclose(instructionSetFile);
	fclose(programFile);

	//Delete the used BST and hashTable
	deleteBST(head);
	deleteHashTable(hashTableSize, hashTable);

	//print Done
	//printf("\nDone.\n");
}
