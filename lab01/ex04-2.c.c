# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

/** EX -04/2
 * this code can be used to get the command line from uaser and prin the 
 * result in the terminal
 * */

int main(void){

	int pid;
	char command[256];
	char arg[10];
	
	printf("Wellcome to the bash.Type command to run\n");
	scanf( "%s" ,command);
	printf("type argument\n");
	
	fgets(arg, 10, stdin);
	
	// get the argument length
	int arglen = strlen(arg);
	
	if(arglen>0 && arg[arglen-1]=='\n')
		arg[arglen-1] = '\0';
		
	pid = fork();
    
    // if error occur print the message
	if(pid < 0){
		perror("fork error");
		exit(1);
	}
	
	else if(pid == 0){
		if (strlen(arg) == 0){
			execl(command,command,NULL);  // if there is no argument
		}
		else{
			execl(command,command,arg,NULL); // if there is a argument
		}
		
	}
	else{
		
		printf("I am the parent process\n");
		wait(NULL);
	}

	return 0;
}


	

