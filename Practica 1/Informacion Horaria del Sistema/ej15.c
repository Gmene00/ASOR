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
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );
    int ano=info->tm_year;
    
    char buf[80];
    strftime(buf, 100, "%A, %H:%M", info);
    printf("Estamos a %s", buf);
    printf(" del %i\n", 1900+ano);
    return(0);
}