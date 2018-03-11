//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the create command.
The functions contained include createFile, createDirectory, createHardLink, createSoftLink

 /*
 Output: the output depends on the arguments being supplied by the user when using the create
 command.
*/


//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

/*
	This function takes fileName and creates a file named fileName
*/
void createFile(char * fileName) {
	
	int fd; //The file descriptor
	
	//Creates the initial file with user permissions
	fd = open(fileName, O_RDWR | O_CREAT, 0600);
	
	//Checks to see if open failed
	if (fd < 0) {
		fprintf(stderr, "ERROR creating \"%s\".\n", fileName);
		exit(-1);
	}
	
	//Modifys permissions of fileName to 640, on fail exit the process
	if (chmod(fileName, S_IRUSR | S_IWUSR | S_IRGRP) == -1) {
		fprintf(stderr, "ERROR modifying permissions of \"%s\".\n", fileName);
		exit(-1);
	}
	
	//Necessary closing
	close(fd);
}

/*
	This function takes a directoryName and creates a directory named 
	directoryName
*/
void createDirectory(char * directoryName) {
	
	struct stat st = {0}; //Stat struct to test weather directoryName exists
	
	//If directoryName doesn't exist, create the directory
	if (stat(directoryName, &st) == -1) {
		//creates the directory directoryName
		mkdir(directoryName, 0750);
		
		if (chmod(directoryName, S_IRWXU | S_IRGRP | S_IXGRP) == -1) {
			fprintf(stderr, "ERROR: Unable to modify \"%s\".\n", directoryName);
			exit(-1);
		}
		
	} 
	else {
		printf("ERROR: Directory already exists.\n");
		return;
	}
	
}

/*
	This function takes oldName and linkName and creates a hardLink from
	oldName to linkName
*/
void createHardLink(char * oldName, char * linkName) {
	
	//if link() returns -1, a link cannot be created, else link creates a hard link between oldName and linkName
	if (link(oldName, linkName) == -1) {
		fprintf(stderr, "ERROR in create: hard link can't be created. %s\n", strerror(errno));
		exit(-1);
	}
	
}

/*
	This function takes oldName and linkName and creates a hardLink from
	oldName to linkName
*/
void createSoftLink(char * oldName, char * linkName) {
	
	//if link() returns -1, a link cannot be created. Else, the link creates a soft link between oldName and linkName
	if (symlink(oldName, linkName) == -1) {
		fprintf(stderr, "ERROR in create: soft link can't be created. %s\n", strerror(errno));
		exit(-1);
	}
	
}