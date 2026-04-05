### for group members only

## Project Structure

- `src/`: Contains all C source code. Every utility has its own `.c` file here.
- `bin/`: Contains the compiled, executable binaries (ignored by Git).
- `test/`: folder to test destructive commands like `rm` or `mv`.
- `Makefile`: The build script that automatically compiles our code.

---

## Setup and Execution

To compile and run the shell on your local machine, follow these steps:

**1. Compile the project:**
Open your terminal in the root directory (`/ncsc210-os-lab-g17/G17_Project2_1/`) and run:
```bash
make
```
*This will compile all `.c` files in the `src/` directory and place the executables in the `bin/` directory.*

**2. Run the shell:**
```bash
./bin/shell
```

**3. Clean the build (Optional):**
If you want to delete all compiled binaries and start fresh, run:
```bash
make clean
```

---

## How to Add a New Utility

### Creating a new branch would be better 

```bash
git checkout -b custom_utility main  

# or custom_ls or custom_cat
```

Follow these 3 steps to add your command:

### Step 1: Write your C code
Create a new file in the `src/` folder for your utility (e.g., `src/sh_ls.c`). 
Make sure your program:
- Uses `int main(int argc, char *argv[])` to read user input.
- Returns `0` upon success, and `1` upon failure.

### Step 2: Update the Makefile
Open the `Makefile` in the root directory. Find the `TARGETS` line near the top:
```makefile
# Before
TARGETS = bin/shell bin/sh_rm

# After (Just add your binary name to the list!)
TARGETS = bin/shell bin/sh_rm bin/sh_ls
```

### Step 3: Compile and Test (from root directory of project 2).
1. Run `make` in your terminal
2. Launch the shell: `./bin/shell`
3. Type your new command (e.g., `g17-shell> sh_ls`) to see it run!