/* Author: E13200
 * Title:  Lab02-Exercise03.1
 * Date:   2017.08.21
 * Description: 
 * 
 * The  exec() family of functions replaces the current process image with
 * a new process image. This code will illustrate the functionality od the execl() command
 * When exec() is used to replace the execution image of a forked child, all the communication
 * means are lost since exec() replaces all the original code. Therefore, here it is impossible 
 * to use the pipe() command to interprocess communicaition.
 * 
 * compilation:
 * gcc -Wall exec.c -o test
 * ./test <argument_name:check the output of the ls -l command>
 * 
 * */

# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>


int main(int argc, char**argv){

	int pid;
	pid = fork();
    
    
	if(pid < 0){
		perror("fork error");
		exit(1);
	}
	
	else if(pid == 0){
	 
		execl("/bin/ls", "-l", argv[1], NULL);  // replays from a another process.
		puts("Program ls has terminated");
	}
	else{
		
		printf("I am the parent process\n");
		wait(NULL);
	}

	return 0;
}


	
