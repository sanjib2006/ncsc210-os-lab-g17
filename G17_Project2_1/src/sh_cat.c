#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void print_file(int fd){
    char buf[512];
    int n;

    while((n=read(fd,buf,sizeof(buf)))>0){
        if(write(1,buf,n)!=n){ //1 -> for stdout
            perror("sh_cat: write error\n");
            exit(1);
        }
    }
    if(n<0){
        perror("sh_cat: read error\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    int fd=0;//default is stdin (0)

    if (argc == 1) {
        print_file(fd);
        return 0;
    }

    for(int i=1;i<argc;i++){
        if((fd=open(argv[i],O_RDONLY))<0){
            fprintf(stderr,"sh_cat: cannot open %s\n: %s\n",argv[i],strerror(errno));
            continue;
        }
        print_file(fd);
        close(fd);
    }
    
    return 0;
}





