//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the functions that check supplied arguments with corresponding commands associated
with the program. If they arguments supplied match with a particular command, that command is executed.

It contains the following functions fileExists, fileReadable, parseCommandLine,getLine, createArgList, executeChildProcess

 /*
 Output: the output depends on the arguments being supplied by the user 
 command.
*/

//standard libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//included external header files, containing prototypes
#include "input.h"
#include "shellFunctions.h"

/*
    The getLine function reads one line from the specified file and returns the result as a null terminated string.
*/
char * getLine(FILE * stream){
    
    //lineSize is the maximum size of a line, and line is a pointer to the start of the read line
    const size_t lineSize = 1024;
	//memory allocation
    char * line = malloc(lineSize);
    //newLine is a char * to the line without the '\n' character 
    char * newLine;

    //Gets one line from stream, returning NULL if empty
    if (fgets(line, lineSize, stream)!= NULL){

        //Check if it ends with a newline, then replaces it with a terminator
        if(line[strlen(line)-1] == '\n'){
            line[strlen(line)-1] = '\0';

            //Free and return
            newLine = strdup(line);//duplicates line into newLine
            free(line);
            return newLine;
        }
        //Otherwise, just leave it be
        else{
            //Free and return
            newLine = strdup(line);//duplicates line into newLine
            free(line);
            return newLine;
        }
    }
    //fgets returned NULL
    else{
        //Free and return
        free(line);
        return NULL;
    }

} //End char* getLine(FILE * stream)

//Helper functions below this point

/*
	The fileExists function returns a 1 if the supplied file name exists  by using the access function. 
	If the supplied file name does not exist, the function returns 0.
*/
int fileExists(char * filename){
	//F_OK is used for checking if the file is readable
	if(access(filename, F_OK) != -1) return 1;
	else return 0;
} //End int fileExists(char * filename)

/*
	The fileReadable function returns a 1 if the supplied file name is readable by using the access function. 
	If the supplied file name is not readable, the function returns 0.
*/
int fileReadable(char * filename){
	//R_OK is used for checking if the file is readable
	if(access(filename, R_OK) != -1) return 1;
	else return 0;
} //End int fileReadable(char * filename)

