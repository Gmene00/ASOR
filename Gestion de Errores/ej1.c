#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main() {
   int a = setuid(2);
   if(a==-1){
       perror("Ha fallado");
   }
   return 1;
}