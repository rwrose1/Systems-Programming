//Project: 	Prog1
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	10/19/2017
//Course:  	ICSI 402
//Desc:    	A function to handle the -l flag and a function to handle the - v flag.
//Input:
//Output:
//Assumption:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "archivingTwo.h"
#include "other.h"
#include "constants.h"
#include "archivingSize.h"

// function to handle -l flag
/*
  This function takes the archiveName, and opens the archive. If the archive exists, this will
  print the total size of the archive file, the names of all the individual files in the archive,
  and their respective sizes. it takes parameters archiveName.
*/
void printArchiveDetails(char* archiveName) {
	
	//Variables here
	char * tempArchiveName;
	int numOfFiles;
	unsigned char fileNameLength;
	long contentSize, totalSize;
	tempArchiveName = strdup(archiveName);
	FILE * inputFile;
	int fileDetectedCount = 0;

	//opens a new bin file with new string for reading
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		fprintf(stderr, "Could not allocate space for the input archive.");
		exit(-1);
	}
	//makes totalSize equal to fileSize that takes a parameter named inputFile
	totalSize = fileSize(inputFile);
    //prints the total size of the entire archive
	printf("\nTotal size of %s: %ld bytes.\n", tempArchiveName, totalSize);
    //reads number of files from the .bin file
	fread(&numOfFiles, SIZEnumOfFilesInArchive, 1, inputFile);

	printf("\nNumber of Files: %d\n", numOfFiles);
	//for loop, that loops through the file.
	int i = 0;
	for (i = 0; i < numOfFiles; i++) {
		fread(&fileNameLength, SIZElengthOfFileName, 1, inputFile);
		//printf("%d\n", fileNameLength);
		//dynamic memory allocation for the name of the file
		char * tempString = malloc(fileNameLength * sizeof(char));
		//checks if you can't allocate, then terminates
		if (tempString == NULL) {
			exit(-1);
		}
		//reads the file name into tempString
		fread(tempString, sizeof(char), fileNameLength, inputFile);
		//reads the content size from the .bin file.
		fread(&contentSize, SIZElengthOfFile, 1, inputFile);
		// prints the filename and the size
		printf("File Name: %s; Size (in bytes): %ld\n", tempString, contentSize);
		//seeks to the next file
		fseek(inputFile, contentSize, SEEK_CUR);

		//free
		free(tempString);
	}
	
} //End details

