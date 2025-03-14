#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello, world! (pid: %d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("I am child process (pid: %d)", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("YangYi8008123198exec.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("exec failed\n");
    } else {
        int wc = wait(NULL);
        printf("I am parent process (pid: %d), child process terminated with status %d\n", (int)getpid(), wc);
    }
    return 0;
}