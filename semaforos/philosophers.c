#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define PHILOSOPHER_NUM 5

sem_t forks[PHILOSOPHER_NUM];

void *dinner(void *args)
{
    int philosopher_id = *(int *)args;                  // Id para cada filósofo
    int left = philosopher_id;                          // Tenedor izquierdo
    int right = (philosopher_id + 1) % PHILOSOPHER_NUM; // Tenedor derecho

    while (1)
    {
        printf("Filósofo[%d] está pensando\n", philosopher_id);
        sleep(rand() % 6); // Asigna un tiempo aleatorio en segundos

        printf("Filósofo[%d] está hambriento\n", philosopher_id);

        // Espera a que los tenedores (semáforos) estén disponibles
        sem_wait(&forks[left]);  // Espera al tenedor izquierdo
        sem_wait(&forks[right]); // Espera al tenedor derecho

        printf("Filósofo[%d] toma los tenedores (%d, %d)\n", philosopher_id, left, right);
        sleep(rand() % 3); // Tiempo para comer

        // Libera los tenedores (semáforos)
        printf("Filósofo[%d] deja los tenedores (%d, %d)\n", philosopher_id, left, right);
        sem_post(&forks[left]);  // Libera el tenedor izquierdo
        sem_post(&forks[right]); // Libera el tenedor derecho
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[PHILOSOPHER_NUM];
    int ids[PHILOSOPHER_NUM];

    // Inicializar los semáforos (tenedores)
    for (int i = 0; i < PHILOSOPHER_NUM; i++)
    {
        if (sem_init(&forks[i], 0, 1) != 0)
        {
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
    }

    // Crear los hilos para cada filósofo
    for (int i = 0; i < PHILOSOPHER_NUM; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, dinner, &ids[i]);
    }

    // Espera a que los hilos terminen
    for (int i = 0; i < PHILOSOPHER_NUM; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destruir los semáforos
    for (int i = 0; i < PHILOSOPHER_NUM; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}
