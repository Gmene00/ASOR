#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	int myupd6, s, cambios, bytes;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	ssize_t c;
	size_t size;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];
	struct tm * t_info;
	time_t t;
	fd_set set;
	if (argc != 3) {
		printf("Argumentos incorrectos");
		return -1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = 0;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	getaddrinfo(argv[1], argv[2], &hints, &res);        	
    myupd6 = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(myupd6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

    while (1) {
            FD_ZERO(&set);
            FD_SET(0, &set); 
            FD_SET(myupd6, &set); 
            cambios = select(myupd6 + 1, &set, NULL, NULL, NULL);
            if (cambios == -1) {
                printf("Error select()");
                return -1;
            }
            else if (cambios) {
                if (FD_ISSET(0, &set)) {
                    bytes = read(0, buf, BUFFER_SIZE);
                    printf("%d bytes recibidos entrada estandar.\n", bytes);
                }
                else {
                    addrlen = sizeof(addr);
                    c = recvfrom(myupd6, buf, BUFFER_SIZE, 0, (struct sockaddr * ) &addr, &addrlen);
                    buf[c] = '\0';
                    getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
                    printf("%ld bytes recibidos de %s:%s\n", c, host, serv);
                }
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
                    if (FD_ISSET(0, &set)) {
                        printf("%s\n", buf);
                    }
                    else {
                        sendto(myupd6, buf, size, 0, (struct sockaddr * ) &addr, addrlen);
                    }
                }
            }
    }
    close(myupd6);	
    printf("Fin\n");
    return 0;
}