#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>  // 添加此行，解决 strlen 的警告

// 定义栈的大小
#define MAX_SIZE 100

// 运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 运算符计算
int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// 栈操作：入栈
void push(int stack[], int *top, int value) {
    stack[++(*top)] = value;
}

// 栈操作：出栈
int pop(int stack[], int *top) {
    return stack[(*top)--];
}

// 运算符栈操作：入栈
void pushOp(char opStack[], int *top, char op) {
    opStack[++(*top)] = op;
}

// 运算符栈操作：出栈
char popOp(char opStack[], int *top) {
    return opStack[(*top)--];
}

// 中缀表达式求值
int evaluateExpression(char* expr) {
    int numStack[MAX_SIZE], opStack[MAX_SIZE];
    int numTop = -1, opTop = -1;
    int i = 0;

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            // 跳过空格
            i++;
            continue;
        }

        // 如果是数字，则入栈
        if (isdigit(expr[i])) {
            int num = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            push(numStack, &numTop, num);
        }
        // 如果是左括号，入栈
        else if (expr[i] == '(') {
            pushOp(opStack, &opTop, expr[i]);
            i++;
        }
        // 如果是右括号，处理括号内的运算
        else if (expr[i] == ')') {
            while (opTop != -1 && opStack[opTop] != '(') {
                int val2 = pop(numStack, &numTop);
                int val1 = pop(numStack, &numTop);
                char op = popOp(opStack, &opTop);
                push(numStack, &numTop, applyOp(val1, val2, op));
            }
            popOp(opStack, &opTop);  // 弹出 '('
            i++;
        }
        // 如果是运算符，处理栈中的运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (opTop != -1 && precedence(opStack[opTop]) >= precedence(expr[i])) {
                int val2 = pop(numStack, &numTop);
                int val1 = pop(numStack, &numTop);
                char op = popOp(opStack, &opTop);
                push(numStack, &numTop, applyOp(val1, val2, op));
            }
            pushOp(opStack, &opTop, expr[i]);
            i++;
        }
    }

    // 处理剩余的运算符
    while (opTop != -1) {
        int val2 = pop(numStack, &numTop);
        int val1 = pop(numStack, &numTop);
        char op = popOp(opStack, &opTop);
        push(numStack, &numTop, applyOp(val1, val2, op));
    }

    // 栈顶就是结果
    return numStack[numTop];
}

int main() {
    char expr[] = "(5 + 3) * 2 - 4 / 2 + 6";  // 示例表达式
    int result = evaluateExpression(expr);
    printf("Result: %d\n", result);  // 输出计算结果
    return 0;
}
