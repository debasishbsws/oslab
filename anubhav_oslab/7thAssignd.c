#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(argv[1]);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], entry->d_name);

        struct stat st;
        if (stat(filepath, &st) == 0) {
            printf("Inode: %ld, File: %s\n", st.st_ino, entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}

