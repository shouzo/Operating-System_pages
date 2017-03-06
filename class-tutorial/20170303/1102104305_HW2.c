#include <stdlib.h>
#include <stdio.h>

int main(void) {
/* Press any Integer */
	int n;
	scanf("%d", &n);

/* Use "fork()" to creat Child's and Parent's process */
	int ret = fork();
	int result = n;	// Set the "result" initial value

	if (ret == 0) {	// Child's entry
		printf("\n***** Child's pid = %d *****\n", getpid());
		while (n --> 0)
			result += n;
		printf("1 + 2 + ... + n = %d\n", result);
		exit(0);
	
	} else {	// Parent's entry
		printf("***** Parent's pid = %d *****\n", getpid());
		printf("n 的因數：%d", n);
		while (n --> 1)
			if (result % n == 0)
				printf("\t%d", n);
		exit(0);
	}
}
