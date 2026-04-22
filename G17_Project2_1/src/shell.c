#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

int main()
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];

    printf("Welcome to Group 17 Custom Shell!\n");
    printf("Type 'exit' to quit.\n\n");

    while (1)
    {
        printf("g17-shell> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
        {
            printf("\nExiting shell...\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
        {
            continue;
        }

        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        int i = 0;
        args[i] = strtok(input, " \t");
        while (args[i] != NULL && i < MAX_ARGS - 1)
        {
            i++;
            args[i] = strtok(NULL, " \t");
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {

            char bin_path[MAX_INPUT_SIZE];
            snprintf(bin_path, sizeof(bin_path), "./bin/%s", args[0]);
            execv(bin_path, args);
            printf("Error: Command '%s' not found or failed to execute.\n", bin_path);
            exit(1);
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
