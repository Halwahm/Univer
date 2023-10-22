#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void *thread1(void *arg)
{
    pid_t pid = getpid();
    for (int i = 0; i < 75; i++)
    {
        if (i == 50)
        {
            printf("OS04_08_T1 SLEEP \n");
            sleep(10);
        }
        sleep(1);
        printf("OS04_08_T1 PID: %d-#%d\n", pid, i);
    }
    pthread_exit("Child thread");
}

int main()
{
    pthread_t a_thread;
    void *thread_result;
    pid_t pid = getpid();
    int res = pthread_create(&a_thread, NULL, thread1, NULL);

    for (int i = 0; i < 100; i++)
    {
        if (i == 30)
        {
            printf("Main Thread SLEEP \n");
            sleep(15);
        }
        sleep(1);
        printf("OS04_08 PID:    %d-#%d\n", pid, i);
    }

    int status = pthread_join(a_thread, (void **)&thread_result);
    exit(0);
}
