#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int myudp6;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t lenaddr;
	ssize_t c;
	size_t size;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];
	struct tm * t_info;
	time_t t;

	if (argc != 3) {
		printf("Argumentos incorrectos");
		return -1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;

	if (getaddrinfo(argv[1], argv[2], &hints, &res)) {
		printf("Error getaddrinfo()\n");
		return -1;
	}
    myudp6 = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(myudp6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

	while (1) {
		lenaddr = sizeof(addr);
		c = recvfrom(myudp6, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &lenaddr);
		buf[c] = '\0';
		if (getnameinfo((struct sockaddr *) &addr, lenaddr, host, 
				NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV) != 0) {
			printf("Error getnameinfo()\n");
			return -1;
		}
		printf("Byte %ld de %s:%s\n", c, host, serv);

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
			c = sendto(myudp6, buf, size, 0, (struct sockaddr * ) &addr, lenaddr);			
		}
	}
	close(myudp6);	
	printf("Fin\n");
	return 0;
}

/* En el servidor
[root@localhost Servidor de hora]# ./ej2 :: 3000
Byte 2 de ::ffff:192.168.0.100:50109
Byte 1 de ::ffff:192.168.0.100:50109
No existe comandoByte 2 de ::ffff:192.168.0.100:50109
Byte 1 de ::ffff:192.168.0.100:50109
No existe comandoByte 2 de ::ffff:192.168.0.100:50109
Fin

En el cliente
[root@localhost cursoredes]# nc -u 192.168.0.1 3000
t
17:53:06
d
2022-12-12
q
^C
*/