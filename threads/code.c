#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NUM 4

void *myfunc(void *args)
{
    char *msg = *(int *)args;
    printf("Hola desde el hilo %d\n", msg);
    for (int i = 0; i < 500; i++)
    {
        printf("thread [%d]: %d\n", msg, i);
        usleep(1000000);
    }
}

int main()
{
    pthread_t thread[THREAD_NUM];
    int ret1, ret2;
    int i;

    for (i = 0; i < THREAD_NUM; i++)
        pthread_create(&thread[i], NULL, myfunc, &i);

    printf("Función principal PID: %d\n", getpid());

    for (i = 0; i < THREAD_NUM; i++)
        pthread_join(thread[i], NULL);

    return 0;
}