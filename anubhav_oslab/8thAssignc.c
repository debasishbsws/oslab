#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Add this line

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execlp("ls", "ls", "-l", NULL);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: Waiting for child...\n");
        wait(NULL);
        printf("Parent process: Child process has completed.\n");
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

