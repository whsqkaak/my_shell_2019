/*
    whsqkaak@naver.com
    my_shell/cd command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <path name>\n", argv[0]);
	exit(1);
    }
    char name[100];
    printf("Before Directory : %s\n", getcwd(name, 100));
    if(chdir(argv[1])==-1){
        printf("Fail change directory\n");
	exit(1);
    }
    printf("After Directory : %s\n", getcwd(name, 100));
    exit(0);
}
