#include <stdio.h>
#include <stdlib.h>

void head_file(FILE *fp, int nlines) {
    char line[4096];
    int count = 0;
    while (count < nlines && fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        count++;
    }
}

int main(int argc, char *argv[]) {
    int nlines = 10;
    int arg_start = 1;

    if (argc > 1 && argv[1][0] == '-') {
        nlines = atoi(&argv[1][1]);
        arg_start = 2;
    }

    if (arg_start == argc) {
        head_file(stdin, nlines);
    } else {
        for (int i = arg_start; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                continue;
            }
            if (argc - arg_start > 1) {
                printf("==> %s <==\n", argv[i]);
            }
            head_file(fp, nlines);
            fclose(fp);
            if (i < argc - 1) printf("\n");
        }
    }
    return 0;
}
