#include <stdio.h>
#include <stdlib.h>

#include "index.h"
#include "other.h"
#include "structs.h"
/*
    The indexer function returns nothing, but takes two arguments as parameters: the absolute path of an input file to added to the supplied FILE * to the
    output file. This function reads data from outputFile, adds data to outputFile, sorts said data and rewrites is back to the outputFile. 
*/
void indexer(char * inputFilePath, FILE * outputFile, char * outputFileName){
    //Note the outputFile has been opened for "a+" currently (appending and reading)
    //To open the outputFile for writing, that is, delete the file and start over use:
    //FILE *freopen(const char *filename, const char *mode, FILE *stream)

    //If the outputFile is empty
    if (fileSize(outputFile) == 0){
        printf("\tThe output file is empty!\n");

        termList * inputList;
        termList * outputList;

        inputList = malloc(sizeof(termList));
        if (inputList == NULL){
            fprintf(stderr, "Could not allocate memory for inputList.");
        }

        outputList = malloc(sizeof(termList));
        if (outputList == NULL){
            fprintf(stderr, "Could not allocate memory for outputList.");
        }

        inputList = readFromFile(inputFilePath); //Reads terms in any order

        //Sort data in memory
        //inputList = sortTerms(inputList); //Sorts list by terms

        //Print sorted data to outputFile
        //printSorted(inputList, outputFile, outputFileName) //Prints sorted list in alphabetical order, keeping order of file counts descending

        deleteTermList(inputList);
        deleteTermList(outputList);
        if (inputList != NULL) free(inputList);
        if (outputList != NULL) free(outputList);
    }
    
    //If the outputFile is not empty
    else{
        printf("\tThe output file is NOT empty!\n");

        termList * inputList;
        termList * outputList;
        termList * newList;

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
        //outputList = readFromIndex(ouputFile, outputFileName); //Reads terms in order

        //Read non-sorted data into memory
        //inputList = readFromFile(inputFilePath); //Reads terms in any order

        //Sort data in memory
        //inputList = sortTerms(inputList); //Sorts list by terms

        //MergeSort latter into former
        //newList = mergeSorted(inputList, outputList); //merges inputList and outputList, keeps terms in alphabetical order

        //Rewrite new merged list into outputFile
        //printSorted(newList, outputFile, outputFileName) //Prints sorted list in alphabetical order, keeping order of file counts descending

        deleteTermList(inputList);
        deleteTermList(outputList);
        deleteTermList(newList);
        if (inputList != NULL) free(inputList);
        if (outputList != NULL) free(outputList);
        if (newList != NULL) free(newList);
    }
}