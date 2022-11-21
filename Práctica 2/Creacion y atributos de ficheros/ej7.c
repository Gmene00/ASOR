#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    umask(0027);
    int archivo= open("ejercicio.txt", O_RDWR | O_CREAT, 0645);
    if (archivo == -1) return -1;
    return 1;
}

//-rw-r----- 1 cursoredes cursoredes    0 Nov 21 10:36 ejercicio.txt