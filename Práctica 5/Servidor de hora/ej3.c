#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int myudp6, s;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t lenaddr;
	ssize_t c;
	char buf[BUFFER_SIZE];

	if (argc != 4) {
		printf("Argumentos incorrectos");
		return -1;
	}
    if (argv[3][0] != 't' && argv[3][0] != 'd' && argv[3][0] != 'q') {
		printf("No existe comando");
		return -1;
	}
    memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &res)) {
		printf("Error getaddrinfo()\n");
		return -1;
	}
    myudp6 = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(myudp6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
    lenaddr = sizeof(addr);
	sendto(myudp6, argv[3], strlen(argv[3]) + 1, 0, (struct sockaddr * ) res->ai_addr, res->ai_addrlen);
    if (argv[3][0] != 'q') { 
		c=recvfrom(myudp6, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &lenaddr);
        buf[c] = '\0';
		printf("%s\n", buf);
	}
}