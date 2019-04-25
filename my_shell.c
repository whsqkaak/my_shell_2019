/*
    whsqkaak@naver.com 
    2019/04/24
    myshell.c
    ubuntu 16.04
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMD_LEN 100 // The Maximum command length.


int main(void){
    char *args[CMD_LEN + 1]; // command line arguments.
    char *input; // Input command.
    int i;
    int status;
   
   // Get input command repeatedly 
    while (1) {
        printf("LSH_SHELL>>> ");
	fflush(stdout); // Flush stdout buffer.

        input = (char*)malloc(CMD_LEN * sizeof(char));
        fgets(input, CMD_LEN, stdin);

        i = 0;
	args[0] = strtok(input, " \n");

        // strtok input command line
	while(args[i] != NULL){
            i++;
	    args[i] = strtok(NULL," \n");
	}
        
        // NULL input
	if(args[0] == NULL){
            goto no_input;
	}

        // exit command
	if(strcmp(args[0], "exit")==0){
            break;
	}

	// fork  아무 의미없는 명령어 입력 시에도 프로세스가 fork되야하나
	pid_t pid = fork();
	// fork error
	if (pid < 0){
	    perror("Fork error");
	    exit(0);
	}

	// child process
	if (pid == 0){
	    execv(args[0], args);
	}
	// parent process
	if (pid > 0){
	    int retval = waitpid(pid, &status, 0);
	    if (retval > 0){
	        if(WIFEXITED(status)){
		    printf("Child exited by process completion : %d\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status)){
		    printf("Child exited by signal : %d\n", WTERMSIG(status));
		}
	    }
	    else{
	        printf("Unexpected error.\n");
		exit(0);
	    }
	    printf("Child process complete.\n");
	}

        no_input:;
	free(input);

    }
    return 0;
}
