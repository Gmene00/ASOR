#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

int main(){
    printf("El número máximo de enlaces: %li\n", pathconf("ej7.c", _PC_LINK_MAX));
	printf("El tamaño máximo de una ruta: %li\n", pathconf("ej7.c", _PC_PATH_MAX));
	printf("El tamaño máximo de un nombre de fichero: %li\n", pathconf("ej7.c", _PC_NAME_MAX));
    return 0;
}