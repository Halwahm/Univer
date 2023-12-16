#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void cycle(int countIteration, char* str) {
	for (int i = 0; i < countIteration; i++) {
		sleep(1);
		printf("%s PID: %d-#%d\n", str, getpid(), i);
	}
}

int main() {
	pid_t pid; 
	switch(pid=fork()) {  
		case -1:
			perror("fork");
			exit(1);
		case 0:
			cycle(50, "OS03_05_1");
		default:
			cycle(100, "OS03_05");	
	}
	exit(0);
}
