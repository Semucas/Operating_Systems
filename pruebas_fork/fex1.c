#include <stdio.h>

int main()
{
    fork();
    printf("Hi Operating Systems \n Process_ID: %d\n", getpid());
    while (1)
        ;
    return 0;
}