#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (setuid(0) == -1) {
        perror("setuid");
        exit(1);
    }

    system("cat /etc/shadow");

    return 0;
}
