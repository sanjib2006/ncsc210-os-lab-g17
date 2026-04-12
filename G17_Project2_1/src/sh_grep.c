#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//NOTE: This implementation assumes regular files.

#define READ_BUF 4096   /* chunk size for read() calls          */
#define MAX_LINE 4096   /* max bytes kept per line (truncates)  */

/*
 * Write every byte of a null-terminated string to fd.
 * Does not add a newline; caller supplies one when needed.
 */
static void write_str(int fd, const char *s)
{
    size_t len = strlen(s);
    if (len > 0)
        write(fd, s, len);
}

/*
 * Convert a non-negative integer to its decimal ASCII representation.
 * buf must be at least 12 bytes.  Returns the number of characters written
 * (not counting the null terminator).
 */
static int int_to_str(int n, char *buf)
{
    if (n == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return 1;
    }

    char tmp[12];
    int  pos = 0;

    while (n > 0)
    {
        tmp[pos++] = '0' + (n % 10);
        n /= 10;
    }

    /* digits are in reverse order — flip them */
    for (int k = 0; k < pos; k++)
        buf[k] = tmp[pos - 1 - k];
    buf[pos] = '\0';
    return pos;
}

/*
 * Manual substring search — no strstr, no regex.
 * Returns 1 if pattern (plen bytes) appears anywhere in line (llen bytes).
 * When ignore_case is non-zero each character pair is compared after tolower().
 */
static int contains(const char *line, int llen,
                    const char *pattern, int plen, int ignore_case)
{
    if (plen == 0)
        return 1; /* empty pattern matches every line */

    if (plen > llen)
        return 0;

    for (int i = 0; i <= llen - plen; i++)
    {
        int j;
        for (j = 0; j < plen; j++)
        {
            char tc = ignore_case
                      ? (char)tolower((unsigned char)line[i + j])
                      : line[i + j];
            char pc = ignore_case
                      ? (char)tolower((unsigned char)pattern[j])
                      : pattern[j];
            if (tc != pc)
                break;
        }
        if (j == plen)
            return 1;
    }
    return 0;
}

/*
 * Read fd in READ_BUF-sized chunks, reconstruct lines byte-by-byte, and
 * match each line against pattern.  All output goes through write().
 * Returns the total number of matching lines found.
 *
 * fd          - open file descriptor to read from (0 = stdin)
 * filename    - label emitted when multi_file is set
 * multi_file  - non-zero when more than one file was given on the CLI
 */
static int grep_fd(int fd, const char *filename, const char *pattern,
                   int show_linenum, int ignore_case, int invert,
                   int count_only, int multi_file)
{
    int     plen        = (int)strlen(pattern);
    char    chunk[READ_BUF];
    char    line[MAX_LINE];
    int     line_len    = 0;
    int     linenum     = 0;
    int     match_count = 0;
    char    numbuf[12];
    ssize_t bytes;

    /* Emit one matched line to stdout using only write() */
#define EMIT_LINE() \
    do { \
        if (multi_file)    { write_str(1, filename); write(1, ":", 1); } \
        if (show_linenum)  { int_to_str(linenum, numbuf); write_str(1, numbuf); write(1, ":", 1); } \
        write(1, line, line_len); \
        write(1, "\n", 1); \
    } while (0)

    while ((bytes = read(fd, chunk, sizeof(chunk))) > 0)
    {
        for (ssize_t ci = 0; ci < bytes; ci++)
        {
            char c = chunk[ci];

            if (c == '\n')
            {
                /* Complete line — test and (optionally) emit */
                linenum++;
                int matched = contains(line, line_len, pattern, plen, ignore_case);
                if (invert) matched = !matched;
                if (matched)
                {
                    match_count++;
                    if (!count_only)
                        EMIT_LINE();
                }
                line_len = 0;   /* reset for next line */
            }
            else
            {
                /* Accumulate; silently truncate lines longer than MAX_LINE-1 */
                if (line_len < MAX_LINE - 1)
                    line[line_len++] = c;
            }
        }
    }

    /* Handle a final line that has no trailing '\n' */
    if (line_len > 0)
    {
        linenum++;
        int matched = contains(line, line_len, pattern, plen, ignore_case);
        if (invert) matched = !matched;
        if (matched)
        {
            match_count++;
            if (!count_only)
                EMIT_LINE();
        }
    }

#undef EMIT_LINE

    /* -c: one count line per stream, printed after all lines are processed */
    if (count_only)
    {
        if (multi_file) { write_str(1, filename); write(1, ":", 1); }
        int_to_str(match_count, numbuf);
        write_str(1, numbuf);
        write(1, "\n", 1);
    }

    return match_count;
}

int main(int argc, char *argv[])
{
    int show_linenum = 0;
    int ignore_case  = 0;
    int invert       = 0;
    int count_only   = 0;

    /* Parse flags — stop at first non-flag token */
    int i;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-' || argv[i][1] == '\0')
            break;

        /* Combined flags (-ni, -iv, -niv, …) are all handled in one pass */
        const char *p = argv[i] + 1;
        while (*p)
        {
            switch (*p)
            {
                case 'n': show_linenum = 1; break;
                case 'i': ignore_case  = 1; break;
                case 'v': invert       = 1; break;
                case 'c': count_only   = 1; break;
                default:
                    write_str(2, "sh_grep: invalid option -- '");
                    write(2, p, 1);
                    write_str(2, "'\n");
                    write_str(2, "Usage: sh_grep [-n] [-i] [-v] [-c] <pattern> [file ...]\n");
                    return 1;
            }
            p++;
        }
    }

    /* The next positional argument is the search pattern */
    if (i >= argc)
    {
        write_str(2, "Usage: sh_grep [-n] [-i] [-v] [-c] <pattern> [file ...]\n");
        return 1;
    }

    const char *pattern     = argv[i++];
    int         num_files   = argc - i;
    int         multi_file  = (num_files > 1);
    int         had_error   = 0;
    int         total_matches = 0;

    if (num_files == 0)
    {
        /* No files — consume fd 0 (stdin) */
        total_matches = grep_fd(0, "(standard input)", pattern,
                                show_linenum, ignore_case, invert, count_only, 0);
    }
    else
    {
        for (int f = i; f < argc; f++)
        {
            int fd = open(argv[f], O_RDONLY);
            if (fd < 0)
            {
                write_str(2, "sh_grep: ");
                write_str(2, argv[f]);
                write_str(2, ": No such file or directory\n");
                had_error = 1;
                continue;
            }
            total_matches += grep_fd(fd, argv[f], pattern,
                                     show_linenum, ignore_case, invert,
                                     count_only, multi_file);
            close(fd);
        }
    }

    if (had_error)
        return 1;
    return (total_matches > 0) ? 0 : 1;
}