///function to handle -v flag
/*
  Takes the archiveName, and checks to see if all the fileNames are contained within the archive.
  If the archive correctly contains all the files, then "Archive verified" is printed to the console.
  If the archive is missing data, then the program will print "Archive is missing X bytes" to the console.
  If the archive's data is incorrect, then the program will print "Archive is corrupted."
  parameters: fileNames are all the files supplied by the user
			  numFiles is the number of files supplied by the user
			  archiveName is the name of the archive to be verified
*/
void verifyArchive(char ** fileNames, int numFiles, char * archiveName) {
		
//Variables
	char * tempArchiveName = strdup(archiveName);// char pointer to the name of the archive
	FILE * inputFile, * tempFile;// file pointers to inputfile and tempfile
	long contentSizeArchive, contentSizeFile;// size of the content and size of the file
	int index, archiveNumOfFiles;// index of the filename and number of file in archive
	long missingBytes = 0;// number of missing bytes
	int fileDetectedCount = 0;// counts of the appropriate number of files was detected.
	long totalBytes = 0;

	unsigned char fileNameSize, archiveNameSize;

	//opens a new bin file with new string for writing
	if ((inputFile = fopen(tempArchiveName, "rb")) == NULL){
		printf ("Error opening file: %s.\n", tempArchiveName);
		exit(-1);
	}
	
	//printf("\nNum Files to check %d: ", numFiles);
 
	//Reads in the archive num of files, and passes the archive pointer
	fread(&archiveNumOfFiles, sizeof(int), 1, inputFile);
	//printf("\nNumber of files given by the archive: %d.\n", archiveNumOfFiles);

	//Determine if there is a missing number of bytes
	if(numFiles == archiveNumOfFiles){
		//The same amount of files are supplied that are in the archive

		//Calculate the bytes in the archive
		long totalArchiveSize = fileSize(inputFile);
		char * tempString;
		int bytesPerFile[numFiles], x = 0;
		//Calculate the bytes in the files
		for(x; x<numFiles; x++){
			if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
				fprintf(stderr, "Could not allocate space for a new tempFile.");
					exit(-1);
				}
			tempString = strdup(fileNames[x]);
			int currentBytes = 0;
			//Bytes for file name's length:
			//Currently: 1 bytes
			currentBytes += SIZElengthOfFileName;
		
			//Bytes for file name
			//Currently: 1 + fileNames[x] length
			currentBytes += 1 + strlen(tempString);
		
			//Bytes for content size
			//Currently 4 bytes
			currentBytes += SIZElengthOfFile;
		
			//Bytes for contents
			//Currently fileSize([x]);
			currentBytes +=  fileSize(tempFile);
		
			//Store in bytesPerFile array
			bytesPerFile[x] = currentBytes;

			totalBytes += bytesPerFile[x];
		
			//Close it
			fclose(tempFile);
		  	}

		  	printf("\nThe file size of the archive: %ld.\n", totalArchiveSize);
			printf("The size of the supplied files: %ld + %d (for SIZEnumOfFilesInArchive).\n", totalBytes, SIZEnumOfFilesInArchive);
			  
			int missingBytes = (totalBytes + SIZEnumOfFilesInArchive) - totalArchiveSize;
			if (missingBytes != 0){
				printf("The archive is missing %d bytes.\n", missingBytes);
				return;
			}
		}
	else{
		//Calculate the bytes in the archive
		long totalArchiveSize = fileSize(inputFile);
		char * tempString;
		int bytesPerFile[numFiles], x = 0;
		//Calculate the bytes in the files
		for(x; x<numFiles; x++){
			if ((tempFile = fopen(fileNames[x], "r")) == NULL) {
				fprintf(stderr, "Could not allocate space for a new tempFile.");
					exit(-1);
				}
			tempString = strdup(fileNames[x]);
			int currentBytes = 0;
			//Bytes for file name's length:
			//Currently: 1 bytes
			currentBytes += SIZElengthOfFileName;
		
			//Bytes for file name
			//Currently: 1 + fileNames[x] length
			currentBytes += 1 + strlen(tempString);
		
			//Bytes for content size
			//Currently 4 bytes
			currentBytes += SIZElengthOfFile;
		
			//Bytes for contents
			//Currently fileSize([x]);
			currentBytes +=  fileSize(tempFile);
		
			//Store in bytesPerFile array
			bytesPerFile[x] = currentBytes;

			totalBytes += bytesPerFile[x];
		
			//Close it
			fclose(tempFile);
			}
			  
			//printf("\nThe file size of the archive: %ld.\n", totalArchiveSize);
			//printf("The size of the supplied files: %ld + %d (for SIZEnumOfFilesInArchive).\n", totalBytes, SIZEnumOfFilesInArchive);
			
			//Determine the missing bytes
			
			//total not supplied bytes given by subtracting totalArchiveSize minus the totalSupplied file bytes
			long totalNOTsupplied = totalArchiveSize - totalBytes;
			//printf("Total supplied bytes : %ld.\n", totalArchiveSize);
			//printf("Total Bytes : %ld\n", totalBytes);
			//printf("Total NOT supplied bytes = %ld\n", totalNOTsupplied);

			char * fileOfFiles = malloc(strlen("filesOf") + strlen(tempArchiveName) + 1);
			strcpy(fileOfFiles, "filesOf");
			strcat(fileOfFiles, tempArchiveName);
			
			//printf("\nFile names will be stored in: %s.\n", fileOfFiles);

			if ((tempFile = fopen(fileOfFiles, "rb")) == NULL) {
				fprintf(stderr, "Could not allocate memory for %s\n", fileOfFiles);
				exit(-1);
			}

			long count = 0; //Count of bytes per file
			char buffer[SIZEmaxFileName]; //The string buffer that get used to read in file names
			FILE * notSupplied; //the file pointer to open the not supplied files

			// while fgets does not return null, check and see if buffer is contained in the arguments, then add to 
			//count if it is.
			while ((fgets(buffer, SIZEmaxFileName, tempFile)) != NULL) {
				//printf("Retrieved file name %s\n", buffer);
				char * pos = strstr(buffer, "\n");
				pos[0] = '\0';


				if (checkIfContains(fileNames, numFiles, buffer) == -1) {
					if ((notSupplied = fopen(buffer, "rb")) == NULL) {
						fprintf(stderr, "Could not allocate memory for \"%s\"\n", buffer);
						exit(-1);
					}
					//printf("%s will be added to the sum of files not supplied.\n", buffer);
					count += fileSize(notSupplied);
					count += SIZElengthOfFile;
					count += SIZElengthOfFileName;
					count += strlen(buffer) + 1;
					fclose(notSupplied);
				}

			}

			//printf("the total bytes of the unsupplied files : %ld.\n", count);
			
			//The diffrence and the awnser to the missing bytes problem
			long difference = (count + SIZEnumOfFilesInArchive) - totalNOTsupplied;

			fclose(tempFile);
			
			//If diffrence is not 0, then the archive is missing "diffrence" bytes.
			if(difference != 0){
				printf("\nThe archive is missing %ld bytes.\n", difference);
				return;
			}

		}
	
	rewind(inputFile);
	//Reads in the archive num of files, and continues the archive pointer
	fread(&archiveNumOfFiles, SIZEnumOfFilesInArchive, 1, inputFile);

	if (archiveNumOfFiles < numFiles){
		fprintf(stderr, "Archive is corrupted.\n");
		exit(-1);
	}

	//For loop for the number of files of the archive
	int i;
	int y = 0;
	for (i = 0; i < archiveNumOfFiles; i++) {
		
		//getLength of FileName #i
		fread(&fileNameSize, SIZElengthOfFileName, 1, inputFile);

		if (fileNameSize < 1 || fileNameSize > SIZEmaxFileName){
			fprintf(stderr, "Archive is corrupted.\n");
			exit(-1);
		}
		
		//printf("\narchiveFileNameS: %d\n", archiveFileNameS);
		// dynamic memory allocation for the tempString
		char * tempString = malloc(fileNameSize * sizeof(char));
		if (tempString == NULL) {
			exit(-1);
		}
		//reads into tempString
		fread(tempString, sizeof(char), fileNameSize, inputFile);
		//prints out fileNameArchive
		//printf("\n%s\n", tempString);
		
		//reads in the content size
		fread(&contentSizeArchive, SIZElengthOfFile, 1, inputFile);  
   		
		//If tempString is contained in fileNames, go on, if not, move the file pointer and continue.
		if ((index = checkIfContains(fileNames, numFiles, tempString)) == -1) {
			fseek(inputFile, contentSizeArchive, SEEK_CUR);
			continue;
		}
		//comment files detected.
		fileDetectedCount++;
		//Compare the file contents
		
		//printf("File Name: %s\n", fileNames[index]);
		//Open tempFile
		if ((tempFile = fopen(fileNames[index], "r")) == NULL) {
			fprintf(stderr, "Could not allocate space for: %s.\n", fileNames[index]);
			exit(-1);
		}
		
		int count = 0;
		int cArchive, cFile;
		
		while(count < contentSizeArchive) {
			//Compare each char, if char is different print corrupted and then return
			cArchive = fgetc(inputFile);
			cFile = fgetc(tempFile);
			count++;
			
			if (cArchive != cFile) {
				printf("\nArchive is corrupted.\n");
				return;
			}
			
		}

		//necessary freeing and closing
		fclose(tempFile);
		free(tempString);
	}
	
	fclose(inputFile);
	printf("\nArchive verified.\n");
	return;
	
}