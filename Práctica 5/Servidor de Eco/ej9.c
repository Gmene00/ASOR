#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#define BUFFER_SIZE 500

static void my_handler(int arg) {
	while (waitpid(-1, 0, WNOHANG) != -1) {}//wait for process to change state
    //No hacemos nada dentro
    /*
    The value of pid can be:
    -1--> meaning wait for any child process whose process group ID is 
    equal to the absolute value of pid.
    Esto quiere decir que se esperan a todos los hijos creados por la consola 
    que ejecuta el programa

    WNOHANG --> return immediately if no child has exited.
    si no ha finalizado alguno de los hijos especificados en el primer argumento, 
    no se quiere esperar a que lo hagan; es decir, se quiere una llamada no bloqueante. 
    */
}

int gestionar_mensaje(int myclient, struct sockaddr_storage addr) {
    socklen_t addrlen;
    int c, s, se;
    char buf[BUFFER_SIZE], host[NI_MAXHOST], serv[NI_MAXSERV];//definimos los tamaños maximos
    //getnameinfo -> Address-to-name translation to a corresponding host and service, in protocol-independent manner
    //host, NI_MAXHOST 
    //serv, NI_MAXSERV 
    //NI_NUMERICHOST --> flag, If set, then the numeric form of the hostname is returned.
    //NI_NUMERICSERV --> flag, If set, then the numeric form of the service address is returned.
	addrlen = sizeof(addr);
    s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	//On success, 0 is returned, and node and service names, if requested, are filled with null-terminated strings
    if (s != 0) {
		printf("Error getnameinfo(): %s\n", gai_strerror(s));
		close(myclient);//Cierra el file descriptor
		return -1;
	}
    printf("Hijo %d: Conexión desde %s:%s\n", getpid(), host, serv);
	while ((c = recv(myclient, buf, BUFFER_SIZE, 0))) {//receive a message from a socket, recibe todo el tamaño 500 del buffer
	    //return the number of bytes received, or -1 if an error occurred.
        if (c == -1) {
		    printf("Error recv()\n");
			close(myclient);//Cierra el file descriptor
			return -1;
		}
		se=send(myclient, buf, c, 0);//send a message on a socket, envia el mensaje de vuelta al fd del cliente.
        //On success, these calls return the number of bytes sent.  On error, -1
        if(se==-1){
            printf("Error send\n");
            return -1;
        }
    }
    printf("Hijo %d: Conexión terminada\n", getpid());	
	return 0;
}

int main(int argc, char *argv[]){
    int myudp6, s,b,l,se, myclient;
	struct addrinfo hints, * res;
	struct sockaddr_storage addr;
	socklen_t addrlen;
    struct sigaction myaction;
	ssize_t c;

	if (argc != 3) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	
	myaction.sa_handler = my_handler;//Funcion que controla las señales
	myaction.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &myaction, NULL);

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
    //BIND -> Assigns the address specified by addr to the socket referred to
    //by the file descriptor sockfd.  addrlen specifies the size, in
    //bytes, of the address structure pointed to by addr.
    b=bind(myudp6, (struct sockaddr *) res->ai_addr, res->ai_addrlen);//Une una direccion a un socket
	if (b) {//On success, zero is returned.
        printf("Error bind()\n");
        return -1;
	}
    l=listen(myudp6, 5);//Listen for connections on a socket.
    //5 -> defines the maximum length to which the
    //queue of pending connections for sockfd may grow, tam maximo de la cola.
    if (l) {//On success, zero is returned.
        printf("Error listen()\n");
	}       
	
    while(1){
        addrlen = sizeof(addr);
        //addr -> This structure is filled in with the address of the peer socket, as known to the communications layer.
        //addlen -> The exact format of the address returned addr is determined by the socket's address family
        myclient = accept(myudp6, (struct sockaddr *) &addr, &addrlen);//Accept a connection on a socket.
        //On success, these system calls return a file descriptor for the accepted socket
        pid_t pid = fork();
        if(pid==-1){
            printf("Error fork()\n");
        }
        else if (pid==0){//hijo
            gestionar_mensaje(myclient,addr);
        }
        else{
            close(myclient);
        }
        
    }
	return 0;
}
//Siempre hay que cerrar antes los clientes que el servidor, para poder seguir usando el mismo puerto.