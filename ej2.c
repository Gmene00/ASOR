#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
   int a = setuid(2);
   if(a==-1){
       perror("Ha fallado");
       printf("ERROR(%d): %s\n", a, strerror(a));
   }
   return 1;
}