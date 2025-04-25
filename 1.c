#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

int main() {
    FILE *fp;
    char line[MAX_LINE];
    char *user, *uid_str;
    uid_t current_uid = getuid();

    fp = popen("getent passwd", "r");
    if (!fp) exit(1);

    while (fgets(line, sizeof(line), fp)) {
        char *line_copy = strdup(line);
        user = strtok(line, ":");
        strtok(NULL, ":");
        uid_str = strtok(NULL, ":");

        if (user && uid_str) {
            int uid = atoi(uid_str);
            if (uid >= 1000 && uid != current_uid) {
                printf("знайдено іншого звичайного користувача: %s (uid=%d)\n", user, uid);
            }
        }

        free(line_copy);
    }

    pclose(fp);
    return 0;
}
