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

 void editing(char *str);

 int main(){
 	pid_t pid;
 	int sfd, cfd;
 	int flag = 1, i = 0;
 	char buf[255];
 	struct sockaddr_in my_addr, peer_addr;
 	socklen_t peer_addr_size;

 	sfd = socket(AF_INET, SOCK_STREAM, 0);
 	if (sfd == -1)
 		handle_error("socket");

 	my_addr.sin_family = AF_INET;
 	my_addr.sin_port = htons(9999);
 	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

 	if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1)
 		handle_error("bind");
 	if (listen(sfd, 5) == -1)
 		handle_error("listen");

 	while(flag){
 		cfd = accept(sfd, (struct sockaddr*) &peer_addr, &peer_addr_size);
 		if (cfd == -1)
 			handle_error("accept");

 		pid = fork();
 		if (pid == 0){
 			char buf[255];
 			int flag = 1;
 		
 			while(flag){
 				recv(cfd, buf, 255, 0);
 				if (!strncmp(buf, "quit", 5)){
 					close(cfd);
 					exit(EXIT_SUCCESS);
 				} else{
 					editing(buf);
 					send(cfd, buf, 255, 0);
 				}
 			}
 		}
 		close(cfd);
 	}

 	exit(EXIT_SUCCESS);
 }

 void editing(char *str){
 	char mes[25] = "I receive your message: ";
 	char buf[255];
 	int i = 0, j = 0, m = 0;

 	while(str[i] != '\0'){
 		buf[i] = str[i];
 		i++;
 	}

 	while(j < 24){
 		str[j] = mes[j];
 		j++;
 	}

 	while(i > 0){
 		str[j] = buf[m];
 		m++;
 		j++;
 		i--;
 	}
 	str[j] = '\0';

 	return;
 }