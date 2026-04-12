## Project Description

In this project, you have to develop a series of simplified UNIX-like utilities. These utilities will be lightweight versions of common commands, such as cat, ls, time, and others. To avoid confusion with the standard UNIX commands, each utility will have a unique name; for instance, instead of using cat, you will implement a command called custom_cat from scratch. Some utilities are mentioned here:

### Utilities to Implement

- **a. ls** - List directory contents  
- **b. cat** - Concatenate and display file content  
- **c. grep** - Search for patterns in files  
- **d. wc** - Word, line, and character count   
- **e. rm** - Remove files or directories  
- **f. head** - Display the first few lines of a file  
- **g. tail** - Display the last few lines of a file  

---

---

### Implemented Utilities

#### `sh_grep` — Search for patterns in files

Searches each named file (or standard input if no files are given) for lines containing the given pattern. Prints each matching line to standard output.
Implemented using raw POSIX system calls only (`open`, `read`, `write`, `close`); no stdio (`fopen`/`printf`) is used.

**Usage**

```
sh_grep [-n] [-i] [-v] [-c] <pattern> [file ...]
```

**Flags**

| Flag | Description |
|------|-------------|
| `-n` | Prefix each matching line with its 1-based line number |
| `-i` | Case-insensitive matching |
| `-v` | Invert match — print lines that do **not** contain the pattern |
| `-c` | Print only a count of matching lines (one per file) |

Flags may be combined (e.g., `-ni`, `-iv`).

**Examples**

```bash
# Basic search
sh_grep hello file.txt

# Case-insensitive search across two files (filenames prefixed automatically)
sh_grep -i hello file1.txt file2.txt

# Show line numbers for matching lines
sh_grep -n TODO src/shell.c

# Count lines that do NOT contain "error"
sh_grep -vc error log.txt

# Pipe from another command
echo "hello world" | sh_grep hello
```

**Exit status:** `0` if at least one match was found, `1` if no matches, `1` on error.

---

### Note

1. Implement all the operations from scratch in C, including a main UNIX-like shell program to run the other commands. Write proper makefile and Readme file.  
2. Attach the screenshot of your execution in the documentation file of this project.  