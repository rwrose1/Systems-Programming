//Project: 	Prog3
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/9/2017
//Course:  	ICSI 402
//Desc:    	
//        	
//Input:   	 
//Output:  	
//Assumption:	
//standard libraries
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>

//included external header files containing prototypes
#include "structs.h"
#include "other.h"

/*
isFile check if the supplied path is a file or not, accepts a constant char pointer named path as a parameter
*/
int isFile(const char * path) {
	struct stat s;
	stat(path, &s);
	return S_ISREG(s.st_mode);
}

/*
isDir checks the supplied file path to see if the it is a directory or not, accept a constant char pointer named file_path as a parameter
*/
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

/* this functions checks to if the a supplied term is in the list or not
it takes parameters of the char pointer for the term that is supplied, 
and a pointer to the termList struct for the head of the list
*/
int isTermContained(char * termSupplied, termList * head){
	while (head != NULL){
		/*if the head is not equal to NULL, it compares the supplied term, 
		with the term of the head of the list and checks to see if it is equal
		*/
		if (strcmp(termSupplied, head->term) == 0){
			return 1;
		}
		//if they are equal head is equal the pointer to the next
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
		if(next = NULL){
			free(current);
			//free(current->filesAndCounts);
			return;
		}
		free(current);
		//free(current->filesAndCounts);
		current = next;
	}
	//head = NULL;
}

/* 
The printAll function takes a pointer to the head of a termList as a parameter; its function is to print out all
terms and sublists in the data structure using a nested while loop.
*/
void printAll(struct termList ** head) {
	termList * current = *head;
	fileCountList * currentFile;
	int i = 1;
	//when current is not equal to NULL, current is set to the next pointer, and its contents are printed.
	while (current != NULL) {
		printf("\nTerm %d : \"%s\".\n", i, current->term);
		currentFile = current->filesAndCounts;
		while (currentFile != NULL) {
			printf("File %s : %d\n", currentFile->file, currentFile->count);
			currentFile = currentFile->next;
		}
		current = current->next;
		i++;//increment
	}
}

