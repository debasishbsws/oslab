#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>

#define SHM_SIZE 1024

int main() {
    // Provide a valid path to an existing file
    const char *file_path = "/home/anubhav/anubhav_oslab/employee.txt";

    key_t key = ftok(file_path, 1);
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }

    strcpy(data, "Hello, shared memory!");

    printf("Data written to shared memory: %s\n", data);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

