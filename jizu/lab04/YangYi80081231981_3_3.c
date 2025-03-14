#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Hello, world! (pid: %d)\n", (int)getpid());
    int ra_b, ra_c;
    ra_b = fork();
    if (ra_b < 0) {
        printf(stderr, "fork failed\n");
        exit(1);
    } else if (ra_b == 0) {
        printf("I am child B (pid: %d) and my parent is %d\n", (int)getpid(), (int)getppid());
        int rb_d = fork();
        if (rb_d < 0) {
            printf(stderr, "fork failed\n");
            exit(1);
        } else if (rb_d == 0) {
            printf("I am child D (pid: %d) and my parent is %d\n", (int)getpid(), (int)getppid());
        } else {
            printf("I am parent (pid: %d) and my children are %d and %d\n", (int)getpid(), ra_b, rb_d);
        }
    } else {
        ra_c = fork();
        if (ra_c < 0) {
            printf(stderr, "fork failed\n");
            exit(1);
        } else if (ra_c == 0) {
            printf("I am child C (pid: %d) and my parent is %d\n", (int)getpid(), (int)getppid());
            int rc_e, rc_f;
            rc_e = fork();
            if (rc_e < 0) {
                printf(stderr, "fork failed\n");
                exit(1);
            } else if (rc_e == 0) {
                printf("I am child E (pid: %d) and my parent is %d\n", (int)getpid(), (int)getppid());
            } else {
                rc_f = fork();
                if (rc_f < 0) {
                    printf(stderr, "fork failed\n");
                    exit(1);
                } else if (rc_f == 0) {
                    printf("I am child F (pid: %d) and my parent is %d\n", (int)getpid(), (int)getppid());
                } else {
                    printf("I am parent (pid: %d) and my children are %d and %d\n", (int)getpid(), rc_e, rc_f);
                }
            }
        } else {
            printf("I am parent (pid: %d) and my children are %d and %d\n", (int)getpid(), ra_b, ra_c);
        }
    }
}