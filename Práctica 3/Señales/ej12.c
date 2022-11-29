#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int c_sigint = 0;
volatile int c_sigtstp = 0;
volatile int totalsignal = 0;

void myhandler(int mysignal){
  if (mysignal == SIGINT) c_sigint++;
  if (mysignal == SIGTSTP) c_sigtstp++;
  totalsignal++;
}

int main(){
    struct sigaction myaction; 
    sigaction(SIGINT, NULL, &myaction); 
    myaction.sa_handler = myhandler;
    sigaction(SIGINT, &myaction, NULL); 
    sigaction(SIGTSTP, NULL, &myaction);
    myaction.sa_handler = myhandler;
    sigaction(SIGTSTP, &myaction, NULL);

    sigset_t set;
	sigemptyset(&set);
	while (totalsignal < 10);

	printf("SIGINT: %i\n", c_sigint);
	printf("SIGTSTP: %i\n", c_sigtstp);


  return 0;
}