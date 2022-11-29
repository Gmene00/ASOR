#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>


int main(void) {
	char path[PATH_MAX];

	printf("PID: %d\n", getpid());
	printf("PPID: %d\n", getppid());
	printf("SID: %d\n", getsid(getpid()));
	printf("PGID: %d\n", getpgid(getpid()));
	printf("Nº maximo de ficheros: %ld\n", sysconf(_SC_OPEN_MAX));

	if ( getcwd(path, PATH_MAX) == NULL) {
		perror("Error");
		return -1;
	}
	printf("Directorio: %s\n", path);
    return 0;
}