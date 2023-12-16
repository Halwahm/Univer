#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sched.h>

void thread1() {
	pid_t pid = getpid();
	int cnice = nice(0);
	printf("nice %d\n", cnice);
	
	for(int i = 0; i < 1000000000; i++) {
		if(i == 10) {
			cnice = nice(10);
			printf("nice %d\n", cnice);
		}
		printf("OS05_07 main PID %d\n", pid);
		sleep(2);
	}
}

void thread2() {
	pid_t pid = getpid();
	for(int i = 0; i < 1000000000; i++) {
		printf("OS05_07 main PID %d\n", pid);
		sleep(2);
	}
}

int main() {
	pid_t pid;
	switch(pid = fork()) {
		case -1: 
			perror("fork");
			exit(1);
		case 0:
			thread1();
		default:
			thread2();
			wait(NULL);	
	}
}