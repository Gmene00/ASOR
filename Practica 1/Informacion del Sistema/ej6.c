#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

int main(){
    printf("La longitud máxima de los argumentos: %li\n", sysconf(_SC_ARG_MAX));
	printf("El número máximo de hijos: %li\n", sysconf(_SC_CHILD_MAX));
	printf("El número máximo de ficheros abiertos: %li\n", sysconf(_SC_OPEN_MAX));
	return 0;
}