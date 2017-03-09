#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int flag = 0;
	
/* Use "fork()" to create Child's process */
	while(1) {
		flag = fork();

		if (flag == -1) {
			printf("fork() = -1, PID = %d\n", getpid());
			exit(0);
		}
		else if (flag == 0) {
			printf("Child's PID = %d\n", getpid());
		}
		else if (flag != 0) {
			printf("Parent's PID = %d\n", getpid());
			wait(0);
			break;
		}
	}
	exit(0);
}
