#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

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
	if (S_ISREG(ino->st_mode)) {
		link(argv[1], "rigido");
		symlink(argv[1], "simbolico");
	}
	free(ino);
	return 0;
}