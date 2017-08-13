# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

/**
 * 
 * The  exec() family of functions replaces the current process image with
 * a new process image. This code will illustrate the functionality od the execl() command
 * 
 * */

int main(int argc, char**argv){

	int pid;
	
	//printf("\n The program pid is : %d \n",getpid());
	//printf("The program's parent pid is : %d \n",getpid());
	
	pid = fork();
    
    
	if(pid < 0){
		perror("fork error");
		exit(1);
	}
	
	else if(pid == 0){
	 
		execl("/bin/ls", "-l", argv[1], NULL);
		puts("Program ls has terminated");
	}
	else{
		
		printf("I am the parent process\n");
		wait(NULL);
	}

	return 0;
}


	
