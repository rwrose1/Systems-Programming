//standard libraries
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//include external header files containing prototypes
#include "other.h"
#include "browse.h"
#include "index.h"

/*
	The browse function is a recursive funtion; it returns nothing. There are three arguments taken as parameters: the directory path 
	where browse will begin its recursive tree walk, the outputFile that the indexer functions outputs to, and the outputFileName as so
	the browse function ignores its own output. During the file tree walk, if the browse function finds a file, it call indexer on that 
	file's absolute path to add its data to the inverted index's output file.
*/
void browse(char * directoryPath,  char * outputFileName){

	DIR * directory;// directory pointer
	char tempPath[512];//max size of the tempPath
	struct dirent * entry;
	//opens the path of the directory and sets it equal to directory
	directory = opendir(directoryPath);
	
	// checks to see if the directory is null, if it is prints an error and terminates
	if(directory == NULL){
        fprintf(stderr, "Couldn't open: \"%s\"\n", directoryPath);
        exit(-1);
    }
	else{
        
		printf("Calling browse on: \"%s\".\n", directoryPath);
		
		
		while((entry = readdir(directory)) != NULL)
		{
			//Checks if name is viable; i.e. NOT "." ".." or the outputFile name
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, outputFileName) == 0){
				continue;
			}
			
			strcpy(tempPath, "");// copies whitespace into tempPath
			strcat(tempPath, directoryPath);//concatenates the path of the directory to the temporary path
			strcat(tempPath, "/");// concatenates the backslash character into the temporary path
			strcat(tempPath, entry->d_name);// concatenates the name of the directory to tempPath
			
			//check is the tempPath is a directory using the isDir function,
			if(isDir(tempPath)) {
				printf("Directory found: \"%s\".\n", entry->d_name);

                browse(tempPath, outputFileName);
                
                printf("\tFinished directory: \"%s\".\n\n", entry->d_name);
			}
			else {
                //file name: entry->d_name);
                
                printf("\tIndexing absolute path: \"%s\".\n", tempPath);
				//calls indexer on the tempPath
                indexer(tempPath,  outputFileName);

			}
		}
		
		closedir(directory);// closes the directory
    }

}