#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char * argv[] = {"/bin/ls", "-1", 0};
int main(void) {

	int pid, status;

	if ((pid = fork()) < 0) {
		printf("Fork error \n");
		exit(1);
	}
	
	if (pid == 0) {	/* Child executes here */
		execv (argv[0], argv);
		printf("Exec error \n");
		exit(1);
	} else		/* Parent executes here */
		wait(&status);

	printf("Hello there! \n");
	return 0;
}
