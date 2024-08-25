#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid, pid1, pid2;
    pid = fork();

    if (pid == 0)
    {
        for (int i = 0, ac = 0; i <= 5; i++)
        {
            ac += i;
            printf("hijo[1] --> pid = %d y ppid = %d i = %d acumulado = %d\n", getpid(), getppid(), i, ac);
        }
        printf("\n");
    }
    else
    {
        wait(NULL);
        pid1 = fork();
        if (pid1 == 0)
        {
            for (int i = 0, ac = 0; i <= 5; i++)
            {
                ac += i;
                printf("hijo[2] --> pid = %d y ppid = %d i = %d acumulado = %d\n", getpid(), getppid(), i, ac);
            }
            printf("\n");
        }
        else
        {
            wait(NULL);
            pid2 = fork();
            if (pid2 == 0)
            {
                for (int i = 0, ac = 0; i <= 5; i++)
                {
                    ac += i;
                    printf("hijo[3] --> pid = %d y ppid = %d i = %d acumulado = %d\n", getpid(), getppid(), i, ac);
                }
                printf("\n");
            }
            else
            {
                wait(NULL);
                for (int i = 0, ac = 0; i <= 5; i++)
                {
                    ac += i;
                    printf("parent --> pid = %d i = %d acumulado = %d\n", getpid(), i, ac);
                }
                printf("\n");
            }
        }
    }
    return 0;
}