#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	
	if (execvp(argv[1], argv + 1) == -1) {
		printf("Error execvp\n");
		return -1;
	}
	printf("El comando termino de ejecutarse\n");
	return 0;
}
//Nunca se ejecutara el ultimo printf ya que al realizarse la llamada a execvp
//se crea un nuevo proceso con lo que se le pase como argumento.
//./ej7 “ps -el” nunca se ejecutará ya que las comillas no las reconoce, por lo que da error.