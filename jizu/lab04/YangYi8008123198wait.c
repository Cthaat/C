#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, world! (pid: %d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Hello, child! (pid: %d)\n", (int)getpid());
    } else {
        int wc = wait(NULL);
        printf("Hello, parent! (pid: %d) (wc: %d)\n", (int)getpid(), wc);
    }
    return 0;
}