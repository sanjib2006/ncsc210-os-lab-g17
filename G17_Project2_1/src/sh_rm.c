#include <stdio.h>
#include <unistd.h>
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

    printf("You are going to delete: %s\n", argv[1]);

    if (S_ISDIR(file_info.st_mode))
    {
        printf("Directory\n");
        if (rmdir(argv[1]) == 0)
        {
            printf("sh_rm: Directory %s deleted successfully.\n", argv[1]);
            return 0;
        }
        else
        {
            perror("Could not delete directory");
            return 1;
        }
    }
    else
    {
        printf("File\n");
        if (unlink(argv[1]) == 0)
        {
            printf("sh_rm: File %s deleted successfully.\n", argv[1]);
            return 0;
        }
        else
        {
            perror("Could not delete file");
            return 1;
        }
    }

    return 0;
}