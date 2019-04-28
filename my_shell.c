/*
    whsqkaak@naver.com 
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
    char env_dir[CMD_LEN]; // Executable(command) file location..  
    char cur_dir[CMD_LEN]; // Current directory.
    
    int i;
    int status;
    
    getcwd(env_dir, CMD_LEN); // Executable files locate cwd.

    // Get input command repeatedly 
    while (1) {
        printf("LSH_SHELL:%s> ",getcwd(cur_dir,CMD_LEN));
	fflush(stdout); // Flush stdout buffer.
       
        char tmp_dir[CMD_LEN*2]; // To protect env_dir variable.
	strcpy(tmp_dir, env_dir);

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

	// cd command
	if(strcmp(args[0], "cd")==0){
            if(chdir(args[1])==-1){
	        break;
	    }
	    continue;
	}

	// fork  아무 의미없는 명령어 입력 시에도 프로세스가 fork되야하나
	pid_t pid = fork();
	// fork error
	if (pid < 0){
	    perror("Fork error");
	    exit(0);
	}

        // To make Absolute path.
        strcat(tmp_dir, "/");
        args[0] = strcat(tmp_dir, args[0]);

	// child process
	if (pid == 0){
	    execv(args[0], args);
	}
	// parent process
	if (pid > 0){
	    int retval = waitpid(pid, &status, 0);
	    if (retval <= 0){
	        exit(0);
	    }
	}

        no_input:;
	free(input);
    }
    return 0;
}
