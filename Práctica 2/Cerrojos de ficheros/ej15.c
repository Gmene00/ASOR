#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char ** argv) {
	int fd;
	if (argc != 2) {
		printf("Argumentos incorrectos\n");
		return -1;
	}
	int archivo= open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (archivo == -1) return -1;
	if ( lockf(archivo,F_LOCK, 0) == -1) {
		perror("Error al bloquear");
        return -1;
	}
	else {
		printf("Hora pre bloqueo: %ld\n", time(NULL));
		sleep(10);
		lockf(fd, F_ULOCK, 0);
		printf("Hora tras bloqueo: %ld\n", time(NULL));
	}
	close(archivo);
	return 0;
}