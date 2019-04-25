/*
    whsqkaak@naver.com
    my_shell/pwd command
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_MAX 100

int main(int argc, char *argv[]){
    char buf[BUF_MAX];
    printf("%s\n", getcwd(buf, BUF_MAX));

    exit(0);
}
