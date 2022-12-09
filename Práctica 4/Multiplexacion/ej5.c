#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>


int main(void) {
	int fd1, fd2, cambios, bytes;
	char buffer[256];
	fd_set set;

	fd1 = open("mituberia1", O_RDONLY | O_NONBLOCK);
	fd2 = open("mituberia2", O_RDONLY | O_NONBLOCK);
	FD_ZERO(&set);
	FD_SET(fd1, &set);
	FD_SET(fd2, &set);

	int nmaxfd=0;
	if(fd1>fd2){
		nmaxfd=fd1;
	}
	else{
		nmaxfd=fd2;
	}

	cambios = select(nmaxfd + 1, &set, NULL, NULL, NULL);
	if (cambios!=-1) {
		if (FD_ISSET(fd1, &set)) {
			bytes = read(fd1, buffer, 256);
			buffer[bytes] = '\0';
			close(fd1);
			fd1 = open("mituberia1", O_RDONLY | O_NONBLOCK);
			printf("mituberia1: %s", buffer);
		}
		else {
			bytes = read(fd2, buffer, 256);
			buffer[bytes] = '\0';
			close(fd2);
			fd2 = open("mituberia2", O_RDONLY | O_NONBLOCK);
			printf("mituberia2: %s", buffer);
		}
	}
	else {
		printf("No dato\n");
	}
	return 0;
}
//Terminal 1
//[cursoredes@localhost Multiplexacion]$ ./ej5
//mituberia2: Hola

//Terminal 2
//[cursoredes@localhost Multiplexacion]$ echo "Hola" > mituberia2