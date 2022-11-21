#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv) {
	if (argc != 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	int archivo= open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (archivo == -1) return -1;
	if (dup2(archivo, 1) == -1) return -1;
	
	printf("Hola, redirigimos esto.\n");
	close(archivo);
	return 0;
}