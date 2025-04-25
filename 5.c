#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char filename[] = "tempfile.txt";
    int fd;

    fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }
    write(fd, "This is a temporary file.", 24);
    close(fd);

    if (setuid(0) == -1) {
        perror("setuid");
        exit(1);
    }
    if (chown(filename, 0, 0) == -1) {
        perror("chown");
        exit(1);
    }
    if (chmod(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        perror("chmod");
        exit(1);
    }

    if (setuid(1000) == -1) {
        perror("setuid");
        exit(1);
    }

    if (access(filename, R_OK) == 0)
        printf("Can read the file.\n");
    else
        printf("Cannot read the file.\n");

    if (access(filename, W_OK) == 0)
        printf("Can write to the file.\n");
    else
        printf("Cannot write to the file.\n");

    return 0;
}
