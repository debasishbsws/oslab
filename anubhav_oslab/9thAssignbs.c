#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "/home/anubhav/anubhav_oslab/" // Define the path to the named pipe

int main() {
    int fd;
    char message[] = "Hello from Process 1!"; // Message to be sent

    // Create the FIFO if it doesn't already exist
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Write the message to the FIFO
    if (write(fd, message, sizeof(message)) == -1) {
        perror("write");
        exit(1);
    }

    // Close the FIFO
    close(fd);

    printf("Process 1 has sent a message to Process 2 via named pipe.\n");

    return 0;
}

