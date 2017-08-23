
/* Author : E13200
 * Title  : Lab04-named pipe demostration
 * Date   : 2017.08.23
 * Description : This program will get the string from the pipe and capitalize that. 
 * Then again send that string to the another pipe. Therefore, the se.c program can get 
 * that string and print in terminal.
 * compilation:
 * first compile and run the code se.c then compile this code as
 * gcc -Wall re.c -o test2
 * ./test2
 * check the output in the se.c
 * */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_SIZE 1000

void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main() { 
	// Follow the structure of the given code 
	
	char* fifo1 = "/tmp/fifo1"; 
	char* fifo2 = "/tmp/fifo2";

	char *tr_args[] = {"tr", "[:lower:]", "[:upper:]", NULL}; // define the arguments


    // Create two named pipelines
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);

	// Open the file into the file decriptors
	int fd1 = open(fifo1, O_RDONLY);
	int fd2 = open(fifo2, O_WRONLY);
	
	// Set the fd1 as the standard input and get the data from modified file by sender
	if (dup2(fd1, 0) == -1)
		die("dup2()");
	// Set the fd2 as the standard output for write data
	if (dup2(fd2, 1) == -1)
		die("dup2()");
		

	// Execute tr() command and write data to the stdout
	if(execvp("tr", tr_args) == -1)
		die("execvp()");
		
	// Close the file descriptors
	close(fd1);
	close(fd2);

	exit(EXIT_SUCCESS);

    return 0; 
}

