#define TIMESLICE	1
#define PROCESS_NO	4
float remaintime[PROCESS_NO] = {6, 3, 1, 7};
int turnaroundtime[PROCESS_NO];
int clock = 0; // global time clock
int pro_num = 0;

int scheduler(void) {
    if (remaintime[pro_num] > TIMESLICE) {
        printf("P[%d] = %d\n", pro_num, remaintime[pro_num]);
        remaintime[pro_num] -= (float)TIMESLICE;
    }

    else if (remaintime[pro_num] == TIMESLICE) {
        break;
    }

    else if (remaintime[pro_num] < TIMESLICE) {
        break;
    }
    

    // select one from the read processes by the round robin algorithm, 
    // and then return the pid of the selected process;
    // if no ready process (i.e., all the processes are finished), then return -1;

    return getpid();
}




int main(void)
{
    pid_t pid;

    pid = scheduler();


    if (pid == -1) {
    
    }


//1. call scheduler() to get the pid of a process,
//
//2. if the pid obtained by step 1 is -1, go to step 7
//
//3. if the remaining time of the selected process is smaller than a time slice
//         add clock by the remaining time of the process
//         store the value of clock as the turnaround time of the process.
//         set the remaining time of the process as zero.
//  endif
//
//4. if the remaining time of the selected process is equal to a time slice
//         add clock by a time slice 
//         store the value of clock as the turnaround time of the process.
//         set the remaining time of the process as zero.
//  endif
//
//5. if the remaining time of the selected process is larger than a time slice
//         add clock by a time slice
//         subtract the remaining time of the process by a time slice
//  endif
//
//6. go to step 1.
//
//7. summate the turnaround time of all the processes
//
//8. calculate the average turnaround time of the processes
           
}
