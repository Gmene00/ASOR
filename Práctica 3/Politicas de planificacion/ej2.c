#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char **argv) {
    int planificador = sched_getscheduler(0);

    if(planificador==SCHED_OTHER){
        printf("SCHEDULER: OTHER\n");
    }
    else if(planificador==SCHED_FIFO){
        printf("SCHEDULER: FIFO\n");
    }
    else if(planificador==SCHED_RR){
        printf("SCHEDULER: RR\n");
    }
    else{
        printf("Error\n");
    }

    struct sched_param p;
    sched_getparam(0,&p);
    printf("PRIORIDAD: %i\n", p.sched_priority);

    printf("MAX: %i - MIN: %i\n", sched_get_priority_max(planificador), sched_get_priority_min(planificador));

}