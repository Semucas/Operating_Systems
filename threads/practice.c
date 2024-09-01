#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

void *acumulado(void *args) // Acumulado: 1, 1+2, 1+2+3, 1+2+3+4, ...
{
    int nro = *(int *)args;
    int temp = 0;
    for (int i = 0; i <= 500; i++)
    {
        temp += i;
        printf("Hilo [%d], acumulada[%d] = %d\n", nro, i, temp);
        usleep(1E6);
    }
}

void *productoria(void *args) // Productoria: 1, 1*2, 1*2*3, 1*2*3*4, ...
{
    int nro = *(int *)args;
    long long int temp = 1;
    int mul = 1;

    for (int i = 0; i <= 500; i++)
    {
        if (i % 20 == 0)
        {
            temp = 1;
            mul = 1;
        }
        temp *= mul;
        mul++;
        printf("Hilo [%d], productoria[%d] = %lld\n", nro, i, temp);
        usleep(1E6);
    }
    return NULL;
}

void *potenciacion(void *args) // 2^n: 2^0, 2^1, 2^2, 2^3, 2^4, ..., 2^500
{
    int nro = *(int *)args;
    long double temp = 0;

    for (int i = 0; i <= 500; i++)
    {
        temp = pow(2, i);
        printf("Hilo [%d], potencia[2^%d] = %.0Lf\n", nro, i, temp);
        usleep(1E6);
    }

    return NULL;
}

void *fibonacci(void *args) // Fibonacci: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...
{
    int nro = *(int *)args;
    double num1 = 0;
    double num2 = 1;

    long double temp = 0;
    for (int i = 0; i <= 500; i++)
    {
        if (i == 0)
        {
            temp;
        }
        else if (i == 1)
        {
            temp = 1;
        }
        else
        {
            temp = num1 + num2;
            num1 = num2;
            num2 = temp;
        }
        printf("Hilo [%d], fibonacci[%d] = %.0Lf\n", nro, i, temp);
        usleep(1E6);
    }
}

int main()
{
    pthread_t thread1, thread2, thread3, thread4;
    int thread_nums[4] = {1, 2, 3, 4};

    printf("Función principal PID: %d\n", getpid());

    pthread_create(&thread1, NULL, acumulado, &thread_nums[0]);
    pthread_create(&thread2, NULL, productoria, &thread_nums[1]);
    pthread_create(&thread3, NULL, potenciacion, &thread_nums[2]);
    pthread_create(&thread4, NULL, fibonacci, &thread_nums[3]);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    return 0;
}