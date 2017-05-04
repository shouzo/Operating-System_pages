#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 10

void *thread_function(void *arg);
pthread_barrier_t global_barrier;

int main() {
    int res;
    pthread_t a_thread[NUM_THREADS];
    void *thread_result;
    int lots_of_threads;

    pthread_barrier_init(&global_barrier, NULL, NUM_THREADS);

    for(lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads++) {

        res = pthread_create(&(a_thread[lots_of_threads]), NULL, thread_function, (void *)(long)lots_of_threads);
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

    for(lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
        res = pthread_join(a_thread[lots_of_threads], &thread_result);
        if (res != 0) {
            perror("pthread_join failed");
        }
    }

    printf("Thread joined\n");
    pthread_barrier_destroy(&global_barrier);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) { 
    pid_t pid;
    pthread_t tid;
    int n = (long)arg;
    pid = getpid();
    tid = pthread_self();
    printf("Hello!! Thread PID:%u, TID:%u,arg:%d\n",pid,(unsigned int)tid,n);
    pthread_barrier_wait(&global_barrier);
    printf("GoodBye!! Thread PID:%u, TID:%u\n",pid,(unsigned int)tid);

    pthread_exit(0);