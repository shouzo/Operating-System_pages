#include <stdlib.h>
#include <stdio.h>

int main(void) {
	int flag = 0, count = 0;
	
/* Use "fork()" to create Child's process */
	while (flag = fork()) {
		// fork() = -1
		if (flag == -1) {
			printf("fork() = -1, PID = %d\n", getpid());
			printf("Total times = %d\n", count);
			exit(0);
		}
		
		// fork() = 0, Child's entry
		else if (flag == 0) {
			//printf("Child's PID = %d\n", getpid());
			exit(0);
		}

		// fork() > 0, Parent's entry		
		else {
			count++;
			printf("fork() times = %d\n", count);
			//exit(0);
		}
	}
	exit(0);
}
