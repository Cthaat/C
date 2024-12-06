#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100

typedef struct {
    double data[MAXSIZE]; // 使用double存储，支持浮点数
    int top;
} SeqStack;

// 初始化栈
void InitStack(SeqStack *S) {
    S->top = -1;
}

// 判断栈空
int IsEmpty(SeqStack *S) {
    return S->top == -1;
}

// 入栈
void Push(SeqStack *S, double x) {
    if (S->top == MAXSIZE - 1) {
        printf("栈满\n");
        exit(1);
    }
    S->data[++S->top] = x;
}

// 出栈
double Pop(SeqStack *S) {
    if (IsEmpty(S)) {
        printf("栈空\n");
        exit(1);
    }
    return S->data[S->top--];
}

// 获取栈顶元素
double GetTop(SeqStack *S) {
    if (IsEmpty(S)) {
        printf("栈空\n");
        exit(1);
    }
    return S->data[S->top];
}

// 判断运算符优先级
int Priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 表达式求值
double Evaluate(char *exp) {
    SeqStack opnd, optr;
    InitStack(&opnd);
    InitStack(&optr);
    Push(&optr, '#');

    int i = 0;
    char ch;
    double num = 0;
    int sign = 1;  // 用于处理负数

    while (exp[i] != '\0') {
        ch = exp[i++];
        // 跳过空格
        while (isspace(ch)) {
            ch = exp[i++];
        }

        if (isdigit(ch) || ch == '.') {  // 操作数
            num = 0;
            while (isdigit(ch) || ch == '.') {
                if (ch == '.') {
                    i++;
                    double decimal = 0.1;
                    while (isdigit(exp[i])) {
                        num += (exp[i++] - '0') * decimal;
                        decimal *= 0.1;
                    }
                    i--;  // 回退一位
                    break;
                }
                num = num * 10 + (ch - '0');
                ch = exp[i++];
            }
            i--;  // 回退一位
            Push(&opnd, num * sign);
            sign = 1;  // 重置符号
        } else if (ch == '-') {
            if (i == 0 || exp[i - 1] == '(') {
                sign = -1;
            } else {
                // 处理减法运算符
                while (Priority(GetTop(&optr)) >= 1) {
                    // ... 计算部分 ...
                }
                Push(&optr, '-');
            }
        } else if (ch == '+') {
            // 处理加法运算符
            while (Priority(GetTop(&optr)) >= 1) {
                // ... 计算部分 ...
            }
            Push(&optr, '+');
        } else if (ch == '*' || ch == '/') {
            // 处理乘除运算符
            while (Priority(GetTop(&optr)) >= 2) {
                // ... 计算部分 ...
            }
            Push(&optr, ch);
        } else if (ch == '(') {
            Push(&optr, ch);
        } else if (ch == ')') {
            while (GetTop(&optr) != '(') {
                // ... 计算部分 ...
            }
            Pop(&optr);  // 弹出'('
        } else {
            printf("非法字符: %c\n", ch);
            exit(1);
        }
    }

    // ... 剩余计算部分 ...

    return Pop(&opnd);
}

// ... 计算部分函数 ...

int main() {
    char exp[MAXSIZE];
    printf("请输入表达式：");
    fgets(exp, MAXSIZE, stdin);
    exp[strcspn(exp, "\n")] = '\0';

    double result = Evaluate(exp);
    printf("结果为：%.2lf\n", result);
    return 0;
}