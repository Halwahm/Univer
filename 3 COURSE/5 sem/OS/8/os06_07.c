#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("%d\n", getpid());
    int *block;

    block = malloc(256000000);

    printf("%p\n", block);

    for (int i = 0; i < 100000; i++)
    {
        block[i] = i;
    }
    sleep(1000);
}