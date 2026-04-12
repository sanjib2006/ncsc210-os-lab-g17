#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("\n===================================================\n");
    printf("              GROUP 17 SHELL HELP MANUAL\n");
    printf("===================================================\n\n");

    printf("Built-in command:\n");
    printf("  exit\n");
    printf("      Close the shell.\n\n");

    printf("Custom utilities:\n");

    printf("  sh_help\n");
    printf("      Show this help manual.\n\n");

    printf("  sh_ls [path]\n");
    printf("      List non-hidden entries in the target directory.\n\n");

    printf("  sh_rm [-r] <target...>\n");
    printf("      Remove file(s). Use -r to remove directories recursively.\n\n");

    printf("  sh_cat [-n | -b] [file ...]\n");
    printf("      Concatenate and print file contents (or stdin).\n");
    printf("      -n  number all output lines\n");
    printf("      -b  number non-empty output lines\n\n");

    printf("  sh_grep [-n] [-i] [-v] [-c] <pattern> [file ...]\n");
    printf("      Search for a pattern in files or stdin.\n");
    printf("      -n  show line numbers\n");
    printf("      -i  case-insensitive matching\n");
    printf("      -v  invert match\n");
    printf("      -c  print only the match count\n\n");

    printf("  sh_wc [-l | -w | -c] <file ...>\n");
    printf("      Count lines, words, and bytes.\n");
    printf("      Without flags, prints all three counts.\n\n");

    printf("===================================================\n");

    return 0;
}
