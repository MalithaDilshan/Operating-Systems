
/* Author : E13200
 * Title  : Lab04-named pipe demostration
 * Date   : 2017.08.23
 * Description : This program will send the string to the pipe. Then again get the capitalized string
 * from the pipe.
 * compilation:
 * first compile and run the this code and enter the string(this code will handle the seperated string by blank) then compile re.c code.
 * gcc -Wall se.c -o test1
 * ./test1
 * check the output in the terminal
 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_SIZE 1000 


void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main() { 	
	// 	Same as given example we have to define two file descriptor to comminicate
	
	char* fifo1 = "/tmp/fifo1"; 
	char* fifo2 = "/tmp/fifo2";

	char buff[MAX_SIZE]; // define the buffer

	// Get input from user
    char input[MAX_SIZE];
    printf("............................................................\n");
    printf("Enter the string here :");
    fgets(input, MAX_SIZE, stdin);

    // Create two named pipelines
	mkfifo(fifo1, 0666);
	mkfifo(fifo2, 0666);
	
	int input_length = strlen(input);

	// Send data to the other process
	int fd1 = open(fifo1, O_WRONLY); // open the file
	input[input_length] = '\0';
	write(fd1, input, input_length+1); // write the input data to the file
	
    close(fd1); // done with fd1

    // Read data from pipe
	int fd2 = open(fifo2, O_RDONLY);
    read(fd2, buff, MAX_SIZE); // read and put data to the buffer
    printf("Capitalized String is: %s\n", buff); 
    
    printf("............................................................\n");
    
    close(fd2); // done wiht the fd2

    // Distroy pipes
	unlink(fifo1);
	unlink(fifo2);

    return 0; 
}


