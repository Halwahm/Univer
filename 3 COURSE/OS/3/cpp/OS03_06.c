#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	system("./OS03_05_1");  
	for (int i = 0; i < 100; i++) {
		sleep(1);
		printf("OS03_06 PID: %d-#%d\n", getpid(), i);
	}

	exit(0);
}
