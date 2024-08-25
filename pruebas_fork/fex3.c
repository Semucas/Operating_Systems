#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int i;
    pid_t pid;

    pid = fork();

    if (pid < 0)
        printf("fallo del fork\n");
    else if (pid == 0)
        for (i = 0; i < 5; i++)
            printf("hijo[1] --> pid = %d y ppid %d i= %d\n", getpid(), getppid(), i);
    else
        wait(NULL);
    for (i = 0; i < 5; i++)
        printf("rutina del proceso padre valor de i: %d\n\n", i);
}