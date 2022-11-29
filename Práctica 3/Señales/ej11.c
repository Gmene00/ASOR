#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	sigset_t myset;
    //export "SLEEP_SECS"=10 para poder hacer luego el getenv
	char * segundos = getenv("SLEEP_SECS");
	if (segundos == NULL) {
		printf("Error sleep secs\n");
		return -1;
	}
	sigemptyset(&myset);//Inicializa la estructura que almacenara las señales.
    //Añadimos las señales
	sigaddset(&myset, SIGINT);
	sigaddset(&myset, SIGTSTP);
    printf("Codigo bloqueado\n");
	sigprocmask(SIG_BLOCK, &myset, NULL);//Protege la seccion del codigo.
	sleep(atoi(segundos));//Dormimos el proceso
	
    sigset_t pendientes;
    sigemptyset(&myset);
	sigpending(&pendientes);

	if (sigismember(&pendientes, SIGINT)) {
		printf("SIGINT\n");
	}
	if (sigismember(&pendientes, SIGTSTP)) {
		printf("SIGTSTP\n");
        sigprocmask(SIG_UNBLOCK, &myset, NULL);
        printf("Codigo desbloqueado\n");
	}
	return 0;
}
/*Terminal 1
[root@localhost Señales]# gcc ej11.c -o ej11
[root@localhost Señales]# ./ej11
Codigo bloqueado
SIGTSTP
Codigo desbloqueado
[root@localhost Señales]#
*/

/*Terminal 2
[root@localhost CodigoP3]# kill -s SIGTSTP 5032
*/