#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char ** argv) {
	int tuberia;
	if (argc != 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	if ((tuberia = open("mituberia", O_WRONLY)) == -1) {
		printf("Error tuberia, comprueba el nombre...");
		return -1;
	}
	write(tuberia, argv[1], strlen(argv[1]) + 1);
    write(tuberia, "\n", 1);
	return 0;
}

//Terminal 1
//[cursoredes@localhost Tuberias con nombre]$ ./ej4 hola

//Terminal 2
//[cursoredes@localhost Tuberias con nombre]$ cat mituberia
//hola