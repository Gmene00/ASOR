#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv){
    int fd[2];
    if(argc>5){
        printf("Argumentos invalidos\n");
        return -1;
    }
    if(pipe(fd)==-1){
        printf("Error pipe");
        return -1;
    }
    int pid=fork();
    if(pid==-1){
        printf("Error fork");
        return -1;
    }
    else if(pid==0){//Hijo
        close(0);//Cierra la salida estandar
        dup2(fd[0],0);
        close(fd[0]);//Extremo lectura
        close(fd[1]);//Extremo escritura
        execlp(argv[3],argv[3],argv[4],NULL);
    }
    else{//Padre
        close(1);//Cierra la entrada estandar
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1],argv[1],argv[2],NULL);
    }
    return 0;
}

//[root@localhost CodigoP4]# ./ej1 echo 12345 wc -c
//[root@localhost CodigoP4]# 6