/*
The insertTerm fuction inserts a fileCountList (third parameter) and a term (second parameter) in order into a linked list with the head 
node head (first paramater). It accomplishes this by loopthing through the list comparing the terms alphabetically and the sublist numberically
(count).
*/
void insertTerm(termList ** head, char * term, fileCountList * filesAndCounts){

	//printf("Called insertTerm on : ");
	
	//pointers to the termList struct for current, previous and the new nodes.
	termList * current;
	termList * newNode;
	termList * prev;
	
	//allocate space for newNode
	newNode = malloc(sizeof(termList));
	//if the newNode is equal to null, error is printed and terminates
	if(newNode == NULL){
		fprintf(stderr, "Could not allocate memory for termList * newNode.\n");
		exit(-1);
	}
        //allocating for space for the term in newNode
	newNode->term = malloc(strlen(term) * sizeof(char));
	//copies term, into newNode->term
	strcpy(newNode->term, term);
	/*
	newFileCount = malloc(sizeof(fileCountList));
	if(newFileCount == NULL){
		fprintf(stderr, "Could not allocate memory for fileCountList * newFileCount.\n");
		exit(-1);
	}

	newFileCount->file = malloc(strlen(tempFileName) * sizeof(char));
	strcpy(newFileCount->file, tempFileName);
	newFileCount->count = 1;
	*/
	//fileAndCounts is the head node of every major list
	newNode->filesAndCounts = filesAndCounts;

	//printf("File: \"%s\" ; Term: \"%s\" ; Count %d.\n", filesAndCounts->file, newNode->term, filesAndCounts->count);

	//Head is equal to null, assign it new node
	if (*head == NULL) {

		//printf("\t\t\t...inserted at head\n"); fflush(stdout);//flush 
		*head = newNode;
		newNode->next = NULL;
		return;
	}

	//If the new term goes before or is equal to head
	if (strcmp(term, (*head)->term) <= 0) {
		//The new term is equal to the head
		if (strcmp(term, (*head)->term) == 0) {
			
			//printf("\t\t\t...incremented at head\n"); fflush(stdout);//flush
			fileCountList * current;//current is a pointer to the struct fileCountList
			current = (*head)->filesAndCounts;
			
			//Increment count in head if contains same file
			while(current != NULL) {
				if (strcmp(current->file, filesAndCounts->file) == 0) {
					current->count++;
					
					//printf("\t\t\t...Finished Incremented\n"); fflush(stdout);//flush
					
					return;
				}
				current = current->next;
			}
			insertFileAndCount(&(*head)->filesAndCounts, filesAndCounts);//inserts a filesAndCount node into the head, merging the given sublist
			
			//printf("\t\t\t...Finished Incremented\n"); fflush(stdout);//flush
			
			return;
			

		} 
		//The term is inserted before the head
		else {
			//printf("\t\t\t...inserted before head\n"); fflush(stdout);/flush
			newNode->next = *head;// the pointer to head is equal to a pointer to next of newNode
			*head = newNode;// newNode is equal to a pointer to the head
		}
		return;
		
	}

	//Inserting or incrementing in body
	current = (*head);// current node is a pointer to head
	// when current is not equal to NULL, compare the term in current, and term to see if current->term is less than term, alphanumerically
	while (current != NULL) {
		if (strcmp(term, (current)->term) <= 0) {
		        
			/*if the term in current, and term are equal, currentFile is a pointer to the struct fileCountLists and it is equal
			filesAndCounts in current
			*/
			if (strcmp(term, (current)->term) == 0) {
				//DO INCREMENT
				//printf("INCREMENTING (In Loop) %s on term %s\n", (current->term), term);
				//printf("\t\t\t...incremented in body\n");
				fileCountList * currentFile;
				currentFile = current->filesAndCounts;
				
				/* when the currentfile is null, checks if currentFile->file and filesAndCounts->file are equal
				 if they are the count in currentfile is incremented */
				while(currentFile != NULL) {
					if (strcmp(currentFile->file, filesAndCounts->file) == 0) {
						currentFile->count++;
						//printf("\t\t\t...Finished Incremented\n"); fflush(stdout);//flush
						return;
					}
					currentFile = currentFile->next;
				}
				//inserts a filesAndCount node into the head, merging the given sublist
				insertFileAndCount(&current->filesAndCounts, filesAndCounts);
				
				//printf("\t\t\t...Finished Incremented\n"); fflush(stdout);//flush
				
				return;
				
			} 
			else {
				//printf("\t\t\t...inserted in body\n");
				newNode->next = current;// current is equal to a pointer to next of newNode
				prev->next = newNode;// newNode is equal to a pointer to the next of prev
				return;
			}

		}
		//current is equal to the previous
		prev = current;
		//current is equal to a pointer next of current
		current = current->next;
	}

	current = (*head);
	while(current->next != NULL){
		//current is equal to a pointer next of current
		current = current->next;
	}
	//newNode is equal to a pointer next of current
	current->next = newNode;
	// the pointer to next of newNode is NULL
	newNode->next = NULL;
	//printf("\t\t\t...added on end.\n");
}

int isEmpty(const char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  return 1;
}

