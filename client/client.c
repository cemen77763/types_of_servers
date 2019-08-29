#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define handle_error(msg)\
 do { perror(msg); exit(EXIT_FAILURE); } while(0);

int main(int agrc, char *argv[]){
	int sfd;
	int working = 1;
	char buf[255];
	struct sockaddr_in peer_addr;

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
		handle_error("socket");

	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	peer_addr.sin_port = htons(9999);

	if (connect(sfd, (struct sockaddr *) &peer_addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("connect");

	while(working){
		scanf("%s", buf);
		send(sfd, buf, 255, 0);
		if (!strncmp(buf, "quit", 5)){
 			close(sfd);
 			working = 0;
 			break;
 		}

		recv(sfd, buf, 255, 0);
 		printf("=========================\n%s\n=========================\n", buf);
	}

	exit(EXIT_SUCCESS);
}