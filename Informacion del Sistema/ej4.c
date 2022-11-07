#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

int main(){
    struct utsname buffer;
    uname(&buffer);
    printf("Nombre del sistema = %s\n", buffer.sysname);
    printf("Nombre del nodo = %s\n", buffer.nodename);
    printf("Release = %s\n", buffer.release);
    printf("Version = %s\n", buffer.version);
    printf("Maquina = %s\n", buffer.machine);
    return 0;
}