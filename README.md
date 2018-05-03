Mini Shell Application
======================

## John Harvey

### About
Mini shell written in C which handles redirection, fork execute, and piping. 

### Install Notes
1. Clone repo with git `git clone https://github.com/jharvey7136/mini_shell.git`
2. Navigate to app's root directory through terminal
3. Compile program with command: `make`
4. Run program with command: `make run`
5. Once program is running, test by running command: `testFile.c | out.txt`
6. Clean object files and executables with command: `make clean`

### Output
By testing with the above command in step 5, the program will write every other line of testFile.c to out.txt.
