#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int gestionar_mensaje(int myupd6) {
	int s;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	ssize_t c;
	size_t size;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];
	struct tm * t_info;
	time_t t;

	while (1) {
		addrlen = sizeof(addr);
		c = recvfrom(myupd6, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &addrlen);
		buf[c] = '\0';
		s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
		printf("Hijo %d: %ld bytes recibidos de %s:%s\n", getpid(), c, host, serv);

		if (buf[0] == 'q') {
			break;
		}
		else if ( buf[0] != 't' && buf[0] != 'd') {
			printf("No existe comando");
		}
		else {
			t = time(NULL);
			t_info = localtime(&t);	
			if (buf[0] == 't') {
				size = strftime(buf, BUFFER_SIZE, "%H:%M:%S", t_info);
			}
			else {
				size = strftime(buf, BUFFER_SIZE, "%Y-%m-%d", t_info);
			}
			c = sendto(myupd6, buf, size, 0, (struct sockaddr * ) &addr, addrlen);
		}			
	}
	close(myupd6);	
	printf("Fin\n");
	return 0;
}


int main(int argc, char ** argv) {
	int myupd6, s;
	struct addrinfo hints, * res;
	if (argc != 3) {
		printf("Argumentos incorrectos");
		return -1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	s = getaddrinfo(argv[1], argv[2], &hints, &res); 
	myupd6 = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(myupd6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	
    int i;
	for (i = 0; i < 5; i++) {
		pid_t pid = fork();

		switch(pid) {
			case -1:
				printf("Error fork()");
				return -1;
			case 0:
				return gestionar_mensaje(myupd6);
			default:
				break;
		}
	}
	for (i = 0; i < 5; i++) {
		int hijo = wait(NULL);
		printf("Fin el hijo %d\n", hijo);
	}

	freeaddrinfo(res);
	return 0;
}