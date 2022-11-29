#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>

void myprint(char *nombre){
    char path[PATH_MAX];

	printf("PID %s: %d\n", nombre, getpid());
	printf("PPID %s: %d\n", nombre, getppid());
	printf("SID %s: %d\n", nombre, getsid(getpid()));
	printf("PGID %s: %d\n", nombre, getpgid(getpid()));
	printf("Nº maximo de ficheros %s: %ld\n", nombre, sysconf(_SC_OPEN_MAX));

	if ( getcwd(path, PATH_MAX) == NULL) {
		printf("Error %s", nombre);
	}
	printf("Directorio %s: %s\n", nombre, path);
}

int main(void) {
    pid_t pid = fork();
    switch(pid) {
		case -1:
			perror("Error fork");
			return -1;
		case 0:
            sleep(10);//comentar para el apartado b
            myprint("hijo");
			break;
		default:
            //sleep(10);//descomentar apartado b
            myprint("padre");
            wait(NULL);//comentar para el apartado b
            break;
    }
    return 0;
}

//a)El hijo se queda huérfano y el ppid lo recoge la shell o init.
//b) Esto es lo que sale
//6478  1000  4117 S ./ej6
//6479  1000  4117 Z [ej6] <defunct>