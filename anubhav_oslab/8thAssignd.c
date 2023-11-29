#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int signum) {
    printf("Signal received: %d\n", signum);
}

int main() {
    signal(SIGUSR1, handler);

    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        printf("Child process: sending signal to parent...\n");
        kill(getppid(), SIGUSR1);
        sleep(2);
        printf("Child process: exiting.\n");
    } else if (child_pid > 0) {
        // Parent process
        printf("Parent process: waiting for signal...\n");
        int status;
        wait(&status); // Wait for the child process to finish
        printf("Parent process: signal received.\n");
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

