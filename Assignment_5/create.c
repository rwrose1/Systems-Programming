//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the create command.
The role of the create command is that it is used for the creation of new files,
directories and links. Just like the previous commands, this function is its own seperate program, that gets
executed by simpleshell, or it can also be manually executed by when its own executable file is run.

the program supports the following usage with the following arguments depending on the supplied arguments

(1): create -f filepath
it creates an empty file, with the name that is given in the specified path
The file that is created will contain a 6040 permission that is specified in octal.
The pathname that is supplied is either be an absolute or relative path, or just the filename. 

(2): create -d dirpath
 it creates a new directory with the name that is given from the path that is specified.
 A 7050 permission will be specified in octal for this command.

(3): create -h oldname linkname
 its creates a hard link. The name or the path of the existing file is called, oldname.
 While the name or the path of the hard link that is being created is called linkname.

(4): create -s oldname linkname
 it creates a soft link, also known as a symbolic link.
 The name or the path of the existing file is called oldname.
 While the name or the path of the hard link that is being created is called linkname.

 /*
 Output: the output depends on the arguments being supplied by the user when using the create
 command.
*/

//standard c libraries
#include <stdio.h>
#include <stdlib.h>

#include "createFunctions.h"

/*
main function, takes parameters of for the number of arguments
*/
int main( int argc, char *argv[] )  {

	//printf("\n\nIn create...\n");

	// if the number of command line arguments is equal to 1, prints the arguments that are supplied
	if( argc == 2 ) {
		fprintf(stderr, "ERROR: Not enough arguments supplied to create.c.\n");
		exit(-1);
	}
	// if the number of command line arguments is greater than 1, prints to many arguments are supplied
	else if( argc > 2 ) {
	  
		//Case 1: flag is -f, create a file
		if( strcmp(argv[1], "-f") == 0 ) {
		
			//printf("\tFlag \"%s\" Specified\n", argv[1]);
			
			//Error Checks	
			//Too many arguments
			if ( argc > 3 ) {
				fprintf(stderr, "ERROR in create.c: too many arguments.\n");
				exit(-1);
			}
			
			//call createFile function
			createFile(argv[2]);
		}
			
		//Case 2: flag is -d, create a directory
		if( strcmp(argv[1], "-d") == 0 ) {
			
			//printf("\tFlag \"%s\" Specified\n", argv[1]);
			
			//Error Checks
			//Too many arguments
			if ( argc > 3 ) {
				fprintf(stderr, "\tERROR in create.c: too many arguments.\n");
				exit(-1);
			}
			
			//call createDirectory function
			createDirectory(argv[2]);
		}
		
		//Case 3: flag is -h, create a hardlink between argv[2] and argv[3]
		if( strcmp(argv[1], "-h") == 0 ) {
			
			//printf("\tFlag \"%s\" Specified\n", argv[1]);
			
			//Error Checks
			//Too many arguments
			if ( argc > 4 ) {
				fprintf(stderr, "ERROR in create.c: too many arguments.\n");
				exit(-1);
			}
			
			//Too little arguments
			if ( argc != 4) {
				fprintf(stderr, "ERROR in create.c: Not enough arguments.\n");
				exit(-1);
			}
			
			//call createHardLink function
			createHardLink(argv[2], argv[3]);
		}
		
		//Case 4: flag is -s, create a softlink between argv[2] and argv[3]
		if( strcmp(argv[1], "-s") == 0 ) {
			
			//printf("\tFlag \"%s\" Specified\n", argv[1]);
		
			//Error Checks
			//Too many arguments
			if ( argc > 4 ) {
				fprintf(stderr, "ERROR in create: too many arguments.\n");
				exit(-1);
			}
			
			//Too little arguments
			if ( argc != 4) {
				fprintf(stderr, "ERROR in create: Not enough arguments.\n");
				exit(-1);
			}
			
			//call createSoftLink function
			createSoftLink(argv[2], argv[3]);
		}

	  
  	}
   	// if the no arguments are supplied, it will print out that is expects an argument.
   	else {
		fprintf(stderr, "ERRROR: At least two argument expected in create.c.\n");
		exit(-1);
	}
	
	//Exit with 0, program was succesfully completed
	exit(0);
}