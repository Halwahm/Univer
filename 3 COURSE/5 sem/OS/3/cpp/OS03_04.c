#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	for (int i = 0; i < 1000; i++) {
		sleep(2);
		printf("PID: %d-#%d\n", getpid(), i);
	}

	exit(0);
}