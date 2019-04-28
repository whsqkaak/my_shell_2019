/*
    whsqkaak@naver.com
    my_shell/ls command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

static void do_ls(char *path, char *opt);

int main(int argc, char *argv[]){
    int i, j;
    char opt[100];
    
    // option token
    j = argc;
    for(i=1;i<argc;i++){
        if(argv[i][0] == '-'){
	    strtok(argv[i], "-");
	    strcat(opt, argv[i]);
	    argv[i] = NULL;
	    j--;
	}
    }

    // ls Current directory
    if(j==1){
        do_ls(".", opt);
    }
    // ls another directory
    else{
        for(i=1;i<j;i++){
            do_ls(argv[i], opt);
        }
    }	
    exit(0);
}

static void do_ls(char* path, char *opt){
    DIR *d;
    struct dirent *ent;
    int opt_a=0;
    
    // option 'a'
    if(strchr(opt, 'a')){
        opt_a = 1;
    }

    d = opendir(path);
    if(!d){
        perror(path);
	exit(1);
    }
    
    while(ent = readdir(d)){
        if(ent->d_name[0] == '.' && opt_a == 0){
	    continue;
	}
	printf("%-15s ", ent->d_name);
    }
    
    printf("\n");
    closedir(d);
}
