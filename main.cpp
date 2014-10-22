#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "ljob.h"
#include "lthread.h"
#include "lthreadpool.h"
using namespace std;

void* task(void* arg)
{
    usleep(1);
    printf("Task running.%2d..Thread working: 0x%lx\n", *((int*)arg), pthread_self());
}

int main()
{
    LThreadPool lthpool(5);
    int i;
    for (i = 0; i < 20; i++) {
        LBaseJob* job = new LBaseJob();
        job->routine = task;
        int *tmp = new int;
        *tmp = i;
        job->arg = tmp;
        lthpool.run(job);
    }
    sleep(2);
    lthpool.destroy();
    return 0;
}
