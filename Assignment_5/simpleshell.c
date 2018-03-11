//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: This program contains the main function that checks the number of supplied arguments, and executes the command based the the arguments supplied, if an 
incorrect argument or too many or too few arguments are supplied error is printed.
 /*
 Output: the output depends on the arguments being supplied by the user when using the create
 command.
*/


//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// included external header files containing prototypes.
#include "input.h"

/*
the main function checks the number of supplied arguments, and executes the command based the the arguments supplied, if an 
incorrect argument or too many or too few arguments are supplied error is printed.
*/
int main( int argc, char *argv[] )  {

    //Variables
    FILE * script; //This pointer to a file contained a script to be executed in-order
    char * commandline; //This temporary string holds one commandline from the shell or script
    char homePath[255]; //A string to hold the location of the executables
    getcwd(homePath, sizeof(homePath)); //Get the locations of the executables and store.
    
	
    if( argc == 2 ) {
        //One command line argument
        //Start shell on supplied script-file
        
        /*Check if the instructionset file doesn't exists or is unreadable, if the file doesn't exist or is considered unreadable,
	  error is printed and terminates.*/
	    if(fileExists(argv[1])==0){
	    	fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", does not exist.\nExiting...\n", argv[1]);
		    exit(-1);
	    }
	    if(fileReadable(argv[1])==0){
	    	fprintf(stderr, "\nThe supplied instructionset filename, \"%s\", cannot be read.\nExiting...\n", argv[1]);
	    	exit(-1);
        }
		
        //Open the script-file (and check if fopen returns NULL)
        if ((script = fopen(argv[1], "r")) == NULL){
            fprintf(stderr, "Could not allocate memory for \"%s\".\nExiting...\n", argv[1]);
            exit(-1);   
        }
		
        //Loop to read script-file line by line
		while((commandline = getLine(script)) != NULL){
            parseCommandLine(1, commandline, homePath); 
        }

        //Close the script-file
        fclose(script);
    }
	//if more than one command line argument is supplied, error is printed and terminates
    else if( argc > 2 ) {
        
        fprintf(stderr, "A wrong number of command line arguments were provided to simpleshell.c.\nExiting...\n");
        exit(-1);
    }
    else {
        //No command line arguments
        //Start shell on command line
        
        //Print shell name for first command
        printf("simpleshell:~$ ");
        //Loop to read cmd-line line by line
        while(((commandline = getLine(stdin)) != NULL)){
            parseCommandLine(0, commandline, homePath);
        }
    }

} //End int main( int argc, char *argv[] )
