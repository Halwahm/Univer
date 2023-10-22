#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    for (int i = 0; i < 100; i++)
    {
        printf("PID: %d-#%d\n", getpid(), i);
        sleep(1);
    }
}
