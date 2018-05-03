//John Harvey
//CS3240
//Shell 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "makeargv.h"

#define READ (O_RDONLY)
#define WRITE (O_WRONLY | O_CREAT)
#define IN (STDIN_FILENO)
#define OUT (STDOUT_FILENO)  
#define ERR (STDERR_FILENO)


/* Function to help with the redirection */
void redirectFunc(const char *filename, int flags, int fileno) 
{
    int fno = open(filename, flags);	// open file to redirect

    if (fno < 0) 
    {
        fprintf(stderr, "could not open file %s\n", filename);	// error check
        exit(-1);
    }
    if (dup2(fno, fileno) < 0) 		// attempt to redirect using dup2
    {
        fprintf(stderr, "could not redirect file %s to %d\n",	// error check
            filename, fileno);
        exit(-1);
    }
}

/* function to strip white space from beginning and end of string */
char* strip(char *s)
{
    char *back = s + strlen(s);
    
    while ((* --back ) == ' ');
    *(back + 1) = '\0';      
    
    while ((*s) == ' ') s++; 
    
    return s; 
}

/* function to fork the process, make the args, and execute redirection */
void forkExec(char *command, int fdin, int fdout)
{
    int i, n;
    char **ExecVectors;    
    pid_t pid;

    printf( "The process identifier (pid) of the parent process is %d\n", (int)getpid()); // print out pid for testing purposes

    if((pid = fork()) <0)	//attempt to fork
	{
		fprintf(stderr, "fork error \n");		//error handle
	}
    
    else if (pid == 0)  /* child */
    {
    	printf( "After the fork, the process identifier (pid) "		// print out pid for testing purposes
		        "of the child is %d\n", (int)getpid());

        if (fdin != IN)
        {
            dup2(fdin, IN);
            close(fdin);
        }
        if (fdout != OUT)
        {
            dup2(fdout, OUT);
            close(fdout);
        }        
        
        n = makeargv(command, "<", &ExecVectors);		// do redirection for <
        if (n > 1 && fdin == IN)
        {
            command = ExecVectors[0];
            redirectFunc(strip(ExecVectors[1]), O_RDONLY, IN);
        }
        
        n = makeargv(command, ">", &ExecVectors);		// do redirection for >
        if (n > 1 && fdout == OUT)
        {
            command = ExecVectors[0];
            redirectFunc(strip(ExecVectors[1]), WRITE, OUT);
        }
        
        n = makeargv(command, " ", &ExecVectors);
        execvp(strip(ExecVectors[0]), ExecVectors);
        
    } 
    else /* Parent */
    {
        wait(NULL);
        
        if (fdin != IN)
            close(fdin);	// close in
        
        if (fdout != OUT)
            close(fdout);   // close out     
    }
}

/* function which will pipe and then execute */
void pipeExec(char **ExecVectors, int n)
{
    int i, fdin = IN, fd[2];

    for (i = 0; i < n; i++)
    {
        if (i < n - 1)
        {
            pipe(fd);
            forkExec(ExecVectors[i], fdin, fd[1]);
            fdin = fd[0];
        }
        else  
        {
            forkExec(ExecVectors[i], fdin, OUT);
        }
    }
}