/*
	The function readFromFile returns a pointer to the head of a linked list of termList 
	structs. It accepts two parameters, the input file's absolute path, and a char pointer named currentFile, readFromFile reads through 
	the supplied file, adding the terms to the linked list, the file their from, and the correct count
	(incremented) when required.
*/
termList * readFromFile(char * inputFilePath, char * currentFile) {

	//printf("\t\tAttempting to read from file \"%s\".\n", inputFilePath);
	//printf("\t\tFile contents: \n");
        
	// opens the inputFilePath, for readding
	FILE * inputFile = fopen(inputFilePath, "r");
	// if inputFile is equal to null, prints an error and terminates
	if(inputFile == NULL){
		fprintf(stderr, "Could not allocate space for: %s.\n", inputFilePath);
		exit(-1);	
	}
	// size of the line
	char line[1024]; 
	char * token;// token for tokenizing
	int i;// count for the loop
	
	// head is a pointer to the termList struct, has a value of NULL
	termList * head = NULL;
	
	// fgets, get the next line from inputfile, checks if it is not equal to NULL, and if it is, prints the line.
	while(fgets(line, 1024, inputFile) != NULL){
		//printf("\t\t\t%s", line);
	}

	//printf("\n");
	
	rewind(inputFile);// returns the file positions to the beginning of the inputFile
	/*
	char * currentFile;
	int x = 0, count = 0;


	
	for(x; x < strlen(inputFilePath) + 1; x++){
		if(inputFilePath[x] == '/'){
			count ++;
		}
	}

	currentFile = strstr(inputFilePath, "/");
	
	for(x = 0; x < count; x ++){
		currentFile = strstr(currentFile, "/");
		++currentFile;
	}
	*/
	//printf("\t\tCurrent file: \"%s\".\n", currentFile);

	//printf("\t\tFormatted file contents: \n");
        
	// fgets, get the next line from inputfile, checks if it is not equal to NULL, and if it is, prints the line.
	while(fgets(line, 1024, inputFile) != NULL){
		// if the line is empty, continue
		if (isEmpty(line)) continue;
                
		//for loop for char line, if it hits an non alphanumeric number, converts it to whitespace
		for (i = 0; i < strlen(line); i++) {
			
			if (!isalnum(line[i])) {
				line[i] = ' ';
			}
			
		}

		//printf("\t\t%s\n", line);
		
		token = strdup(line);// duplicates line into token
		token = strtok(token, " ");// breaks line into token if there is white space
		
		fflush(stdout);// flush
		//printf("\t\t\tTerms: \n");
		
		int j;// loop integer for for loop
		// while the token is not null, it gets the file and count and inserts them into a sublist
		while(token) {

			
			//standardizes the terms
			for(j = 0; token[j]; j++){
				token[j] = tolower(token[j]);  
			}

			//printf("\t\t\t\"%s\" ", token);
			//allocates memory to newFileCount
			fileCountList * newFileCount = malloc(sizeof(fileCountList));
			if(newFileCount == NULL){
				fprintf(stderr, "Could not allocate memory for fileCountList * newFileCount.\n");
				exit(-1);
			}

			//copy over values then insert
			newFileCount->file = malloc(strlen(currentFile) * sizeof(char));
			strcpy(newFileCount->file, currentFile);
			newFileCount->count = 1;
			//inserts new file and fileCount into the temp head
			insertTerm(&head, token, newFileCount);
			token = strtok(NULL, " ");
			
		}

		//printf("\n");
	}

	fclose(inputFile);
	return head;

}

/*
	This function prints all the counts of an inputted fileCountList, taking a pointer to the head as a parameter.
*/
void printAllCount(fileCountList ** head) {
	//the current node, to get the info from
	fileCountList * current = *head;
	//printf("It is here!\n");
	//while current != null, print the data in current
	while(current != NULL) {
		printf("File Name: %s %d\n", current->file, current->count);
		current = current->next;
	}
}

/*
	The function readFromIndex returns a pointer to the head of a linked list of termList 
	structs. It accepts two parameters, the FILE that is to be read from and its name for re-
	opening. readFromIndex reads through the supplied file, adding data in order to the linked 
	list when required.
*/
termList * readFromIndex(char * outputFileName){
	//printf("\t\tAttempting to read from file \"%s\".\n", outputFileName);
	
	FILE * inputFile = fopen(outputFileName, "r"); //opens inputfilename for reading, if null, it exits
	if (inputFile == NULL) {
		fprintf(stderr, "ERROR: could not open inputFile");
		exit(-1);
	}
	char line[1024]; //the line to be read
	char * token; //the string that will be tokenized, is a duplicate of line
	char * tempTerm; //the char * to hold the term
	char * end1; //the storage variable for strtok_r
	char * tempFileName; //The temp file name for each term
	int tempCount; //The count for each file
	
	termList * head = NULL; //The list to be returned
	
	fileCountList * fileCountHead = NULL; //The sublist to be put into the temp term list
	
	while (fgets(line, 1024, inputFile) != NULL) {
		token = strdup(line); //duplicates line into token
		token[strlen(token) - 1] = '\0'; //Sets the newline character to null
		//printf("\t\t\tLINE : %s\n", token);
		
		token = strtok_r(token, " ", &end1); //tokenizes token by the whitespace character
				
		//when the list starts, this is where the tempTerm is given
		if (strcmp(token, "<list>") == 0) {
			
			token = strtok_r(NULL, " ", &end1);
			tempTerm = strdup(token);
			
			//printf("\n\t\t\tList start, \"%s\" is the term.\n", tempTerm);
			
			continue;
			
		}
		//This is the end of the list, this is where the tempTerm list is opened, initialized, and inserted into the full list
		if (strcmp(token, "</list>") == 0) {
			
			//printf("\t\t\tList End, insert in head list\n");
			
			//printAllCount(&fileCountHead);
			
			insertTerm(&head, tempTerm, fileCountHead);
			
			deleteFileCountList(&fileCountHead);
			fileCountHead = NULL;
			
			continue;
			
		}
		
		//printf("\t\t\t\tList : ");
		//This is where all the fileCountLists are added, while token != null
		while (token) {
			
			tempFileName = strdup(token);
			
			//take a token from the lien
			token = strtok_r(NULL, " ", &end1);
			
			//convert token to an int
			int count = atoi(token);
			//Alocates space for new node
			fileCountList * newNode = malloc(sizeof(fileCountList));
			
			if (newNode == NULL) {
				fprintf(stderr, "ERROR IN readFromIndex: could not allocate newNode\n");
				exit(-1);
			}
			
			
			//allocate space for a new Node and then insert
			newNode->file = malloc(strlen(tempFileName) * sizeof(char));
			strcpy(newNode->file, tempFileName);
			newNode->count = count;
			
			//printf("\n\t\t\t\t\"File name : %s, count : %d\" \n", newNode->file, newNode->count); fflush(stdout);
			token = strtok_r(NULL, " ", &end1);
			
			insertFileAndCount(&fileCountHead, newNode);
		
		}
		
		//printf("\n");
		
	}
	
	//printAll(&head);
	
	return head;
	
	//printf("\n");
	
}

