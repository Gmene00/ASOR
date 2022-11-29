#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>

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

int main(int argc, char **argv) {
    pid_t pid = fork();
    switch(pid) {
		case -1:
			perror("Error fork");
			return -1;
		case 0:
            myprint("hijo");
            int fdestandar = open("/tmp/daemon.out",O_CREAT | O_RDWR, 00777);
            int fderror = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
            int fdentrada = open("/dev/null", O_CREAT | O_RDWR, 00777);
            int fd2 = dup2(fdestandar,2);
            int fd3 = dup2(fderror, 1);
            int fd4 = dup2(fdentrada, 0);

            if (execvp(argv[1], argv + 1) == -1) {
                printf("Error execvp\n");
                return -1;
            }
			break;
		default:
            myprint("padre");
            wait(NULL);
            break;
    }
    return 0;
}
