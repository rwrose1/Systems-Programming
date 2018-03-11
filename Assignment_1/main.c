//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/3/2017
//Course:  	ICSI 402
//Desc:    	This program takes directory full of log files then concatonates them into
//         	a single log file, where the order is based on the time of each log.
//Input:   	The program can take a command line argument specifying the path where the program will execute
//	   		Otherwise, it will execute in the current directory
//Output:  	A .log file and standard output of the printed merge list
//Assumption:	The possible command line argument is assumed to be a unix path to a directory in unix.

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include "structs.h"
#include "headersOne.h"
#include "headersTwo.h"
#include "headersOther.h"

/*
		This is the main function of the mylogger program. It's control structures determines the 
	directory for opening, looks through said directory for log files, reads lines of any log file, using
	parseLine, it finds and then proceeds to add them to a linked list called inlist. Before moving onto another
	log file, if it exist, the main function call mergeLists to add the inlist to a resultlist, 
	subsequently sorting the resulting list as to keep order. After every inlist is created and used, 
	deleteList is called as to free the memory used for inlist. After the control structures have completed, printLines
	is called to print the result list to standard output, and printLinesToFile is called to print the resulting
	list to the file combinedlogs.log.
*/
int main( int argc, char *argv[] ) {

	/* Local variables */
	DIR * dp; //The DIR * dp is a type representing a directory stream supplied in command line args
	struct dirent * d; //The struct dirent * d is a format of directory items used to determine names of files
	FILE * inputFile; //A file structure created to hold the input file
  	FILE * outputFile; //A file structure created to hold the output file
	char tempLine [128]; //A temperary char array that holds each line of a log file
	char * outputName = "combinedlogs.log"; //The name of the outputted file
	char currentDirectory[128]; //A char array that holds the current directory
	char outputPath[128]; //A char array that holds the required outputPath


	/* Declare resultlist head here */
	loglist_t * resultlist = malloc(sizeof(loglist_t));
	if (resultlist == NULL){
		fprintf(stderr, "Failed to allocated memory for head of resultlist.\n");
		exit(-1);
	}

	/* Determine directory */
  	if( argc == 2 ) {
    	if((dp = opendir(argv[1])) == NULL){
      		perror("Error");
      		exit(-1);
		}
		// The directory was supplied
		printf("The directory opened is: \"%s\"\n", argv[1]);
		strcpy(currentDirectory, argv[1]);
		strcat(currentDirectory, "/");
	}
	  
  	else if( argc > 2 ) {
		//There were too many arguments
    	fprintf(stderr, "Too many arguments!.\n");
		exit(-1);
  	}
  
	else {
		//Open the current directory
		if((dp = opendir(".")) == NULL){
			perror("Error");
			exit(-1);
		}
		//The directory opened was the current working one
		//printf("\nThe directory to open is: \".\"\n");
		strcpy(currentDirectory, "./");
    
  	} /* Directory has been determined */
	
	// Determine the path of the output file
	strcpy(outputPath, currentDirectory);
	strcat(outputPath, outputName);
	outputFile = fopen(outputPath, "w");
	  
	/* Read through names of files in opened directory */
	while((d=readdir(dp)) != NULL){

		//Allocate memory for the inlist
		loglist_t * inlist = NULL;
		inlist = malloc(sizeof(loglist_t));
		if (inlist == NULL) {
				fprintf(stderr, "Failed to allocated memory for head of inlist.\n");
				exit(-1);
		}
		
		//Does the file name contain .log
		if(strstr(d->d_name, ".log")){ 

			char filePath[128]; //Create a char array to hold the filepath of the inputfile
			filePath[0] = '\0'; //Reset filepath

			//Determine filePath
			strcpy(filePath, currentDirectory); 
			strcat(filePath, d->d_name);

			//printf("\nFile to be read: \"%s\"\n", d->d_name);
			//puts("Lines to be parsed:");
			errno =  0;
			/* Open the file for reading */
			if((inputFile = fopen(filePath, "r")) != NULL){

				/* Check if the file starts with a # here */
				int countChar = 0;

				inlist->next = NULL;

				/* Read line by line */
				while(fgets(tempLine, sizeof tempLine, inputFile)!= NULL){

					if (countChar == 0){
						if(tempLine[0] != '#'){
							fprintf(stderr, "Does not start with #!.\n");
							exit(-1);
						}
						countChar++;
					}

					/* Look at lines only without hashtags */
					if (strstr(tempLine, "#") != NULL){
						continue;
					}
					// Check if tempLine contains at least two commas
					else if ((containsTwoPlusCommas(tempLine)) == 0){
						fprintf(stderr, "Log entry does not contains at least two commas.\n");
						continue;
					}
					/*
					// Check if tempLine looks like <level>,<timestamp,<message>
					else if ((looksCorrect(tempLine)) == 0){
						fprintf(stderr, "Log entry does not looks like <level>,<timestamp,<message>.\n");
						exit(-1);
					}
					*/
					else{
						/* Parse tempLine into templogline struct here */
						logline_t * templogline = parseLine(tempLine);

						/* Print for piece of mind */
						//fputs(tempLine, stdout);

						/* Add templogline to on end of inlist*/
						inlist = addLast(inlist, * templogline);

					}
				}
				/* inlist is ready */
				//puts("\n");
				//printLines(inlist);

				//merge here
				//puts("Merge attempted.");
				resultlist = mergeLists(resultlist, inlist);
				//printf("\nMERGEDLISTS\n\n");
				
				//printf("\n\nMERGED SORTED LIST\n\n");
				sortList(resultlist);

				/* inlist is deleted */
				deleteList(inlist);
			}
			else if (inputFile == NULL){
				perror("Error");
				exit(-1);
			}
		}
	}


	/* Close directory */
	if(closedir(dp) != 0){
		fprintf(stderr, "Error closing directory.\n");
	}
 
	/* Print the sorted result list to the output file */
 	printToFile(resultlist, outputFile);

	/* Print for piece of mind */
	//fputs("\nDone.", stdout);
	//perror("ERROR");
	fclose(inputFile);

  	puts("The resulting list: \n");
  	printLines(resultlist);
  
	/* Delete resultlist */
	deleteList(resultlist);
 	return 1;

}