/*
	The function mergeSorted takes a pointer to two head nodes of termList structs, both are already 
	sorted. It then creates and returns a new pointer to the head of a new termList struct that contains values
	from both supplied linked lists in order.s
*/
void mergeSorted(termList ** inputList, termList ** outputList) {
	//printf("... Attempting Merge\n");
	
	termList * current; //the current node, each term is inserted into ouput list
	
	current = *inputList; //initializes current
	
	//while current != null, insert currents term and filesAndCounts into the outputList
	while (current != NULL) {
	//	printf("Term to be merged : %s\n", current->term);
		insertTerm(outputList, current->term, current->filesAndCounts);
		current = current->next;
		}
	
}

/*
	The function printSorted returns nothing. It takes three parameter: One, a pointer to the head
	of a linked list that is to be printed in the correct format to the output file that is supplied as
	well - Two. Three, the name of the outputFile is supplied for reopening when required.
*/
void printSorted(termList * inputList, char * outputFileName){
	FILE * outputFile;

	//This erases the current outputFile
	outputFile = fopen(outputFileName, "w");
	if(outputFile == NULL){
		fprintf(stderr, "Could not allocate memory for: %s.\n", outputFileName);
	}

	//create a temp and assign to head
	termList * temp;
	temp = inputList;

	//loop through outer list
	while(temp!=NULL)
	{
		//print to the file
		fprintf(outputFile, "<list> %s\n", temp->term);
		fileCountList * tempFileCount;
		tempFileCount = temp->filesAndCounts;
		//loop through inner list
		while(tempFileCount != NULL){
			fprintf(outputFile, "%s %d ", tempFileCount->file, tempFileCount->count);
			tempFileCount = tempFileCount->next;
		}
		fprintf(outputFile, "\n");
		fprintf(outputFile, "</list>\n");
		temp=temp->next;
	}

	fclose(outputFile);
}


