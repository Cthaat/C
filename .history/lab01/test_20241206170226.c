#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXSIZE 100

typedef struct {
    double data[MAXSIZE];
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
            // ... 处理数字部分，如上所示 ...
            Push(&opnd, num * sign);
            sign = 1;  // 重置符号
        } else if (ch == '-' || ch == '+' || ch == '*' || ch == '/') {
            // 处理运算符
            while (Priority(GetTop(&optr)) >= Priority(ch)) {
                double num2 = Pop(&opnd);
                double num1 = Pop(&opnd);
                char op = Pop(&optr);
                double result = Calculate(num1, num2, op);
                Push(&opnd, result);
            }
            Push(&optr, ch);
        } else if (ch == '(') {
            Push(&optr, ch);
        } else if (ch == ')') {
            while (GetTop(&optr) != '(') {
                double num2 = Pop(&opnd);
                double num1 = Pop(&opnd);
                char op = Pop(&optr);
                double result = Calculate(num1, num2, op);
                Push(&opnd, result);
            }
            Pop(&optr);  // 弹出'('
        } else {
            printf("非法字符: %c\n", ch);
            exit(1);
        }
    }

    // 遇到表达式结束，将剩余的运算符和操作数计算
    while (GetTop(&optr) != '#') {
        double num2 = Pop(&opnd);
        double num1 = Pop(&opnd);
        char op = Pop(&optr);
        double result = Calculate(num1, num2, op);
        Push(&opnd, result);
    }

    return Pop(&opnd);
}

// 计算部分函数
double Calculate(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': 
            if (num2 == 0) {
                printf("除数为零\n");
                exit(1);
            }
            return num1 / num2;
        default:
            printf("不支持的运算符\n");
            exit(1);
    }
}

int main() {
    char exp[MAXSIZE];
    printf("请输入表达式：");
    fgets(exp, MAXSIZE, stdin);
    exp[strcspn(exp, "\n")] = '\0';

    double result = Evaluate(exp);
    printf("结果为：%.2lf\n", result);
    return 0;
}