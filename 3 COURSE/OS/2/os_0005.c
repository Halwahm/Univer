#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	for (int a = 1; a <= 1000; a++)
	{
		sleep(2);
		printf("PID: %d-#%d\n", getpid(), a);
	}
	exit(0);
}