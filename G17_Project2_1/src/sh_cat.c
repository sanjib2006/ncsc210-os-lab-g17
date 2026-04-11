#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int line_no = 1;

void print_file(int fd, int nflag, int bflag){
    char buf[1024];
    int n;

    int new_line = 1;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; i++) {

            if (new_line) {
                if (bflag) {
                    if (buf[i] != '\n') {
                        char num_buf[32];
                        int len = sprintf(num_buf, "%6d\t", line_no);
                        write(1, num_buf, len);
                        line_no++;
                    }
                }
                else if (nflag) {
                    char num_buf[32];
                    int len = sprintf(num_buf, "%6d\t", line_no);
                    write(1, num_buf, len);
                    line_no++;
                }
                new_line = 0;
            }

            if (write(1, &buf[i], 1) != 1) {
                perror("sh_cat: write error");
                exit(1);
            }

            if (buf[i] == '\n') {
                new_line = 1;
            }
        }
    }

    if (n < 0) {
        perror("sh_cat: read error");
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    int fd=0;//default is stdin (0)
    int nflag = 0;
    int index = 1;
    int bflag=0;

    if(argc>1) {
        if(strcmp(argv[1],"-n")==0){
            nflag = 1;
            index = 2;}
        else if(strcmp(argv[1],"-b")==0){
            bflag=1;
            index=2;
        }
    }

    if(argc == 1 || ((bflag||nflag) && argc == 2)) {
        print_file(fd,nflag,bflag);
        return 0;
    }

    for(int i=index;i<argc;i++){
        if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-b") == 0){
            fprintf(stderr, "sh_cat: use only one option (-n or -b)\n");
            return 1;
        }
        if((fd=open(argv[i],O_RDONLY))<0){
            fprintf(stderr,"sh_cat: cannot open %s\n: %s\n",argv[i],strerror(errno));
            continue;
        }
        print_file(fd,nflag,bflag);
        close(fd);
    }
    
    return 0;
}





