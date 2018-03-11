#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*	
	A Naive Shell that prompts the user for a command, then calls 
	a child process to print out the command, and waits for the child to end.
*/

void main() {
	
	char inputBuffer[1024];
	pid_t child;
	pid_t c;
	int cstatus;
	
	if ((child = fork()) == 0) {
		//Child
		printf("Shell~ ");
		scanf("%[^\n]%*c", inputBuffer);
		
		char * token;
		token = strdup(inputBuffer);
		
		token = strtok(token, " ");
		int argument = 0;
		
		while (token) {
			
			if (argument == 0) {
				argument++;
				token = strtok(NULL, " ");
				continue;
			}
			
			argument++;
			printf("Arg %d: \"%s\"\n", argument, token);
			token = strtok(NULL, " ");
			
		}
		
		printf("Child Terminated...\n");
		
		exit(1);
		
	}
	else {
		//parent
		if (child == (pid_t)(-1)) {
			fprintf(stderr, "ERROR: fork failed\n exiting...\n");
			exit(-1);
		}
		
		c = wait(cstatus);
		
	}
		

}