/*
The parseCommandLine function take parameters of isFile, commandline, and homepath
executes the user supplied arguments, with the corresponding commands for the program.
*/
void parseCommandLine(int isFile, char * commandline, char * homePath) {
    char ** arguments; //A list of string arguments passed to the shell

    //printf("commandline: \"%s\".\n", commandline);

    if ((commandline[0] == '\0') || (commandline[0] == ' ')){   

        if(isFile == 0){
            //Print shell name for next command
            printf("simpleshell:~$ ");
        }
        return;
    }
    
    int i=0, numArgs=0;
    //For loop to determine number of arguments
    while (commandline[i] != '\0'){
        if (commandline[i] == ' '){
            numArgs++;    
        }
        i++;
    } 

    //Increment by one because of word after last space
    numArgs++;

    //The temp string here is a duplicate of the command line
    //It is being used to strtok and find the exec name
    char * temp;
    temp = strdup(commandline);
    const char s[2] = " ";
    char * command; 
    
    //Strtok here
    command = strtok(temp, s);
    
    //The string list to hold all arguments including program name
    char ** argList;
    argList = createArgList(numArgs, commandline, homePath);
 
    /*
    i = 0;
    while(argList[i] != NULL){
        printf("%s\n", argList[i]);
        i++;
    }
    */
    
    //if command should quit simpleshell, then exit with (1)
    if(strcmp(argList[0], "quit") == 0){
        printf("goodbye\n");
        exit(1);
    }

    else if(strcmp(command, "list") == 0){

        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
	
    else if(strcmp(command, "create") == 0){
                
        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
	//if "wd" is supplied, prints an errors if first argument is not "wd", otherwise prints path of the current working directory
	
	else if(strcmp(argList[0], "wd") == 0){
        if(numArgs > 4){
            fprintf(stderr, "There were to many arguments for command: wd.\n");
        }
        else if(numArgs == 3){
            //saved is a stored file descriptor for stdout
            //tempOut is a store file descriptor for the supplied file
            int saved; int tempOut; 

            //Open (create) the supplied file
            tempOut = open(argList[2], O_WRONLY | O_APPEND | O_CREAT, 0644);
            if(tempOut < 0){
				fprintf(stderr, "ERROR: unable to open supplied file.\n");
                return;
            }
            
            //store the file descriptor for stdout
            saved = dup(1);

            //redirect output
            dup2(tempOut, 1);
            
            //call function printCWDirectory
            printCWDirectory();  
           
            //return output to normal
            dup2(saved, 1);

            //close file descriptors
            close(saved);
            close(tempOut);
        }
        else{
            //call function printCWDirectory
            printCWDirectory();
        }
    }
    
    /*
    if "chwd" is supplied, prints an error if second argument is not null, if the first argument is equal to null, prints an error
    otherwise changes the current current working directory and prints out the path of the new specified directory
    */
    else if(strcmp(argList[0], "chwd") == 0){
        if(numArgs > 3){
            fprintf(stderr, "There were to many arguments for command: chwd.\n");
        }
        else if(numArgs < 2){
            fprintf(stderr, "There were to few arguments for command: chwd.\n");
        }
        else{
            //Call changeCWDirectory()
            char * pathname; //A string to hold the passed path argument
            pathname = strdup(argList[1]);
            changeCWDirectory(pathname);
            free(pathname);
        }
    }
    else if(strcmp(command, "fileconverter") == 0){
                
        //Call executeChildProcess (which creates a child process)
        executeChildProcess(numArgs, argList);
    }
    else{
        fprintf(stderr, "ERROR: command not found.\n");
    }

    if(isFile == 0){
        //Print shell name for next command
        printf("simpleshell:~$ ");
    }

    //Loop to free the mem of the list of args (and print)
    for(i = 0; i < numArgs; i++)
    {
        //(print) the free
        //printf("%d \"%s\"\n", i, argList[i]);
        free(argList[i]);
    } 

    //Free the list pointer and temp string
    free(argList); free(temp);


} //End void parseCommandLine(int file, char * commandline)

/*

*/
char ** createArgList(int numArgs, char * commandline, char * homePath){

    const char s[2] = " ";
    char * token; int pos = 0;
    char ** argList = malloc((numArgs + 1) * sizeof(char *));
	
	token = strtok(commandline, s);
	
    while( token != NULL ) {

        if((pos == 0) && (strcmp(token, "quit")!=0) && (strcmp(token, "wd")!=0) && (strcmp(token, "chwd")!=0)){
            argList[pos] = malloc(strlen(token) + strlen(homePath) + 2); //+2 becuase of added '/'
            strcpy(argList[pos], homePath);//copies homePath into index of argList
            strcat(argList[pos], "/");//concatenates / into the index of argList
            strcat(argList[pos], token);//concatenates token into the index of argList
            
            //printf("Path to executable: \"%s\"\n", argList[0]);
        
            pos ++;
            token = strtok(NULL, s);
        }

        else{
            argList[pos] = malloc((strlen(token) + 1) * sizeof(char));
            strcpy(argList[pos], token);

            pos ++;
            token = strtok(NULL, s); 
        }

 
	}
    
    //End the argList with NULL
	argList[pos] = NULL;
    return argList;

} //End char ** createArgList(char * commandline)

/*

*/
void executeChildProcess(int numArgs, char ** argList){

    //Variables
    pid_t  pid;
    pid_t c;
    int cstatus;
    
	//fork(), copies the child process from the parent, if pid is less than 0, print error
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "ERROR: fork failed.\nExiting...\n");
        exit(-1);
    }
	
	//if pid is equal to 0 print the id of the parent and child.
    if (pid == 0) {
        //Child process

        //Child details
        //printf("\nChild - PID: %d and PPID: %d.\n\n", getpid(), getppid());

        //Call program
        execvp(argList[0], argList);

        //If the child process reaches this point, execvp failed
        fprintf(stderr, "Child process could not execute execvp.\n");
        exit(-1);
    }
    else {
        //Wait for the child process to finish
        c = wait(&cstatus);

        //Parent details
        //printf("\nParent - PID: %d and PPID: %d.\n", getpid(), pid);

        //Child status
        //printf("Parent - Child %ld exited with status: %d.\n", (long) c, cstatus);

        char * status;
        if(cstatus == 0){
            status = strdup("success!");
        }
        else{
            status = strdup("ERROR (!= 0).");
        }

        if(cstatus != 0){
            printf("Exit status: %d implies %s\n\n", cstatus, status);
        }
    }
    
} //End void executeChildProcess(char * command, char * commandline)