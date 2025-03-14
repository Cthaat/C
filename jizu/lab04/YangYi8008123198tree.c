#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, I am A1 (pid: %d)!\n", (int)getpid());
    int rc_b, rc_d;
    rc_b = fork();
    if (rc_b < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_b == 0) {
        printf("Hello, I am B1 (pid: %d)! Parent is A1 (pid: %d)\n", (int)getpid(), (int)getppid());
        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            sleep(2);
            printf("Hello, I am C1 (pid: %d)! Parent is B1 (pid: %d)\n", (int)getpid(), (int)getppid());
        } else {
            wait(NULL);
            printf("Hello, I am B1 (pid: %d)! Parent is A1 (pid: %d)\n", (int)getpid(), (int)getppid());
        }
    } else {
        rc_d = fork();
        if (rc_d < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc_d == 0) {
            sleep(1);
            printf("Hello, I am D1 (pid: %d)! Parent is A1 (pid: %d)\n", (int)getpid(), (int)getppid());
        } else {
            int st;
            waitpid(rc_b, &st, 0);
            waitpid(rc_d, &st, 0);
            printf("Hello, I am A2 (pid: %d)! Parent is the init process (pid: 1)\n", (int)getpid());
        }
    }
    return 0;
}