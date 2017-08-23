
/*Title : Fixing the code.see the desciption from the problem of the code from the answers.pdf
 *Date  : 2017.08.23
 *Compilation: 
 *gcc -Wall example3.2_fixed.c -o test
 *./test <argument>    ex] ./test sri lanka
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>



#define INPUTFILE "fixtures.txt"

/* function prototypes */
void die(const char*);

int main(int argc, char **argv)
{
	int pipefd[2];
	int pid;
  int status;

	if (argc < 2)
	{
		printf("%s: missing operand\n", argv[0]);
		printf("Usage: %s <search_term in %s>\n", argv[0],INPUTFILE);
		exit(EXIT_FAILURE);
	}
	
	char *cat_args[] = {"cat", INPUTFILE, NULL};
	char *grep_args[] = {"grep", "-i", argv[1], NULL};

	// make a pipe (fds go in pipefd[0] and pipefd[1])

	if(pipe(pipefd) == -1) 
		die("pipe()");

	pid = fork();
	if(pid == (pid_t)(-1))
		die("fork()");

	if (pid == 0){
		// execute the cat first. makesure the parent waiting for the child.

		// close standard output
		close(1);

		// replace standard output with output part of pipe
		if(dup(pipefd[1]) == -1)
			die("dup()");

		// close unused input half of pipe
		close(pipefd[0]);

		// execute cat
		if(execvp("cat", cat_args) == -1)
			die("execvp()");

		exit(EXIT_SUCCESS);

	}


	else{
		// wait for the child
    wait(&status);
    // Close standard input
		close(0);

		// replace standard input with input part of pipe
		if(dup(pipefd[0]) == -1)
			die("dup()");

		// close unused half of pipe
		close(pipefd[1]);

		// execute grep
		if(execvp("grep", grep_args) == -1)
			die("execvp()");

		exit(EXIT_SUCCESS);
		
	}
}

/* A better way to Die (exit) */
void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}
