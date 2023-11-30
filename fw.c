#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        printf("Child process created! PID: %d\n", getpid());
        sleep(3);
        printf("Child process done!\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Parent process, Parent PID: %d\n", getpid());
        printf("Waiting for child process to finish...\n");
        wait(NULL);
        printf("Child process has finished\n");
    }

    return 0;
}

