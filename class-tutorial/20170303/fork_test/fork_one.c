#include <stdlib.h>
#include <stdio.h>

int main(void) {
	
/* Use "fork()" to create Child's process */
	fork();	
	printf("PID = %d\n", getpid());

	exit(0);
}
