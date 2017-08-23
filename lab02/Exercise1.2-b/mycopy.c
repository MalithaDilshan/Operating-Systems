/* Author: E13200
 * Title : Lab02-Excercise1.2-b
 * Date  : 2017.08.20
 * Description : Usage of the open(), read(), write(), close(). this program takes two arguements source and the destination 
 * You have to compile the file and the give the command line argumets as follows.
 * 
 * gcc -Wall mycopy.c -o testIO
 * follow this formact './testIO <in.txt> <out.txt>' for example,
 * ./testIO /home/e13200/Desktop/test.txt /home/e13200/Desktop/test2.txt 
 * */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char const *argv[])
{	
	/* size_t. Unsigned integral type. Alias of one of the fundamental unsigned integer types.
	 * It is a type able to represent the size of any object in bytes: size_t is the type 
	 * returned by the sizeof operator and is widely used in the standard library to represent 
	 * sizes and counts.
	 * */
	int out;
	int buf_size = 1000;
	size_t ret;

	if (argc != 3){
		fprintf(stderr,"Specify the source and the target\n");
		return 1;
	}
	
	// Openning the file to read (only for read)
	out = open(argv[1], O_RDONLY);
	
	if(out == -1){
		fprintf(stderr,"Couldn't open the file\n");
		return 1;
	} 
	
	char* buffer = malloc(buf_size+1); 
	ret = read(out,buffer,buf_size);

	if(ret == -1){
		fprintf(stderr,"Error reading from file\n");
		return 1;
	}
	
	buffer[ret] = '\0'; 
	
	printf("The string read back is: %s\n",buffer);  
	
	ret = close(out);

	if(ret == -1){
		fprintf(stderr,"Error closing the file after reading.\n");
		return 1;
	}

	// Openning the file to write
	out = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT , S_IRUSR | S_IWUSR ); 
	
	if(out == -1){
		fprintf(stderr,"Couldn't open the file for writing\n");
		return 1;
	}
	
	// Writing data to file

	ret = write(out,buffer,strlen(buffer));
	
	if(ret == -1){
		fprintf(stderr,"Error writing to file\n");
		return 1;
	}
	
	// Done with writing.Closing the file.

	ret = close(out);

	if(ret == -1){
		fprintf(stderr,"Error closing the file after writing.\n");
		return 1;
	}

	free(buffer);

	return 0;
}
