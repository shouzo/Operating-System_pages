/* vim: ts=4 sw=4 et
*/
/* The second program is the producer and allows us to enter data for consumers.
 It's very similar to shm1.c and looks like this. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/shm.h>

#include "shm_com.h"

int main()
{
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;
    int rand_arr[10];

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (unsigned int)(long)shared_memory);

    shared_stuff = (struct shared_use_st *)shared_memory;


    /* Initial the array */
    for (int i = 0; i < 10; i++)
        shared_stuff->some_text[i] = 0;
 

    shared_stuff->written_by_you = 1;
    shared_stuff->answer_by_you = 0;


    while (1) {
        while (shared_stuff->written_by_you == 1) {
            sleep(1);            
            printf("Waiting for server...\n");
        }
      

        printf("\n【Server connected】\n");

        /* Generate random number */
        printf("Generate random number\n");
        srand((unsigned)time(NULL));
        for (int i = 0; i < 10; i++) {
            rand_arr[i] = rand() % 100 + 1;
            shared_stuff->some_text[i] = rand_arr[i];
        }
        shared_stuff->written_by_you = 2;


        /* Wait for the sorted array */
        printf("Wait for the sorted array...\n");
        while (shared_stuff->answer_by_you == 0);

        printf("The array (After Sorted)\n");
        for (int i = 0; i < 10; i++) {
            printf("[%d]%d \t", i, shared_stuff->some_text[i]);
        }

        printf("\n");


        shared_stuff->written_by_you = 1;
        shared_stuff->answer_by_you = 0;
        break;
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
