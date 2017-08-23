

/* Author: E13200
 * Title : Lab02-Excercise2.1-d
 * Date  : 2017.08.21
 * Description :  parent reads a string from the user and send it to the child
 * and the child capitalizes each letter and sends back the 
 * string to parent and parent displays it
 * compilation:
 * gcc -Wall capUnname.c -o test
 * ./test
 * */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

void capitalizer(char * array, int length);


int main()
{
	int pipe_ends[2];
	int pipe_ends1[2];
	
	/*The pid_t data type is a signed integer type which is capable of representing a process 
	 * ID. In the GNU C Library, this is an int .
	 * */
	 
	pid_t pid;
	char data[200];
	
	//printf("%d\n",pipe(pipe_ends));

	// Here we can use the two pipes to comminicates with parent and the child.
	if(pipe(pipe_ends)) 
	{
		perror("Pipe 1 creation");
		return -1;
	}

	if(pipe(pipe_ends1)) 
	{
		perror("Pipe 2 creation");
		return -1;
	}

	pid = fork();  // creating two process
	
	if(pid < 0) 
	{
		perror("Fork");
		return -1;
	}
	
	if(pid > 0) { 

		// Get input from user
		printf("Parent Process:\n");
		printf("Enter the String here:\n");
		
		fgets(data,200,stdin);
		printf("\n");

		// Send that data to the child
		// enable write end only.
		close(pipe_ends[READ_END]);
		write(pipe_ends[WRITE_END], data, strlen(data));
		close(pipe_ends[WRITE_END]); // lock the write end.


		// Reading back the result
		char buff1[100];
		close(pipe_ends1[WRITE_END]);  // same thing doing as child proccess reading data.
		sleep(5);
		int count = read(pipe_ends1[READ_END], buff1, 100);
		buff1[count] = '\0';

		printf("Capitalized data read by parent: %s\n", buff1);
		exit(EXIT_SUCCESS);

	}

	if(pid == 0) { 
		
		char buff[100];
		// now clse the write end. Enable the read end only.
		close(pipe_ends[WRITE_END]);
		sleep(5);

		// Read from the parent
		int count = read(pipe_ends[READ_END], buff, 100);
		buff[count] = '\0'; //EOC

		// Capitalizing the available buffer.
		printf("%s - child going to do capitalize letters\n", buff);
		capitalizer(buff,strlen(buff));
		
		// send the capitalized array to to the parent process.
		printf("Sending capitalized data to parent\n");
		close(pipe_ends1[READ_END]);
		write(pipe_ends1[WRITE_END], buff, strlen(buff));
		close(pipe_ends1[WRITE_END]);

		exit(EXIT_SUCCESS);
	}

	
	return 0;
}

void capitalizer(char * array, int length){
	
	int i;
	//int length
	for (i = 0; i<length; i++){
		if ( array[i] <= 'z' && array[i] >= 'a' ){
			array[i] = (array[i] - 'a') + 'A';  // using the ASCII format and override the initial buffer
		}
	}
}
