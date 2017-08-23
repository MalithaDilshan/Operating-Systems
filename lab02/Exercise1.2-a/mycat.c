
/* Author: E13200
 * Title : Lab02-Excercise1.2-a
 * Date  : 2017.08.20
 * Description : This code will read a text file and writes the output to the standard output 
 * according to the user specified path. You have to compile the file and the give the command line argumets as follows.
 * 
 * gcc -Wall mycat.c -o test
 * follow this formact './testIO <in.txt> 'for example,
 * ./test /home/e13200/Desktop/test.txt

 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>   // header file for the open() function
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char const *argv[]){
	
	/* size_t. Unsigned integral type. Alias of one of the fundamental unsigned integer types.
	 * It is a type able to represent the size of any object in bytes: size_t is the type 
	 * returned by the sizeof operator and is widely used in the standard library to represent 
	 * sizes and counts.
	 * */

	int out;
	int buf_size = 1000;
	size_t ret;

	if (argc != 2){
		fprintf(stderr,"Argument error.Please enter correct number of arguments\n");
		return 1;
	}

	// Openning the file to read (only for read)
	out = open(argv[1], O_RDONLY);
	
	if(out == -1)
	{
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	} 

	// Reading data from the file using buffer.
	char* buffer = malloc(buf_size+1); 
	ret = read(out,buffer,buf_size);

	if(ret == -1)
	{
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
	
	// We have to null terminate the string ourselves. 
	buffer[ret] = '\0'; 
	
	// Writes text file to stdout
	printf("The string read back is: %s\n",buffer);
	
	// Close the buffer
	
	free(buffer);

	ret = close(out);

	if(ret == -1)
	{
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	return 0;
}
