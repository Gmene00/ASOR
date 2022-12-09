#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv){
    int p_h[2];//0->lectura 1->escritura
    int h_p[2];
    int fin = 0, nmsj = 0;
	char buf[256];
    if((pipe(p_h)==-1)||(pipe(h_p)==-1)){
        printf("Error pipe");
        return -1;
    }
    int pid=fork();
    if(pid==-1){
        printf("Error fork");
        return -1;
    }
    else if(pid==0){//Hijo
        close(p_h[1]);
		close(h_p[0]);
		while (!fin) {
			int n = read(p_h[0], buf, 256);
			buf[n] = '\0';
			printf("%s\n", buf);
			sleep(1);
			if (++nmsj == 10) {
				write(h_p[1], "q", 1);
				fin = 1;
			}
			else {
				write(h_p[1], "l", 1);
			}
		}
		close(p_h[0]);
		close(h_p[1]);
    }
    else{//Padre
        close(p_h[0]);
		close(h_p[1]);
		while(!fin) {
			scanf("%s", buf);
			write(p_h[1], buf, strlen(buf) + 1);
			read(h_p[0], buf, 1);
			if (buf[0] == 'q') {
				fin = 1;
			}
		}
		close(p_h[1]);
		close(h_p[0]);
    }
    return 0;
}