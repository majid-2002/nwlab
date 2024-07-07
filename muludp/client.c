// server.c		 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAX 100
#define sa struct sockaddr

int main() {
	struct sockaddr_in serv;
	int sockfd, slen = sizeof(serv);
	char buf[MAX];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(8888);

	bind(sockfd, (sa*)&serv, slen);

	printf("Server listening on port %d...\n", ntohs(serv.sin_port));

	while (1) {
    	struct sockaddr_in cli;
    	int clen = sizeof(cli);	
    	// Receive message from any client
    	bzero(buf, MAX);
    	recvfrom(sockfd, buf, MAX, 0, (sa*)&cli, &clen);
    	printf("Received from client %s:%d - %s", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port), buf);    
    char msg[] ="msg received by server\n";
    	// send message back to the same client
    	sendto(sockfd, msg, sizeof(msg), 0, (sa*)&cli, clen);
	}
	close(sockfd);
	return 0;
}

// client1.c and client2.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAX 100
#define sa struct sockaddr

int main() {
	struct sockaddr_in serv;
	int sockfd, slen = sizeof(serv);
	char buf[MAX];

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(8888);

	printf("Server connected\n");

	while (1) {
    	printf("Type a message: ");
    	bzero(buf, MAX);
    	fgets(buf, MAX, stdin); // Read from stdin

    	// Send message to server
    	sendto(sockfd, buf, MAX, 0, (sa*)&serv, slen);

    	// Receive message from server
    	bzero(buf, MAX);
    	 recvfrom(sockfd, buf, MAX, 0, (sa*)&serv, &slen);
    	printf("%s", buf);
	}

	close(sockfd);
	return 0;
}