#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = getpid();
    for (int i = 1; i < 100000; i++)
    {
        sleep(1);
        printf("%d - %d\n", i, pid);
    }
    exit(0);
}