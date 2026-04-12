#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LEN 4096

void tail_file(FILE *fp, int nlines) {
    char *lines[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++) lines[i] = NULL;

    char buffer[MAX_LINE_LEN];
    int current_line = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (lines[current_line % nlines]) {
            free(lines[current_line % nlines]);
        }
        lines[current_line % nlines] = strdup(buffer);
        current_line++;
    }

    int start = (current_line > nlines) ? (current_line % nlines) : 0;
    int count = (current_line > nlines) ? nlines : current_line;

    for (int i = 0; i < count; i++) {
        int idx = (start + i) % nlines;
        printf("%s", lines[idx]);
        free(lines[idx]);
    }
}

int main(int argc, char *argv[]) {
    int nlines = 10;
    int arg_start = 1;

    if (argc > 1 && argv[1][0] == '-') {
        nlines = atoi(&argv[1][1]);
        if (nlines > MAX_LINES) nlines = MAX_LINES;
        arg_start = 2;
    }

    if (arg_start == argc) {
        tail_file(stdin, nlines);
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
            tail_file(fp, nlines);
            fclose(fp);
            if (i < argc - 1) printf("\n");
        }
    }
    return 0;
}
