//Project: 	Prog5
//Names:   	Luke Prescott, Rob Rose, Tommy Li (lprescott@albany.edu, rwrose@albany.edu, tli3@albany.edu)
//			(001252879, 001247373, 001209184)
//Roles:   	Leader, Monitor, Recorder Respectively
//Date:    	11/28/2017
//Course:  	ICSI 402

/*Desc: this file contains the necessary functions associated with the list command.
The functions contained include fileSize, printNames, printDetails, printHidden, checkDirectory
*/

/*
Output: the output depends on the arguments being supplied by the user when using the create
command.
*/

//standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/*
The fileSize function finds file size by seeking all the way to the end on the file, then telling the long
position the position of the end character. This position is the size of the file in bytes. It only takes,
one argument, which is the FILE type needed to point to.

*/
long fileSize(FILE * file) {
    //Position: the variable to be returned, and the position of the end character.S
    long position;

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file.\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    position = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    rewind(file);// returns to the beginning of the file

    return position;// returns the position of the file offset
}

/*
the printNames function, takes a char pointer named path, the role this function is to 
print the name of files contained in a specified directory.
*/
void printNames(char * path){

    char * fileName; //The file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer

    //Opens directory, and checks if valid
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in listFunctions.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {
        fileName = strdup(ent->d_name);
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] != '.') {
            printf("%20s\n", fileName);
        }
        free(fileName);
    }
    
    //Close
    closedir(directory);
} //End void printNames(char * path)

  /*
  the printDetails function prints the the details about each file. The details for each file include the inode number, the permissions in
  octal value, name of the file, and the size of the file.
  */
void printDetails(char * path){

    char * fileName; //The file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer
    char filePath[255]; //The path to the file, used for -i flag
    FILE * inputFile; //A file that is used to find the size of each file
    int inode, fd; //The innode and file descriptor, respectively
	struct stat buf; //The stat structure to hold onto the stat of the file
	mode_t bits; //The permission bits for each file
	
	//Opens directory, and checks if valid, if null print error and terminate
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in listFunctions.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }

    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {

        //Duplicates ent->name into FileName
        fileName = strdup(ent->d_name);
        
        //The next four lines create the file path so that inputFile can be opened
        strcpy(filePath, path);

        //Checks if the supplied path already ends in a /
        //If not, adds one
        char * ptr;
        ptr = strstr(filePath, "\0");
        if(ptr[strlen(ptr) - 1] != '/'){
            strcat(filePath, "/");
        }
        strcat(filePath, fileName);// concatenates fileName with filePath
        
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] != '.') {

            inputFile = fopen(filePath, "r");// open filePath for reading
            if (inputFile == NULL) {
				//prints the name of the file, the size of each file
                fprintf(stderr, "%20s %29s\n", fileName, "permission ERROR");
                continue;
            }
            
            //This is the file descriptor being opened
            fd = open(filePath, O_RDONLY);
            int ret = fstat(fd, &buf);
            
            if (ret < 0) {
                //error
                fprintf(stderr, "%20s %29s\n", fileName, "stat ERROR");
                continue;
            }
            
            inode = buf.st_ino;
            bits = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
            
            printf("%20s%10ld%10o%10d\n", fileName, fileSize(inputFile), bits, inode);
            fclose(inputFile);
        }

        free(fileName);        
    }
    
    //Close
    closedir(directory);
} //End void printDetails(char * path)

  /*
  the function printHidden take a char pointer named path, the role of this function is to print all of the hidden files contained in a directory
  */
void printHidden(char * path){
    
    char * fileName; //THe file name we use for each file to be printed
    DIR * directory; //Directory pointer
    struct dirent * ent; //File info from the directory pointer

	//Opens directory, and checks if valid, if the directory is null, print error and terminate
    directory = opendir(path);
    if (directory == NULL) {
        fprintf(stderr, "ERROR in list.c: Directory can't be opened.\nExiting...\n");
        exit(-1);
    }
    
    //While each dirent struct read from directory != null, it prints the name
    while ((ent = readdir(directory)) != NULL) {
        fileName = strdup(ent->d_name);
        //if the name is == to "." and "..", do not print because they are hidden
        if (fileName[0] == '.') {
            printf("%20s\n", fileName);
        }
        free(fileName);
    }
    
    //Close
    closedir(directory);
} //End void printHidden(char * path)

  /*
  the checkDirectory function checks if a path is a directory or not
  it returns 0 if it doesn't exists, and returns 1 if it does.
  */
int checkDirectory(char * dirPath){
    
	struct stat directoryStat = {0};
	
	if (stat(dirPath, &directoryStat) != -1) {
		return 1;
	}
	return 0;
	
} //End int checkDirectory(char * dirPath)