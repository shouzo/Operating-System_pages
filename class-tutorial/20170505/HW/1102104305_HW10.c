#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100
int main() {

	FILE *fptr1, *fptr2;
	int i;
	float a = .0, total = .0, avg = .0;
    float sigma = .0, sd = .0;


    /* Use fptr1 to calculate total and average */
    fptr1 = fopen("ans.txt", "r");
	if (!fptr1) {
		printf("open error\n");
		exit(1);
	} 
    
    else {
	    printf("\nopen success, fptr1 starts reading from file\n");
	}


    i = 1;
    while (fscanf(fptr1, "%6f" ,&a) == 1) {
		printf("[%3d] = %3.3f\n", i++, a);
        total += a;
    }
	avg = (total / i);
    fclose(fptr1);




    /* Use fptr2 to calculate standard deviation */
    fptr2 = fopen("ans.txt", "r");
    if (!fptr2) {
		printf("open error\n");
		exit(1);
	} 
    
    else {
	    printf("\nopen success, fptr2 starts reading from file\n");
	}


    i = 1;
    while (fscanf(fptr2, "%6f" ,&a) == 1) {
        sigma += (a - avg) * (a - avg);
        i++;
    }
    sd = sqrt(sigma / i); 
    fclose(fptr2);




    /* Output */
    printf("\n\nThe average = %f\n", avg);
    printf("The standard deviation = %f\n", sd);


	return 0;
}
