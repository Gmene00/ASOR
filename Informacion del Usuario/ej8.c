#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main(){
    printf("UID Real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());
    //Se podría saber si se tiene el bit setuid activado el uid real y el efectivo fuesen distintos.
    return 0;
}