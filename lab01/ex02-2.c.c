# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

/** EX-02
 * get the fork with the loop
 * */

int main(void){

	//int pid;
	
	//printf("\n The program pid is : %d \n",getpid());
	//printf("The program's parent pid is : %d \n",getpid());
	
	
	for(int i=0;i<3;i++){
		fork();
		printf("%d My pid is:%d \n",i,getpid());
		wait(NULL);
    }
    
    printf("pid is %d \n",getpid());

	return 0;
}


/* ** first create the child process and wair for untill return the process 
 * after return the chiled with same id parent will be created the next
 * processes.
 * this program will illustrate how procceses and pids working
 */	
