#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


// When the process get the "Ctrl+C" signal.
void show_time() {
    system("date"); // show the time
}

// When the process get the "Ctrl+\" signal.
void go_default() {
    signal(SIGINT, SIG_DFL);    // recover "Ctrl+C"
}


int main(void) {

    signal(SIGINT, show_time);  // triggering "Ctrl+C"
    signal(SIGQUIT, go_default);// triggering "Ctrl+\"

    while(1) {
        printf("What time is it？\n");  // Something interesting will happen if this line without "\n".
        sleep(1);
    }   
}
