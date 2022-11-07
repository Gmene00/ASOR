#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>

int main(){
    uid_t uid = getuid();
    printf("UID Real: %d\n", uid);
    printf("UID efectivo: %d\n", geteuid());
    //Se podría saber si se tiene el bit setuid activado el uid real y el efectivo fuesen distintos.
    struct passwd *a=getpwuid(uid); 

    char *nombre = a->pw_name;
    char *directorio = a->pw_dir;
    char *descripcion = a->pw_gecos;
    
    printf("Nombre de usuario: %s\n", nombre);
    printf("Directorio home : %s\n", directorio);
    printf("Descripcion : %s\n", descripcion);
    return 1;
}