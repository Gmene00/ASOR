#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
   int archivo= open("ejercicio.txt", O_RDWR | O_CREAT, 0645);
   if (archivo == -1) return -1;
   return 1;
}