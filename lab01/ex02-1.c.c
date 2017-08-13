# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

int main(void){

	int pid;
	
	//printf("\n The program pid is : %d \n",getpid());
	//printf("The program's parent pid is : %d \n",getpid());
	
	pid = fork();
    
    
	if(pid < 0){
		perror("fork");
		exit(1);
	}
	
	else if(pid == 0){
		puts("[*]This is the child process ");
		printf("My pid is %d \n", getpid());
		//printf("My parent pid is %d \n",getppid());
	}
	else{
		//wait(NULL);
		puts("[**]This is the perent process ");
		printf("The process id is : %d \n",getpid());
		wait(NULL);
		
	
	}

	return 0;
}

/** This program will simply dispay the child and the parent output
 *  using the fork() as the system commands
 * /
	
