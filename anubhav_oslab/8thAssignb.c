#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process: sleeping...\n");
        sleep(5);
        printf("Child process: exiting.\n");
        exit(0);
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process: waiting for child...\n");
        wait(NULL); // Wait for any child process to exit
        printf("Parent process: exiting.\n");
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

