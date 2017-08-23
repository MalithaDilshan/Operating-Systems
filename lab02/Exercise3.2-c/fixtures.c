
/* Author: E13200
 * Title : Lab02-Excercise3.2-c
 * Date  : 2017.08.22
 * Description : demostrate the execution of 'cat fixtures | grep <search_term> | cut -b 1-9' command
 * using the pipe concept
 * 
 * gcc -Wall mycat.c -o test
 * follow this formact './testIO <in.txt> 'for example,
 * ./test /home/e13200/Desktop/test.txt

 * */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

#define INPUTFILE "fixtures.txt"

/* function prototypes */
void die(const char*);

int main(int argc, char **argv){
	// define two pipes
  int status;
	int pipefd[2];
	int pipefd1[2]; 
	int pid;

	if (argc < 2){
		printf("%s: missing operand\n", argv[0]);
		printf("Usage: %s <search_term in %s>\n", argv[0], INPUTFILE);
		exit(EXIT_FAILURE);
	}
	// define pointer arrays with arguments
	char *cat_args[] = {"cat", INPUTFILE, NULL};
	char *grep_args[] = {"grep", "-i", argv[1], NULL};
	char *cut_args[] = {"cut", "-b", "1-9", NULL};


	if (pipe(pipefd1) == -1)  // define the pipeline
		die("pipe2()");

	pid = fork();  // make parent and child

	if(pid == (pid_t)(-1))
		die("fork()");

	if (pid == 0){
		// child process

		if(pipe(pipefd) == -1) // define the second pipe
			die("pipe()");

		int pid2 = fork();

		if (pid2 < 0)
			die("fork2()");

		if (pid2 == 0){
			// the cat command have to handle from here. because this is the first command that should be execute before the 
			// grep command and cut command. The parent have to wait exit the this child.

			// replace standard output with output part of pipe
			if(dup2(pipefd[WRITE_END],1) == -1)
				die("dup2()");

			// close unused input half of pipe
			close(pipefd[READ_END]);

			// execute cat using the execvp command. Here this will use the above arguments defined 
			if(execvp("cat", cat_args) == -1)
				die("execvp()");

			exit(EXIT_SUCCESS);

		}

		else {

			// Parent of above child. this is the child of the main parent

			printf("New Parent Started and waiting for New Child...!\n");
			// wait for the child.waiting for  writing cat result to the stdout
			wait(&status);

			// replace standard input with input part of pipe. read the cat result from the read end of the pipeline
			if(dup2(pipefd[READ_END], 0) == -1)
				die("dup2()");
			sleep(1);
			// give the stdout for the write ennd of the next pipeline after reading
			if (dup2(pipefd1[WRITE_END], 1) == -1)
				die("dup2()");

			// after doing this there will be unused ends of defied pipeline. therefore it should lock these ends before execute the 
			// grep command
			close(pipefd[WRITE_END]);
			close(pipefd1[READ_END]);

			// execute grep. the result of the grep command now is in the write end of the pipfd1/defined as stdout.
			if(execvp("grep", grep_args) == -1)
				die("execvp()");

			exit(EXIT_SUCCESS);	

		}

		exit(EXIT_SUCCESS);
	}

	else{

		printf("Grand parent\n");
		// wait for the child execution
		wait(&status);
		// replace standard input with input part of pipe. reading from the stdin(read end of the pipfd1)
		if(dup2(pipefd1[READ_END], 0) == -1)
			die("dup2()");

		// here above I used the read end of the pipeline then it shoud be lock the unused end of this pipeline.
		close(pipefd1[WRITE_END]);

		printf("Result of the 'cat fixtures | grep <search_term> | cut -b 1-9' command --->\n");
		// execute the cut command
		if(execvp("cut", cut_args) == -1)
			die("execvp()");

		exit(EXIT_SUCCESS);
		
	}

}

void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}


