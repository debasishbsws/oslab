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
    char message[100]; // Buffer to store received message

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read the message from the FIFO
    if (read(fd, message, sizeof(message)) == -1) {
        perror("read");
        exit(1);
    }

    // Close the FIFO
    close(fd);

    printf("Process 2 received the following message from Process 1 via named pipe:\n%s\n", message);

    return 0;
}

