#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define THREAD_NUM 10
sem_t semaphore;

void *routine(void *args)
{
    sem_wait(&semaphore);
    sleep(3);
    char c = *(int *)args;
    printf("Hola desde el hilo[%d]\n", c);
    sem_post(&semaphore);
}

int main(int args, char *argv[])
{
    int i;
    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 3);

    for (i = 0; i < THREAD_NUM; i++)
        pthread_create(&th[i], NULL, &routine, &i);

    for (i = 0; i < THREAD_NUM; i++)
        pthread_join(th[i], NULL);

    sem_destroy(&semaphore);

    return 0;
}