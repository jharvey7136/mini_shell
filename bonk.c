//John Harvey
//Shell

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "makeargv.h"
#include "exec.h"

int main(int argc, char *argv[])
{
	/* declare variables */
	char input[256];
	int j;
	char **ExecVectors = NULL;

	while(1)
	{
		fprintf(stdout, "> ");			 // prompt
		fgets(input, 256, stdin);		 // store uder input
		input[strlen(input) - 1] = '\0'; // remove new line from the end

		if (strncmp(input, "exit", 4) == 0)		// exit if 'exit' is typed
        exit(0);

    	else
    	{
    		j = makeargv(input, "|", &ExecVectors);
    		pipeExec(ExecVectors, j);
    	}
	}
	return 0;
}
