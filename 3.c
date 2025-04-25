#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    char *filename = "testfile.txt";
    char *home = getenv("HOME");
    if (home == NULL) {
        perror("HOME environment variable not set");
        exit(1);
    }
    char copyfile[1024];
    snprintf(copyfile, sizeof(copyfile), "%s/testfile_copy.txt", home);

    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }
    write(fd, "This is a test file.", 20);
    close(fd);
    printf("File %s created successfully.\n", filename);

    if (setuid(0) == -1) {
        perror("setuid");
        exit(1);
    }

    char command[2048];
    snprintf(command, sizeof(command), "cp %s %s", filename, copyfile);
    int ret = system(command);
    if (ret == -1) {
        perror("Error executing cp command");
    } else {
        printf("File copied to %s\n", copyfile);
    }

    if (setuid(getuid()) == -1) {
        perror("setuid back to user");
        exit(1);
    }

    fd = open(copyfile, O_WRONLY);
    if (fd == -1) {
        perror("Error opening copied file for writing");
    } else {
        write(fd, " Adding new content.", 20);
        close(fd);
        printf("Content added to %s\n", copyfile);
    }

    if (remove(copyfile) == -1) {
        perror("Error deleting file");
    } else {
        printf("File %s deleted successfully.\n", copyfile);
    }

    return 0;
}
