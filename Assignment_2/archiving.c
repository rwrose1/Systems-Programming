//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc: 	This file contains two functions, archive which creates an archive file from a set of individual files
//          unarchive function unpacks an archive file and create te respective files.

//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// included external header files
#include "archiving.h"
#include "constants.h"
#include "archivingSize.h"
#include "other.h"

/*
	The archive function returns nothing. It accepts, however, three variables: a string array containing all file names
	that are included in the archiving process, an integer for the number of files included, and a string that is to be the 
	name of the archive created. The archive functions programatically writes details and contents of supplied files to 
	the supplied archivename in the following format: 
		4 bytes containing the number of file; then for each file: 1 byte for the length of the name; the name in string format;
		the size of the contents (in 4 bytes); the actual contents.
*/
void archive(char** fileNames, int numFiles, char* archiveName) {
	//Variables here
	char * tempArchiveName; //the temporary character array containing the archive name
	tempArchiveName = strdup(archiveName); //duplicate data to above array
	FILE * outputFile; //The output file
	FILE * tempFile; //The temp file (input file)
	FILE * fileOfFileNames; //A file to hold only file names of the created archive
	int tempNumOfFiles = numFiles; //Assigning a temporary int the number of files

	//opens a new bin file with new string for writing
	if ((outputFile = fopen(tempArchiveName, "wb")) == NULL){
		fprintf(stderr, "Could not allocate space for the output archive.");
		exit(-1);
	}
	
	//Add number of files to bin
	fwrite(&tempNumOfFiles, SIZEnumOfFilesInArchive, 1, outputFile);
	
	//loop for the number of files
	int i = 0;
	for (i = 0; i < numFiles; i++) {
		
		char * tempFileName; //a character array for the inputfile's name
		tempFileName = strdup(fileNames[i]); //assign the inputfile's name
		
		//Attempt to dynamically allocate space
		if ((tempFile = fopen(tempFileName, "r")) == NULL) {
			fprintf(stderr, "Could not allocate space for %s.\n", tempFileName);
			exit(-1);
		}
		
		unsigned char lengthOfFileName = strlen(tempFileName) + 1; //A new unsigned char variable containing the length of the file name + 1
		
		//Add length of file name to bin
		fwrite(&lengthOfFileName, SIZElengthOfFileName, 1, outputFile);
		
		//Add filename to bin
		fwrite(tempFileName, sizeof(char), lengthOfFileName, outputFile);
		
		//Create and assign a int variable that contains the fileSize of the current file
		int tempSize = (fileSize(tempFile));
		
		//Add the fileSize to the bin
		fwrite(&tempSize, SIZElengthOfFile, 1, outputFile);
			
		int c; //A int variable containing characters to add
		int count = 0; //A count variable to keep track in the loop
		
		//Add character by character to the bin file (while not meeting the end of inputFile)
		while((c = fgetc(tempFile)) != EOF) {
			count++;
			char h = (char)c;
			fprintf(outputFile, "%c", h);
		}
		
		//close the tempFile
		fclose(tempFile);
		
	}
	//Store the file names of the archive in augmented archive
	//That is, filesOf + archivename
	char * fileOfFiles = malloc(strlen("filesOf") + strlen(tempArchiveName) + 1);// dynamic memory allocation
	strcpy(fileOfFiles, "filesOf");// copys "filesOf" into fileOfFiles
	strcat(fileOfFiles, tempArchiveName);// concatenates tempArchiveName with fileOfFiles
	
	printf("\nFile names will be stored in: %s.\n", fileOfFiles);
	
	//opens the file for writing to a binary file
	fileOfFileNames = fopen(fileOfFiles, "wb");

	i = 0;
	for(i ; i < numFiles; i ++){
		fwrite(fileNames[i], sizeof(char), strlen(fileNames[i]), fileOfFileNames);
		fwrite("\n", sizeof(char), 1, fileOfFileNames);
	}
	// closes the file containing the names of the files
	fclose(fileOfFileNames);

	//Close the outputFile
	fclose(outputFile);
	
}//End archive

/*
	The unarchive function returns nothing. It accepts, however, one variable: a string that is the name of the 
	archive to be unarchived. This fucntions creates the files contained in the archive with the correct name, size and 
	contents without compression.
*/
void unarchive(char* archiveFile) {
	
	//Variables here
	char * tempArchiveName; //The temp char array containing the archive name
	int numOfFiles; //Int for the number of files 
	int contentSize; //A int for the length of each file's size
	tempArchiveName = strdup(archiveFile); //Assign the archive name to the temp char array
	FILE * inputFile; //The inputfile
	FILE * tempFile; //The output files
	unsigned char fileNameLength;// size of 1 byte for the length of the file names

	//opens a new bin file with new string for reading
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for %s.\n", tempArchiveName);
		exit(-1);
	}
	
	//Read the number of files into the temp int
	fread(&numOfFiles, SIZEnumOfFilesInArchive, 1, inputFile);

	//For loop for the number of files in the archive
	int i = 0;
	for (i = 0; i < numOfFiles; i++) {
		//Read the length of the file name into the temp int
		fread(&fileNameLength, SIZElengthOfFileName, 1, inputFile);
		
		//Allocate memory for the tempString (the name of the file)
		char * tempString = malloc(fileNameLength * sizeof(char));
		
		//Check for NULL returns
		if (tempString == NULL) {
			fprintf(stderr, "Could not allocate space for new tempString.\n");
			exit(-1);
		}
		
		//Read the name into tempString
		fread(tempString, sizeof(char), fileNameLength, inputFile);

		//Open the determined file for writing
		tempFile = fopen(tempString, "w");
		if (tempFile == NULL) {// if the temp file is null , it will print couldn't open
			fprintf(stderr, "Could not open %s", tempString);			
			exit(-1);
		}
		
		//Read the size of the file into the temp int
		fread(&contentSize, SIZElengthOfFile, 1, inputFile);
		
		//For loop for the contents of each file
		int y = 0;
		int c;
		for (y; y < contentSize; y++) {
			//Read and write each character to the tempFile and from the archive
			fread(&c, sizeof(char), 1, inputFile);
			fwrite(&c, sizeof(char), 1, tempFile);
		}

	
		
		//Close the tempfile (output)
		fclose(tempFile);
		
		//Free the allocated name
		free(tempString);
		
	}
	//Close the archive
	fclose(inputFile);
	
} //End unarchive

