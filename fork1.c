/* prog1.c  - Demonstrates fork(), wait(), child computing max, parent computing sum */

#include <stdio.h>      
#include <sys/types.h>  // For pid_t (process ID type)
#include <unistd.h>     // For fork(), getpid(), _exit()
#include <sys/wait.h>   // For wait()
#include <stdlib.h>     // For exit(), general utilities

int main(void) {

    int sum = 0;                         
    int i;                               
    int a[] = {10,11,12,13,14,15,16,17,18,19};  
    int max = a[0];                      

    // Create a child process
    pid_t p = fork();

    // Check if fork() failed
    if (p < 0) {
        perror("fork");                  // Print error message if fork fails
        return 1;                        // Exit program with error
    }

    // ----------- CHILD PROCESS (p == 0) -----------
    else if (p == 0) {

        // Child: find maximum value from the array
        for (i = 0; i < 10; i++) {
            if (a[i] > max)
                max = a[i];              // Update max when a larger value is found
        }

        printf("Child: The maximum is: %d\n", max);

        // Terminate child immediately without affecting buffered output of parent
        _exit(0);                        // Always use _exit() inside child
    }

    // ----------- PARENT PROCESS (p > 0) -----------
    else {

        // Parent should wait until child completes (requirement)
        wait(NULL);                      // Stops parent until child finishes

        // Parent now calculates sum of all array elements
        for (i = 0; i < 10; i++) {
            sum += a[i];                 
        }

        printf("Parent: Sum = %d\n", sum);
    }

    return 0;                            
}
