#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 1024   // 输入最大长度
#define MAX_ARGS 64          // 最大参数数量

// 分割输入为命令和参数
void parse_input(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " \t\n\r"); // 按空格、制表符、换行分割
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n\r");
    }
    args[i] = NULL; // 参数数组必须以 NULL 结尾
}

// 执行命令
void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) { // 子进程
        execvp(args[0], args);
        // 如果 execvp 失败（如命令不存在）
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // 父进程
        int status;
        waitpid(pid, &status, 0); // 等待子进程结束
    } else {
        perror("fork");
    }
}

// 处理内置命令（如 exit, cd）
int handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 1; // 表示已处理内置命令
    }
    return 0; // 非内置命令
}

int main() {
    char input[MAX_INPUT_LEN];
    char *args[MAX_ARGS];

    while (1) {
        // 打印提示符
        printf("myshell> ");
        fflush(stdout);

        // 读取输入
        if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
            break; // 处理 EOF（如 Ctrl+D）
        }

        // 解析输入
        parse_input(input, args);

        // 处理空输入
        if (args[0] == NULL) {
            continue;
        }

        // 处理内置命令
        if (handle_builtin(args)) {
            continue;
        }

        // 执行外部命令
        execute_command(args);
    }

    return 0;
}