#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>


int tbytes = 0;
int tlines = 0;
int twords = 0;

int counter(char* filename, int flg){
    FILE* fp = fopen(filename, "r");
    if(!fp){
        printf("%s\n", filename);
        perror("fp ");
        _exit(1);
    }
    int i =  fseek(fp, 0L, SEEK_END);
    if(i < 0){
        perror("fseek ");
        _exit(1);
    }

    long bytes = ftell(fp);
    rewind(fp);
    
    int words = 0;
    int lines = 0;
    char ch, pch;
    while((ch = fgetc(fp)) != EOF){
        if(ch == '\n'){
            lines++;
        }

        if((ch == '\n' || ch == ' ') && (pch != '\n' && pch != ' ')){
            words ++;
        }
        pch = ch;
    }
    words++;
    
    if(!flg){
        printf("%s >> lines: %d  words: %d  bytes: %ld\n", filename, lines, words, bytes);
    }else if(flg == 1){
        printf("%s >> lines: %d\n", filename, lines);
    }else if(flg == 2){
        printf("%s >> words: %d\n", filename, words);
    }else if(flg == 3){
        printf("%s >> bytes: %ld\n", filename, bytes);
    }
    twords += words;
    tlines += lines;
    tbytes += bytes;
    return 0;
}


int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "Incorrect usage\n");
        _exit(1);
    }
    bool check;
    check = strncmp(argv[1], "-", 1);
    if(argc == 2 && check == false){
        fprintf(stderr, "Incorrect usage\n");
        _exit(1);
    }

    if(check == true){
       for(int i = 1; i<argc; i++){
            counter(argv[i], 0);
        }

       if(argc > 2){
            printf("Total >> lines: %d, words: %d, bytes: %d\n", tlines, twords, tbytes);
        }
    }else{
        int flg = 0;
        if(!strncmp(argv[1], "-l", 2)){
            flg = 1;
        }else if(!strncmp(argv[1], "-w", 2)){
            flg = 2;
        }else if(!strncmp(argv[1], "-c", 2)){
            flg = 3;
        }else if(!strncmp(argv[1], "-", 1)){
            fprintf(stderr, "Invalid Option %s\n", argv[1]);
            _exit(1);
        }

        for(int i = 2; i < argc; i++){
            counter(argv[i], flg);
        }

        if(argc > 3){
            switch(flg){
                case 1:
                    printf("Total >> lines : %d\n", tlines);
                    break;
                case 2:
                    printf("Total >> words : %d\n", twords);
                    break;
                case 3:
                    printf("Total >> bytes : %d\n", tbytes);
                    break;
                default:
                    printf("Error\n");
                    break;
            }
        }
    }
    return 0;

}
