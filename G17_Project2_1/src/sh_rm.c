#include <stdio.h>
#include <sys/stat.h>

struct stat file_info;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sh_rm <filename>\n");
        return 1;
    }
    if (stat(argv[1], &file_info) != 0)
    {
        perror("Error finding target");
        return 1;
    }
    if (S_ISDIR(file_info.st_mode))
    {
        printf("Directory\n");
    }
    else
    {
        printf("File\n");
    }

    printf("You are going to delete: %s\n", argv[1]);

    return 0;
}