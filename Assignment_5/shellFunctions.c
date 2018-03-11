//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the shell program.
It includes the functions printCWDirectory and changeCWDirectory

 /*
 Output: the output depends on the command that is supplied by the user
*/

//standard c libraries
#include <stdlib.h>
#include <stdio.h>

/*
	The printCWDirectory function takes no parameters, and returns nothings. printcCWDirectory calls getcwd()
	and prints its return value to stdin. The role of the printCWDirectory is to print the path of the current working
	directory, using the getcwd function. If there is not current working directory, an error is printed.
*/
void printCWDirectory(void){
	//the directory string holds the return value
	char directory[255];
	if(getcwd(directory, sizeof(directory)) != NULL){
		printf("%s\n", directory);
	}
	else{
		//return is NULL, so exit with err.
		fprintf(stderr, "Could not get current working directory.\n");
	}
} //End void printCWDirectory()

/*
the changeCWDirectory function takes a char pointer named pathname as a parameter, the role of this function is to change the
current working directory to its specified path.
*/
void changeCWDirectory(char * pathname){
	int x = 0;
	x = chdir(pathname);

	if(x == -1){
		//return is -1, so exit with err.
		fprintf(stderr, "Could not change current working directory.\n");
	}
}//End void changeCWDirectory(char * pathname);
