/* vim: ts=4 sw=4 et
*/
/* The second program is the producer and allows us to enter data for consumers.
 It's very similar to shm1.c and looks like this. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>

#include "shm_com.h"

int main()
{
    int running = 1;
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

    while (1) {
        while (shared_stuff->written_by_you == 1) {
            sleep(1);            
            printf("waiting for client...\n");
        }
        
        /*
        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
        // fgets(buffer, BUFSIZ, stdin);
        */

        srand((unsigned)time(NULL));
        for (int i = 0; i < 10; i++) {
            rand_arr[i] = rand() % 100 + 1;
            shared_stuff->some_text[i] = rand_arr[i];
            printf("[%d]%d \t", i, rand_arr[i]);
        }
        printf("\n");

        //  strncpy(shared_stuff->some_text, &rand_arr, TEXT_SZ);
        shared_stuff->written_by_you = 1;
        break;
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
