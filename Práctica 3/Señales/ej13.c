#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int myabort = 0;
volatile int mydelete = 0;

void myhandler(int mysignal){
  if (mysignal == SIGUSR1) myabort=1;
  if (mysignal == SIGALRM) mydelete=1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error argumentos incorrectos\n");
        return -1;
    }
    struct sigaction myaction; 
    sigaction(SIGINT, NULL, &myaction); 
    myaction.sa_handler = myhandler;
    sigaction(SIGINT, &myaction, NULL); 
    sigaction(SIGALRM, NULL, &myaction); 
    myaction.sa_handler = myhandler;
    sigaction(SIGALRM, &myaction, NULL); 
    
    sigset_t myset;
	sigemptyset(&myset);
    sigaddset(&myset, SIGUSR1);
    sigaddset(&myset, SIGALRM);
    
    alarm(atoi(argv[1]));
	printf("%d segundos restantes. Abortar -> SIGUSR1\n", atoi(argv[1]));
    sleep(atoi(argv[1]));

	if (mydelete==1) {
        printf("Borrado\n");
		unlink(argv[0]);
	}
    if (myabort==1) {
		printf("Abortado\n");
	}
    
    return 0;
}