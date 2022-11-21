#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(int argc, char ** argv) {
	if (argc != 2) {
		printf("Argumentos incorrectos\n");
		return 0;
	}
	struct stat *ino;
    ino = malloc(sizeof(struct stat));
    if ( stat(argv[1], ino) == -1 ) {
		free(ino);
		return -1;
	}
	printf("Major: %d\n", major(ino->st_dev));
	printf("Minor: %d\n", minor(ino->st_dev));
	printf("Inodo %ld\n", ino->st_ino);
	printf("Tipo y modo de fichero: %d\n", ino->st_mode);
	printf("Ultimo acceso %s", ctime(&ino->st_atime));
	free(ino);
	return 0;
}
//time_t    st_mtime;   /* time of last modification */
//time_t    st_ctime;   /* time of last status change */