/*
This function returns nothing, and adds a fileCountList into a filefileCount list array, such being its parameters.
*/
void insertFileAndCount(fileCountList ** head, fileCountList * tempNode){
//printf("\t\t\t\tAttempting incrementation of File \"%s\"\n", tempNode->file);
	
	//loop through the outer list
	if(tempNode->next != NULL) {
		//printf("MULTIPLE NODES IN TEMPNODE\n"); fflush(stdout);
		
		//assign temp nodes
		fileCountList * curTemp = tempNode;
		fileCountList * temp;
		
		//loop through inner list
		while (curTemp != NULL) {
			temp = curTemp;
			temp->next = NULL;
			
			//insert
			insertFileAndCount(&(*head), temp);
			
			curTemp = curTemp->next;
		}
		return;
	}
	
	//special case if the head is null
	if (*head == NULL) {
		//printf("\t\t\t\t... %s inserting into head\n", tempNode->file);
		*head = malloc(sizeof(fileCountList));
		*head = tempNode;
		return;
	}
	
	//if the count is less then the head insert before head
	if ((*head)->count < tempNode->count) {
		//printf("\t\t\t\t... replacing head");
		tempNode->next = *head;
		*head = tempNode;
		return;
	}
	
	//printf("\t\t\t\t... %s inserting into list\n", tempNode->file);
	
	fileCountList * current = *head;
	fileCountList * prev;
	
	//loop through inner list
	while(current != NULL) {
		if (current->count < tempNode->count) {
			//sort (swap)
			prev->next = tempNode;
			tempNode->next = current;
			break;
		}
		prev = current;
		current = current->next;
	}
	prev->next = tempNode;
	
	
}
/*
  addNumber returns a char * to the new augmented string that has been created by the supplied name and the current input,
  the character to be inputted or changed.
*/
char * addNumber(char * archiveName, int currentArchive){
  if(strstr(archiveName, ".") == NULL){
    char * newName; char c; int length;
    char * tempName;
    
    //There is no extension
    if(currentArchive > 1){
      //change the number
      length = strlen(archiveName) + 1;// value of the length is equal to the length the name of the archive +1
      newName = strdup(archiveName);// duplicate the name of archive into new name
      c = currentArchive + '0';
      newName[length-1] = c;
      newName[length] = '\0';
      tempName = strdup(newName);// duplicates the newName into tempName
    }
    else{
      //add the number one
      length = strlen(archiveName) + 1; 1;// value of the length is equal to the length the name of the archive +1
      newName = malloc((length * sizeof(char)) + 1);//dynamic memory allocation
      c = currentArchive + '0';
      strcpy(newName, archiveName);// copy archiveName into newName
      newName[length-1] = c;
      newName[length] = '\0';

      tempName = strdup(newName);// duplicates newName into tempName
      free(newName);// frees newName
    }
    return tempName;
  }
  else{


    char * pos; int index; char c; int length, strlength;// variable to position, the index, the length, and the string length
    char * newName, tempName, * extension;// variable for newName, the temp name, the extension
    //There is an extension
    if(currentArchive > 1){
        length = strlen(archiveName) + 1;
        newName = strdup(archiveName);
        //Change the number
        index = 0;
        
        strlength = strlen(newName);// gets the length of newName
        length = strlen(extension = strstr(newName, "."));
        pos = strchr(archiveName, '.');// searches for a . in the name of the archive, postion is set to that location
        index = (int)(pos - archiveName);
        c = currentArchive + '0';
        newName[strlength - length] = c;

        newName[index] = c;
        newName[index + 1] = '\0';

        strcat(newName, pos);// concatenates position with newName
    }    
    else{
      //Find the pos before the extension and add the number 1
      length = strlen(archiveName) + 1;
      newName = malloc((length * sizeof(char)) + 1);// dynamic memory allocation allocation
      c = currentArchive + '0';
      
      pos = strchr(archiveName, '.');
      //extension = strdup(pos);
      index = (int)(pos - archiveName);
      strncpy(newName, archiveName, index);
      //strcpy(newName, archiveName);
      newName[index] = c;
      newName[index + 1] = '\0';
      
      newName = strcat(newName, pos);// conatenate pos with newName
    }
  
    return newName;
    free(newName);
  }
} //End addNumber

/*
	ifFileContained returns an int (1 if the file is contained / 0 if not) and takes a pointer to the head of an outer 
	termList and the current path as a string.
*/
int ifFileContained(termList ** head, char * currentFilePath){
	
	char * currentFileName; //a string to hold the file name
	int x = 0, count = 0; //int for loop and a count for loop

	//How many /'s are there in the supplied string
	for(x; x < strlen(currentFilePath) + 1; x++){
		if(currentFilePath[x] == '/'){
			count ++;
		}
	}

	//dup
	currentFileName = strstr(currentFilePath, "/");

	//Find the file name
	for(x = 0; x < count; x ++){
		currentFileName = strstr(currentFileName, "/");
		++currentFileName;
	}

	//declare a temp list struct for the head of each list
	termList * current = *head;
	fileCountList * currentFile;
	int i = 1; //count in for loop
	//loop through outer list
	while (current != NULL) {
		currentFile = current->filesAndCounts;
		//loop through inner list
		while (currentFile != NULL) {
			if((strcmp(currentFile->file, currentFileName)) == 0){
				//the file is contained
				return 1;
			}
			currentFile = currentFile->next;
		}
		current = current->next;
		i++;
	}

	//if the program gets here, it was not contained
	return 0;
}	
