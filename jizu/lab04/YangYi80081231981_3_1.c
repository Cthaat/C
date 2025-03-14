#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, world (pid: %d)!\n" , (int)getpid());
    int x = 10;
    printf("x = %d\n", x);
    int rc = fork();
    if (rc < 0) {
        printf("fork failed, returning %d\n", rc);
        exit(1);
    } else if (rc == 0) {
        printf("Child: My pid is %d. Parent's pid is %d\n", (int)getpid(), (int)getppid());
        x = 20;
        printf("Child: x = %d\n", x);
    } else {
        printf("Parent: My pid is %d. Child's pid is %d\n", (int)getpid(), rc);
        wait(NULL);
        printf("Parent: Child's x = %d\n", x);
    }
    return 0;
}