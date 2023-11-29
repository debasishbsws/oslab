#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process: child\n");
    } else if (pid > 0) {
        printf("Parent process: parent\n");
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}

