#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <string.h>
#include <wire.h>


int main(){
	
int pid;
int server_sockfd, client_sockfd;
socklen_t server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

printf("%d \n", SOCK_STREAM);
//AF_INET family provides interprocess communication between processes that run on the same system or on different systems.
/*TCP/SOCK_STREAM is a connection-based protocol. The connection is established and the two parties have a conversation until 
 * the connection is terminated by one of the parties or by a network error. UDP/SOCK_DGRAM is a datagram-based protocol.
 *  You send one datagram and get one reply and then the connection */
  
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = htonl(INADDR_ANY);
/*INADDR_ANY is used when you don't need to bind a socket to a specific IP. When you use this value as the address 
 * when calling bind() */
 
server_address.sin_port = htons(12345);
server_len = sizeof(server_address);
bind(server_sockfd, (struct sockaddr *)&server_address,server_len);

/* Create a connection queue, ignore child exit details and wait for
clients. */

listen(server_sockfd, 5);

while(1) {
	char ch[] = "am\n";

	printf("I am waiting\n");

/* Accept connection. */

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

	if (client_sockfd < 0){
		perror("ERROR on accept");
		exit(1);
		}

	pid  = fork();

	if(pid == 0) {
		for(int i=0;i<strlen(ch);i++){
			write(client_sockfd,&ch[i], 1);
		}
		printf("\n");
		sleep(5);
		close(client_sockfd);
		exit(0);
		}

/* Otherwise, we must be the parent and our work for this client is
finished. */

	else 
		close(client_sockfd);

	}
	//wait(NULL);
}
