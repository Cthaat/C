#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_b, pid_c, pid_d, pid_e, pid_f;

    // 创建子进程 B
    pid_b = fork();

    if (pid_b == 0) {
        // 子进程 B
        printf("B: PID = %d, PPID = %d\n", getpid(), getppid());

        // 创建子进程 D
        pid_d = fork();

        if (pid_d == 0) {
            // 子进程 D
            printf("D: PID = %d, PPID = %d\n", getpid(), getppid());
        } else if (pid_d > 0) {
            wait(NULL); // 等待子进程 D 结束
        } else {
            perror("fork D failed");
            exit(1);
        }
        exit(0); // 子进程 B 结束
    } else if (pid_b > 0) {
        // 父进程（主进程）
        // 创建子进程 C
        pid_c = fork();

        if (pid_c == 0) {
            // 子进程 C
            printf("C: PID = %d, PPID = %d\n", getpid(), getppid());

            // 创建子进程 E
            pid_e = fork();

            if (pid_e == 0) {
                // 子进程 E
                printf("E: PID = %d, PPID = %d\n", getpid(), getppid());
            } else if (pid_e > 0) {
                // 创建子进程 F
                pid_f = fork();

                if (pid_f == 0) {
                    // 子进程 F
                    printf("F: PID = %d, PPID = %d\n", getpid(), getppid());
                } else if (pid_f > 0) {
                    wait(NULL); // 等待子进程 F 结束
                    wait(NULL); // 等待子进程 E 结束
                } else {
                    perror("fork F failed");
                    exit(1);
                }
            } else {
                perror("fork E failed");
                exit(1);
            }
            exit(0); // 子进程 C 结束
        } else if (pid_c > 0) {
            printf("A: PID = %d\n", getpid());
            wait(NULL); // 等待子进程 B 结束
            wait(NULL); // 等待子进程 C 结束
        } else {
            perror("fork C failed");
            exit(1);
        }
    } else {
        perror("fork B failed");
        exit(1);
    }

    return 0;
}