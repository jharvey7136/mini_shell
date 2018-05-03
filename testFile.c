#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>



#define READ (O_RDONLY)
#define WRITE (O_WRONLY | O_CREAT)
#define IN (STDIN_FILENO)
#define OUT (STDOUT_FILENO)  
#define ERR (STDERR_FILENO)



void redirectFunc(const char *filename, int flags, int fileno) 
{
    int fno = open(filename, flags);

    if (fno < 0) 
    {
        fprintf(stderr, "could not open file %s\n", filename);
        exit(-1);
    }
    if (dup2(fno, fileno) < 0) 
    {
        fprintf(stderr, "could not redirect file %s to %d\n",
            filename, fileno);
        exit(-1);
    }
}


int redirect(int argc, char *argv[]) 
{
    int line_count = 0;
    int i, f;
    char line[1024];

    char *fileToRedirect;   
    char *whereToRediect;

    if (argc < 3) 
    {
        fprintf(stderr, "invalid number of arguments\n");
    } 
    else 
    {
        for(i = 0; i < argc; i++)               // loop to determine where the redirct symbol is, 
        {                                       // and to set the file to redirct and where to redirct 
            if (strncmp(argv[i], ">", 1) == 0)
            {               
                fileToRedirect = argv[i - 1];
                whereToRediect = argv[i + 1];
            }
            if (strncmp(argv[i], "<", 1) == 0)
            {
                fileToRedirect = argv[i + 1];
                whereToRediect = argv[i - 1];
            }
        }

        redirectFunc(fileToRedirect, READ, IN);     // do the redirctions
        redirectFunc(whereToRediect, WRITE, OUT);
        redirectFunc("err.txt", WRITE, ERR);        
        

        while (fgets(line, sizeof(line), stdin) != NULL) 
        {
            if (line_count++ % 2 == 0) 
            {
                fprintf(stdout, "%s", line);
            } 
            else 
            {
                fprintf(stderr, "%s", line);
            }
        }
    }
    return 0;
}


