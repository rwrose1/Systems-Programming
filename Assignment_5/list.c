//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: the role of the list command is that prints to the standard output, the information
about the files that are contained in a directory. List is a separate program, so it can be called
manually, by executing its own executable file or from simpleshell.

the program supports the following usage with the following arguments depending on the supplied arguments

(1): list pathname
 when the pathname is a an absolute or relative pathname to a directory. this command
 will print all of the non hidden file names that are contained in a specified directory,
 with one file per a line. Any file names that don't start with a dot are considered to
 be hidden files.

(2): list -i pathname
The -i flag is an indication that any extra information needs to be printed.
The informationthat is printed from this command include the name of the file with
one file per a line. The size of the file stated in bytes, the permission associated
it printed in octal format, and the inode number that is stated as a decimal integer.

(3): list -h pathname
the -h flag is an indication that only hidden files names in a specified directory 
should be printed.

(4): list, list -i, list -h
 any of these commands function the same as the command above, but they are executed
 in the current working directory instead a path that is specified.

/*
Output: the output depends on the arguments being supplied by the user when using the list
command.
*/

//standard c libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

//included external header files containing prototypes
#include "listFunctions.h"

//main function, takes parameters of for the number of arguments

int main( int argc, char *argv[] )  {
	
	//Variables
	char dirPath[255]; //The path name for the directory.
	
	printf("\n");
	
	//saved is a stored file descriptor for stdout
	//tempOut is a store file descriptor for the supplied file
	int saved; int tempOut; 
	
	if(argc < 2){
		strcpy(dirPath, ".");
		printNames(dirPath);
	}
	// if the number of command line arguments is equal to 2
	else if(argc == 2) {
	        //if the 2nd argument supplied is equal to -i, printDetails function is called
		if (strcmp(argv[1], "-i") == 0){
			strcpy(dirPath, ".");
			printDetails(dirPath);
		}
		 //if the 2nd argument supplied is equal to -h, printHidden function is called
		else if (strcmp(argv[1], "-h") == 0){
			strcpy(dirPath, ".");
			printHidden(dirPath);
		}
		else if (checkDirectory(argv[1]) == 0){
			fprintf(stderr, "ERROR: Supplied arg. to list is not a directory or known parameter.\n");
			exit(-1);
		}
		else{
			strcpy(dirPath, argv[1]);
			printNames(dirPath);
		}
	}
    //if the number of arguments supplied is equal to 3 
    else if(argc == 3) {
      	//Case 2: flag is -i
	  	if (strcmp(argv[1], "-i") == 0) {
			//Duplicate dirPath
			if(checkDirectory(argv[2]) == 0){
				fprintf(stderr, "ERROR: Supplied arg. to list is not a directory.\n");
				exit(-1);
			}
			strcpy(dirPath, argv[2]);
			printDetails(dirPath);
		}
	 	//Case 3: flag is -h
	  	else if (strcmp(argv[1], "-h") == 0) {
			//Duplicate dirPath
			if(checkDirectory(argv[2]) == 0){
				fprintf(stderr, "ERROR: Supplied arg. to list is not a directory.\n");
				exit(-1);
			}
			strcpy(dirPath, argv[2]);
			printHidden(dirPath);
		}
		else if (strcmp(argv[1], ">") == 0){

            //Open (create) the supplied file
            tempOut = open(argv[2], O_WRONLY | O_APPEND | O_CREAT, 0644);
			if(tempOut < 0){
				fprintf(stderr, "ERROR: unable to open supplied file.\n");
				exit(-1);
			}
			
            //store the file descriptor for stdout
            saved = dup(1);

            //redirect output
            dup2(tempOut, 1);
			
			//Call printNames
			strcpy(dirPath, ".");
			printNames(dirPath); 
           
            //return output to normal
			dup2(saved, 1);

			//close file descriptors
            close(saved);
            close(tempOut);
		}
	}
	else if(argc == 4){
		if (strcmp(argv[1], "-h") == 0){

			if (strcmp(argv[2], ">") == 0) {
				//Open (create) the supplied file
				tempOut = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0644);
				if(tempOut < 0){
					fprintf(stderr, "ERROR: unable to open supplied file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//Call printNames
				strcpy(dirPath, ".");
				printHidden(dirPath); 
			
				//return output to normal
				dup2(saved, 1);

				//close file descriptors
				close(saved);
				close(tempOut);
			
			} else {
				fprintf(stderr, "ERROR unknown flag.\n");
				exit(-1);
			}
		}
		else if (strcmp(argv[1], "-i") == 0){
            //Open (create) the supplied file
		   
			if (strcmp(argv[2], ">") == 0) {
			
				tempOut = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0644);
				if(tempOut < 0){
					fprintf(stderr, "ERROR: unable to open supplied file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//Call printNames
				strcpy(dirPath, ".");
				printDetails(dirPath); 
				
				//return output to normal
				dup2(saved, 1);

				//close file descriptors
            	close(saved);
            	close(tempOut);

			} else {
				fprintf(stderr, "ERROR unknown flag.\n");
				exit(-1);
			}
			
		}
		else{
			
			if(checkDirectory(argv[1]) == 0){
				fprintf(stderr, "ERROR: Supplied arg. to list is not a directory.\n");
				exit(-1);
			}
			if (strcmp(argv[2], ">") == 0) {
				//Open (create) the supplied file
				tempOut = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0644);
				if(tempOut < 0){
					fprintf(stderr, "ERROR: unable to open supplied file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//Call printNames
				strcpy(dirPath, argv[1]);
				printNames(dirPath); 
			
				//return output to normal
				dup2(saved, 1);

				//close file descriptors
            	close(saved);
            	close(tempOut);
			
			} else {
				fprintf(stderr, "ERROR unknown flag.\n");
				exit(-1);
			}
		}
	}
	//if the number of arguments supplied is equal to 5
	else if (argc == 5){
		/*if the 2nd argument supplied is equal to -h, then the 3rd argument is checked to see if it is
		a working directory*/
		if (strcmp(argv[1], "-h") == 0){

			if(checkDirectory(argv[2]) == 0){
				fprintf(stderr, "ERROR: Supplied arg. to list is not a directory.\n");
				exit(-1);
			}
			
			//if the 4th argument supplied is >
			if (strcmp(argv[3], ">") == 0) {

				//Open (create) the supplied file
				tempOut = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
				//if tempOut is less than zero, print error and terminate
				if(tempOut < 0){
					fprintf(stderr, "ERROR: unable to open supplied file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//Call printNames
				strcpy(dirPath, argv[2]);
				printNames(dirPath); 
			
				//return output to normal
				dup2(saved, 1);

				//close file descriptors
            	close(saved);
            	close(tempOut);
			//if the supplied flag didn't meet any of the previous condition, error is printed out stating unknown flag.
			} else {
				fprintf(stderr, "ERROR unknown flag.\n");
				exit(-1);
			}
		}
		else if (strcmp(argv[1], "-i") == 0){
			//checks if the 3rd argument supplied is a directory, while if the 2nd argument supplied is -i
			if(checkDirectory(argv[2]) == 0){
				fprintf(stderr, "ERROR: Supplied arg. to list is not a directory.\n");
				exit(-1);
			}

			if (strcmp(argv[3], ">") == 0) {
				//Open (create) the supplied file
				tempOut = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
				if(tempOut < 0){
					fprintf(stderr, "ERROR: unable to open supplied file.\n");
					exit(-1);
				}
				
				//store the file descriptor for stdout
				saved = dup(1);

				//redirect output
				dup2(tempOut, 1);
				
				//Call printNames
				strcpy(dirPath, argv[2]);
				printNames(dirPath); 
			
				//return output to normal
				dup2(saved, 1);

				//close file descriptors
            	close(saved);
            	close(tempOut);
			
			} else {
				fprintf(stderr, "ERROR unknown flag.\n");
				exit(-1);
			}
		}
		else{
			fprintf(stderr, "ERROR: unknown supplied flag.\n");
			exit(-1);
		}
	}
    // if the no arguments are supplied, it will print out that is expects an argument.
  	else {
    	fprintf(stderr, "ERROR: Too many arguments supplied to list.c.\n");
		exit(-1);
    }

	//Exit with 0, program was succesfully completed
	exit(0);
}
