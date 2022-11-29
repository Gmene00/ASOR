#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	int len = sysconf(_SC_ARG_MAX);
	char comando[len];
	
	if (argc < 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
    int i;
	for ( i = 1; i < argc; i++) {
		strncat(comando, argv[i], len);
		strncat(comando, " ", 2);
	}

	if (system(comando) == -1) {
		printf("Error execvp\n");
		return -1;
	}
	printf("El comando terminó de ejecutarse\n");
	return 0;
}
//En este caso si que se imprime la cadena.