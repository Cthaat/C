#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// 栈结构
typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 入栈
void push(Stack *s, double x) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("栈满！\n");
        exit(1);
    }
    s->data[++s->top] = x;
}

// 出栈
double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("栈空！\n");
        exit(1);
    }
    return s->data[s->top--];
}

// 判断运算符优先级
int priority(char op) {
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
double evaluate(char *expr) {
    Stack opnd, optr;
    initStack(&opnd);
    initStack(&optr);
    push(&optr, '#');  // 栈底标志

    int i = 0;
    char ch;
    double num;

    while ((ch = expr[i]) != '\0') {
        if (isspace(ch)) {
            i++;
            continue;  // 跳过空格
        } else if (isdigit(ch) || ch == '.') {
            // 扫描数字
            sscanf(expr + i, "%lf", &num);
            push(&opnd, num);
            while (isdigit(expr[i]) || expr[i] == '.') {
                i++;
            }
        } else if (ch == '(') {
            push(&optr, ch);
        } else if (ch == ')') {
            while (peek(&optr) != '(') {
                double b = pop(&opnd);
                double a = pop(&opnd);
                char op = pop(&optr);
                push(&opnd, calculate(a, b, op));
            }
            pop(&optr);  // 弹出'('
        } else {
            while (priority(ch) <= priority(peek(&optr))) {
                double b = pop(&opnd);
                double a = pop(&opnd);
                char op = pop(&optr);
                push(&opnd, calculate(a, b, op));
            }
            push(&optr, ch);
        }
        i++;
    }

    while (peek(&optr) != '#') {
        double b = pop(&opnd);
        double a = pop(&opnd);
        char op = pop(&optr);
        push(&opnd, calculate(a, b, op));
    }

    return pop(&opnd);
}

// 执行运算
double calculate(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                printf("除数为零！\n");
                exit(1);
            }
            return a / b;
        default:
            printf("不支持的运算符！\n");
            exit(1);
    }
}

int main() {
    char expr[100];
    printf("请输入表达式：");
    fgets(expr, sizeof(expr), stdin);
    expr[strlen(expr) - 1] = '\0';  // 去掉末尾的换行符

    double result = evaluate(expr);
    printf("结果为：%.2lf\n", result);

    return 0;
}