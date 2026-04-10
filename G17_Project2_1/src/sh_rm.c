#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int recursive = 0;

int delete_dir(const char *path)
{
    DIR *dir = opendir(path);
    struct dirent *entry;
    char full[1024];

    if (!dir)
        return -1;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full, sizeof(full), "%s/%s", path, entry->d_name);

        struct stat info;
        if (stat(full, &info) != 0)
            continue;

        if (S_ISDIR(info.st_mode))
            delete_dir(full); // recursion
        else
            unlink(full);
    }

    closedir(dir);
    return rmdir(path);
}

int main(int argc, char *argv[])
{
    struct stat file_info;
    int start = 1;

    if (argc < 2)
    {
        printf("Usage: sh_rm [-r] <files>\n");
        return 1;
    }

    // minimal flag handling
    if (strcmp(argv[1], "-r") == 0)
    {
        recursive = 1;
        start = 2;
    }

    for (int i = start; i < argc; i++)
    {
        if (stat(argv[i], &file_info) != 0)
        {
            perror("Error finding target");
            continue;
        }

        printf("You are going to delete: %s\n", argv[i]);

        if (S_ISDIR(file_info.st_mode))
        {
            printf("Directory\n");

            if (!recursive)
            {
                printf("Use -r to delete directory\n");
                continue;
            }

            if (delete_dir(argv[i]) == 0)
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