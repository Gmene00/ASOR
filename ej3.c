#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
const int errores = 255;

int main(){
    int i;
    for(i=0; i<errores;i++){
        printf("ERROR(%d): %s\n", i, strerror(i));
    }
    return 1;
}