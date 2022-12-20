#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

int main(int argc, char ** argv) {
	struct addrinfo * respo, * a;
	char host[BUFFER_SIZE];
	if (argc != 2) {
		printf("Argumentos incorrectos");
		return -1;
	}

    if (getaddrinfo(argv[1], NULL, NULL, &respo) != 0) {
		printf("Error getaddrinfo()\n");
		return -1;
	}
	for (a = respo; a != NULL; a = a->ai_next) {
		if (getnameinfo(a->ai_addr, a->ai_addrlen, host, BUFFER_SIZE, NULL, 0, NI_NUMERICHOST) != 0) {
			printf("Error getnameinfo()\n");
			return -1;
		}
		printf("%s\t%d\t%d\n", host, a->ai_family, a->ai_socktype);
	}
	return 0;
}
/*
[cursoredes@localhost Gestion de direcciones]$ ./ej1 147.96.1.9
147.96.1.9      2       1
147.96.1.9      2       2
147.96.1.9      2       3

[cursoredes@localhost Gestion de direcciones]$ ./ej1 fd00::a:0:0:0:1
fd00:0:0:a::1   10      1
fd00:0:0:a::1   10      2
fd00:0:0:a::1   10      3

[cursoredes@localhost Gestion de direcciones]$ ./ej1 www.google.com  --> no funciona ya que estamos en la maquina virtual

[cursoredes@localhost Gestion de direcciones]$ ./ej1 147.96.1.99999
Error getaddrinfo()
*/