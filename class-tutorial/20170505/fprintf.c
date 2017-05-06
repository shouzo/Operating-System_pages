#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
int main() {

	FILE *fptr, *fptr2;
	int i, j;
	float a, b;
    srand(time(NULL));

	fptr = fopen("ans.txt", "w");

	if (!fptr){
		printf("open error \n");
		exit(1);
	} else {
        printf("open success, start writing into file\n");
    }

	for (i = 1; i <= SIZE; i++) {
        a = ((float)rand() / (float)(RAND_MAX)) * 100;
		printf("[%3d] = %3.3f\n", i, a);
		fprintf(fptr, "%3.3f\n", a);
	}

	fclose(fptr);
	/*---------------------------------------------------------- */
	fptr2 = fopen("ans.txt", "r");

	if(!fptr2) {
		printf("open error\n");
		exit(1);
	} else {
	    printf("open success, start reading from file\n");
	}

	i = 1;
	while (fscanf(fptr2, "%6f" ,&b) == 1)
		printf("[%3d] = %3.3f\n", i++, b);
	
	fclose(fptr2);


	return 0;
}
