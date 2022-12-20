#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#define BUFFER_SIZE 500

int main(int argc, char *argv[]){
    int myudp6, s,c, myclient;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
	char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];//definimos los tamaños maximos
    if (argc != 3) {
		printf("Argumentos incorrectos");
		return -1;
	}
	memset(&hints, 0, sizeof(struct addrinfo));
    //¿reserva la estructura?, es lo que aparece en el manual.
	hints.ai_flags = 0; //Aplica flags
	hints.ai_family = AF_UNSPEC;//IPv4 o IPv6, permite ambos
	hints.ai_socktype = SOCK_STREAM; //Al ser TCP el tipo es de flujo

    s = getaddrinfo(argv[1], argv[2], &hints, &res); //Dado el host y el puerto, devuelve la estructura del tipo addrinfo
    /*
    ipv4 localhost shorthand -> 127.0. 0.1 (loopback address) 
    ipv6 localhost shorthand -> ::1
    */
    //HINTS -> specifies criteria for selecting the socket address structures returned in the list pointed to by res.
	//res -> resultado
    if (s) {//Returns 0 if it succeeds
		printf("Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
	}
    //Dominio, tipo y protocolo.
    myudp6 = socket(res->ai_family, res->ai_socktype, res->ai_protocol);//Create an endpoint for communication
    //returns a file descriptor that refers to that endpoint, con lo devuelto en getaddrinfo.
	if (myudp6 == -1) {//fd = -1 -> error
		printf("Error socket()\n");
		return -1;
	}
    c = connect(myudp6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
    //initiate a connection on a socket
    //connects the socket referred to by the file descriptor sockfd to the address specified by addr. The addrlen argument specifies the size of addr.
    if (c!=0) {
        //If the connection or binding succeeds, zero is returned.
	    printf("Error connect()\n");
       	return -1;
	}

    while(1){//mientras que no lo cierre el cliente
        scanf("%s", buf);//leemos del cliente
        if (strlen(buf) == 1 && buf[0] == 'Q') {//ponemos que sea el tamaño 1 porque si una frase empezase por Q, cerraria la conexion
			break;
		}
        else{
            c = send(myudp6, buf, strlen(buf) + 1, 0);//send a message on a socket, envia el mensa
        		if (c == -1) {
				printf("Error send()\n");
				return -1;
			} 
			c = recv(myudp6, buf, BUFFER_SIZE, 0);//receive a message from a socket
            //-1 if an error occurred.
            if(c==-1){
                printf("Error recv\n");
                return -1;
            }
			buf[c] = '\0';
			printf("%s\n", buf);
        }
    }
    close(myudp6);//Cerramos el fd
}      
	