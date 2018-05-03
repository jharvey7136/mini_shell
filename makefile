#John Harvey
#Shell
#CS 3240

#makefile

#type 'make' to complile, and 'make run' to execute
# 'testFile.c | out.txt' is what i have been using as test input

#CONSTANTS
CC=gcc
#CFLAGS=-Wall -std=c99
RUN = ./bonk

all: bonk.c exec.c makeargv.c bonk
	
bonk: bonk.o exec.o makeargv.o
	gcc bonk.o exec.o makeargv.o -o bonk

bonk.o: bonk.c makeargv.h
	$(CC) $(CFLAGS) -c bonk.c

makeargv.o: makeargv.c makeargv.h
	$(CC) $(CFLAGS) -c makeargv.c

exec.o: exec.c exec.h
	$(CC) $(CFLAGS) -c exec.c

clean:
	rm -f *.o bonk

run: all
	 ${RUN}