#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    char *token;
    int status;
    pid_t pid;

    while (1) {
        printf("my_shell> ");
        fflush(stdout); // 确保提示符立即显示

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n"); // 处理EOF (Ctrl+D)
            break;
        }

        // 移除输入中的换行符
        input[strcspn(input, "\n")] = 0;

        // 如果输入为空，则继续下一次循环
        if (input[0] == '\0') {
            continue;
        }

        // 解析输入命令和参数
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // execvp的参数列表必须以NULL结尾

        // 处理内置命令 (例如: exit)
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // 创建子进程
        pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // 子进程
            // 使用execvp执行命令
            execvp(args[0], args);

            // 如果execvp返回，则表示执行失败
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // 父进程
            // 等待子进程结束
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }
        }
    }
}