#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat file_info;

    if (argc < 2)
    {
        printf("Usage: sh_rm <file1> <file2> ...\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if (stat(argv[i], &file_info) != 0)
        {
            perror("Error finding target");
            continue; // move to next file
        }

        printf("You are going to delete: %s\n", argv[i]);

        if (S_ISDIR(file_info.st_mode))
        {
            printf("Directory\n");
            if (rmdir(argv[i]) == 0)
            {
                printf("sh_rm: Directory %s deleted successfully.\n", argv[i]);
            }
            else
            {
                perror("Could not delete directory");
            }
        }
        else
        {
            printf("File\n");
            if (unlink(argv[i]) == 0)
            {
                printf("sh_rm: File %s deleted successfully.\n", argv[i]);
            }
            else
            {
                perror("Could not delete file");
            }
        }
    }

    return 0;
}