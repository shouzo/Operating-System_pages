#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define NUM_THREADS 5
#define MSIZE 10

static double getDoubleTime();
// void check();

void *thread_function(void *arg);
// srand(time(NULL));
// int a = (rand() % 10) + 1;
int A[MSIZE][MSIZE];
int B[MSIZE][MSIZE];
int C[MSIZE][MSIZE];
int D[MSIZE][MSIZE];

int main(void) {
	int res;
	int i, j;

	srand(time(NULL));
	for (i = 0; i < MSIZE; i++) {
		for (j = 0; j < MSIZE; j++) {
			A[i][j] = 1;    // (rand() % 10) + 1;
			B[i][j] = 2;    // (rand() % 10) + 1;
		}
	}

	pthread_t a_thread[NUM_THREADS];
	void *thread_result;
	int lots_of_threads;

	double start_time = getDoubleTime();

	for (lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads++) {
        res = pthread_create(&(a_thread[lots_of_threads]), NULL, thread_function, (void *)(long)lots_of_threads);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
		// sleep(1);
	}

	printf("Waiting for threads to finish...\n");
	
    for (lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
		res = pthread_join(a_thread[lots_of_threads], &thread_result);
		if (res == 0) {
			printf("Picked up a thread[%d]\n", lots_of_threads);
		}
		else {
			perror("pthread_join failed");
		}
	}

	double finish_time = getDoubleTime();
	printf("All done\n");

	// check();

	printf("Execute Time:  %.3lf ms\n", (finish_time - start_time));
	exit(EXIT_SUCCESS);
}


void *thread_function(void *arg) {
	int my_number = (long)arg;
	int i, j, k;
	printf("Thread Number[%d]\n", my_number); 
	for (i = (MSIZE / NUM_THREADS) * my_number; i < ((MSIZE / NUM_THREADS) * my_number) + (MSIZE / NUM_THREADS); i++) {
		for (j = 0; j < MSIZE; j++) {
            for (k = 0; k < MSIZE; k++)
			    C[i][j] += A[i][k] * B[k][j];
			
            printf("C[%d][%d]:{%d} = A[%d][%d]:{%d} * B[%d][%d]:{%d}\n", i, j, C[i][j], i, j, A[i][j], i, j, B[i][j]);
		}
	}

	pthread_exit(NULL);
}


static double getDoubleTime() {
	struct timeval tm_tv;
	gettimeofday(&tm_tv, 0);
	return (double)(((double)tm_tv.tv_sec * (double)1000. + (double)(tm_tv.tv_usec)) * (double)0.001);
}

/*
void check() {
	int i, j, k;
	int count = 0;

	for (i = 0; i < MSIZE; i++) {
		for (j = 0; j < MSIZE; j++) {
            for (k = 0; k < MSIZE; j++)
			    D[i][j] += A[i][k] * B[k][j];
		}
	}

	for (i = 0; i < MSIZE; i++) {
		for (j = 0; j < MSIZE; j++) {
			if ((D[i][j] - C[i][j]) != 0) {
				count++;
				printf("Error[%d][%d] = [%d]\n", i, j, D[i][j] - C[i][j]);
			}
		}
	}

	printf("Different = [%d]\n", count);
}

*/
