/* prog2.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
    printf("The process Id: %d\n", getpid());

    pid_t p = fork();
    if (p < 0) {
        perror("fork failed");
        return 1;
    }
    else if (p == 0) {
        // child
        printf("It is in the child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Call test1 from child\n");
        char *argv[] = {"./test1.out", NULL};
        execv(argv[0], argv);
        // execv returns only on error
        perror("execv failed");
        _exit(errno);
    }
    else {
        // parent
        printf("It is the parent process (parent PID: %d)\n", getpid());
        wait(NULL); // optional: wait for child
    }
    return 0;
}
