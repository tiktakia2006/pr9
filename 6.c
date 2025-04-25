#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Home directory files:\n");
    system("ls -l ~");

    printf("\n/usr/bin directory files:\n");
    system("ls -l /usr/bin");

    printf("\n/etc directory files:\n");
    system("ls -l /etc");

    return 0;
}
