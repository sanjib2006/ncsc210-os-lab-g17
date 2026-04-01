#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 2048



int main(){
    char buffer[BUFSIZE];
    do{
        memset(buffer, 0, BUFSIZE);
        printf("$ ");
        fflush(stdout);

        fgets(buffer, BUFSIZE, stdin);
        if(!strncmp(buffer, "exit", 4))break;
        char b[512] = {0};
        if(!strncmp(buffer, "pwd", 3)){
            getcwd(b, 512);
            printf("%s\n", b);
        }
    }while(1);

    exit(EXIT_SUCCESS);
}
