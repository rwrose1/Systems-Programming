#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "other.h"
#include "browse.h"
#include "index.h"

/*
	The browse function is a recursive funtion; it returns nothing. There are three arguments taken as parameters: the directory path 
	where browse will begin its recursive tree walk, the outputFile that the indexer functions outputs to, and the outputFileName as so
	the browse function ignores its own output. During the file tree walk, if the browse function finds a file, it call idexer on that 
	file's absolute path to add its data to the inverted index's output file.
*/
void browse(char * directoryPath, FILE * outputFile, char * outputFileName){

	DIR * directory;
	char tempPath[512];
	struct dirent * entry;
	
	directory = opendir(directoryPath);
	
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
			
			strcpy(tempPath, "");
			strcat(tempPath, directoryPath);
			strcat(tempPath, "/");
			strcat(tempPath, entry->d_name);
			
			if(isDir(tempPath)) {
				printf("Directory found: \"%s\".\n", entry->d_name);

                browse(tempPath, outputFile, outputFileName);
                
                printf("\tFinished directory: \"%s\".\n\n", entry->d_name);
			}
			else {
                //file name: entry->d_name);
                
                printf("\tIndexing absolute path: \"%s\".\n", tempPath);

                indexer(tempPath, outputFile, outputFileName);

			}
		}
		
		closedir(directory);
    }

}