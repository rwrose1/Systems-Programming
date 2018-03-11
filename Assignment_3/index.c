//standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//include external header files, containing prototypes
#include "index.h"
#include "other.h"
#include "structs.h"
/*
    The indexer function returns nothing, but takes two arguments as parameters: the absolute path of an input file to added to the supplied FILE * to the
    output file. This function reads data from outputFile, adds data to outputFile, sorts said data and rewrites is back to the outputFile. 
*/
void indexer(char * inputFilePath, char * outputFileName){
    //Note the outputFile has been opened for "a+" currently (appending and reading)
    //To open the outputFile for writing, that is, delete the file and start over use:
    //FILE *freopen(const char *filename, const char *mode, FILE *stream)

	// file pointer for the temporary file
    FILE * tempFile;
	//the name of the output file is opened for appending and reading and is assigned to be equal to tempFile
    tempFile = fopen(outputFileName, "a+");

    //checks if the outputFile is empty
    if (fileSize(tempFile) == 0){
        //printf("\tThe output, \"%s\", is empty!\n", outputFileName);
        //printf("\t\tAdding first entry...\n");
		//inputList and outputList are pointers to the struct termList
        termList * inputList;
        termList * outputList;
        
		// allocates space for the inputlist
        inputList = malloc(sizeof(termList));
		// if the inputlist is empty, error is printed
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }
		//allocates space for the output list
        outputList = malloc(sizeof(termList));
		//if the outputList is empty, error is printed
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

		// reads a supplied file, to the inputList
		
		char * currentFile;
		
		int count = 0;
		int x;
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
		
        inputList = readFromFile(inputFilePath, currentFile);

		//temp is pointer to termList struct
        termList * temp;
		// the contents of temp is equal to the inputList
        temp = inputList;
        
        //printf("\t\tCurrent list:\n");
		//checks to see if temp is not equal to NULL
        while(temp!=NULL)
        {	//tempFileCount is a pointer to the fileCountList
            fileCountList * tempFileCount;
            //printf("\t\t\t\"%s\"", temp->term);
			// the tempFileCount is equal to pointer of filesAndCounts of temp
            tempFileCount = temp->filesAndCounts;
            // checks to see if the count of the temp file is not equal to null
			while(tempFileCount != NULL){
                //printf(" \"%s\" %d\n", tempFileCount->file, tempFileCount->count);
                tempFileCount = tempFileCount->next;
            }
			//temp is equal to a pointer next of temp
            temp=temp->next;
        }

        free(temp);// frees temp

        //Print sorted data to outputFile
        //printSorted(inputList, outputFileName);
        
		
        if (inputList != NULL) deleteTermList(inputList);
        if (outputList != NULL) deleteTermList(outputList);
    }
    
    //If the outputFile is not empty
    else{
        //printf("\tThe output file is NOT empty!\n");

		//inputList, outputList, and newList are all pointers to termList
        termList * inputList;
        termList * outputList;
        termList * newList;
        
		/*
		allocating space for the inputList, outputList and newList,
		if they are null, an error is printed
		*/
        inputList = malloc(sizeof (termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof (termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

        newList = malloc(sizeof (termList));
        if (newList == NULL){
            fprintf(stderr, "Could not allocate memory for newList.");
        }

        //Read sorted data into memory
        outputList = readFromIndex(outputFileName); //Reads terms in order
		
		//prints the contents of the outputList
		//printAll(&outputList);
		
		//Get only the file name
		char * currentFile;
		
		
		int count = 0;
		int x;
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
		
		if (ifFileContained(&outputList, inputFilePath) == 1) {
			//printf("The file is contained! ");
			currentFile = addNumber(currentFile, 1);
			//printf("%s\n", currentFile);
			
		}
		
        //Read non-sorted data into memory
        inputList = readFromFile(inputFilePath, currentFile); //Reads terms in any order

        //Sort data in memory
        //inputList = sortTerms(inputList); //Sorts list by terms
		
		//merges inputList and outputList, keeps terms in alphabetical order
        mergeSorted(&inputList, &outputList);
		
		//prints the contents of the outputList
		//printAll(&outputList);
		
        //Rewrite new merged list into outputFile
        printSorted(outputList, outputFileName); //Prints sorted list in alphabetical order, keeping order of file counts descending

        fclose(tempFile);// close tempFile

        if (inputList != NULL) deleteTermList(inputList);
        if (outputList != NULL) deleteTermList(outputList);
        if (newList != NULL) deleteTermList(newList);
        //if (inputList != NULL) free(inputList);
        //if (outputList != NULL) free(outputList);
        //if (newList != NULL) free(newList);


    }
}
