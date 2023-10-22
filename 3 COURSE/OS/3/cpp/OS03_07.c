#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	char* const argv[] = {"ps", "-eF", 0};
	execv("./OS03_05_1", argv); 
	for (int i = 0; i < 100; i++) {
		sleep(1);
		printf("OS03_07 PID: %d-#%d\n", getpid(), i);
	}

	exit(0);
}
