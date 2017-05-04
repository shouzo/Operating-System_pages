#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <time.h>

#define NUM_THREADS 2
#define MSIZE 10000000

static double getDoubleTime();

void *thread_function(void *arg);
pthread_mutex_t work_mutex;
int sum[NUM_THREADS]={0,0};

int main(){
	int res;
	pthread_t a_thread[NUM_THREADS];
	void *thread_result;
	int lots_of_threads;
	//start to measure time...
	double start_time = getDoubleTime();
	//initialize mutex...
	res = pthread_mutex_init(&work_mutex, NULL);
	 if (res != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }
	//pthread_creat...
	for (lots_of_threads = 0; lots_of_threads < NUM_THREADS; lots_of_threads ++){
		res = pthread_create(&(a_thread[lots_of_threads]),NULL,thread_function,(void*)(long)lots_of_threads);
		if(res != 0){
			perror("Thread creation failed");
            exit(EXIT_FAILURE);
		}
	}
	//pthread_join...
	for(lots_of_threads = NUM_THREADS - 1; lots_of_threads >= 0; lots_of_threads--) {
        res = pthread_join(a_thread[lots_of_threads], &thread_result);
        if (res != 0) {
            perror("pthread_join failed");
        }
    }	
	int k,total=0;
	for(k=0;k<NUM_THREADS;k++)
		total += sum[k];
	printf("Total sum = %d\n",total);
	printf("Thread joined\n");
	//stop measuring time...
	double finish_time = getDoubleTime();
	printf("Execute Time:  %.3lf ms\n", (finish_time-start_time));
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
	//pthread_mutex_lock(&work_mutex);
	int my_num = (long )arg;
	//if (MSIZE%NUM_THREADS != 0){	printf("error");pthread_exit(-1); }
	int start_num = (MSIZE/NUM_THREADS)*my_num+1;
	int end_num = (MSIZE/NUM_THREADS)*(my_num+1);
	int i,psum=0;
	for(i=start_num; i <= end_num; i++){
		psum += i;
	}
	sum[my_num] = psum;
	printf("I'm thread[%d] ,start_num:%d,end_num:%d, my_sum = %d\n",my_num,start_num,end_num,sum[my_num]);
	//pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}

static double getDoubleTime() {
        struct timeval tm_tv;
        gettimeofday(&tm_tv,0);
        return (double)(((double)tm_tv.tv_sec*(double)1000.+ (double)(tm_tv.tv_usec))*(double)0.001);
}