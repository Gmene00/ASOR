#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    struct timeval timestruc;
    /*
    struct timeval{
        time_t tv_sec ;   //used for seconds
        suseconds_t tv_usec ;   //used for microseconds
    }*/
	int a = gettimeofday(&timestruc, NULL);
    int ini = timestruc.tv_usec;

    int i;
    for (i = 0; i < 1000000; i++);
    
    int b = gettimeofday(&timestruc, NULL);
    int fin = timestruc.tv_usec;

    printf("Tarda: %i\n",fin-ini);
    return 1;
}