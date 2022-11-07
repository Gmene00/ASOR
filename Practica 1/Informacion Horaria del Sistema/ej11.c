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
	time_t t = time(NULL);
	printf("Epoch: %li\n", t);
	return 0;
}