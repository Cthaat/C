#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct {
    char data[MAXSIZE];
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
void Push(SeqStack *S, char x) {
    if (S->top == MAXSIZE - 1) {
        printf("栈满\n");
        return;
    }
    S->data[++S->top] = x;
}

// 出栈
char Pop(SeqStack *S) {
    if (IsEmpty(S)) {
        printf("栈空\n");
        return '\0';
    }
    return S->data[S->top--];
}

// 获取栈顶元素
char GetTop(SeqStack *S) {
    if (IsEmpty(S)) {
        printf("栈空\n");
        return '\0';
    }
    return S->data[S->top];
}

// 判断运算符优先级，数字越大优先级越高
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
int Evaluate(char *exp) {
    SeqStack opnd, optr; // 操作数栈和运算符栈
    InitStack(&opnd);
    InitStack(&optr);
    Push(&optr, '#'); // 栈底标志
    int i = 0;
    char ch, tmp;
    while (exp[i] != '\0') {
        ch = exp[i++];
        if (ch >= '0' && ch <= '9') { // 操作数
            Push(&opnd, ch - '0');
        } else if (ch == '(') {
            Push(&optr, ch);
        } else if (ch == ')') {
            while (GetTop(&optr) != '(') {
                tmp = Pop(&optr);
                int num2 = Pop(&opnd);
                int num1 = Pop(&opnd);
                switch (tmp) {
                    case '+':
                        Push(&opnd, num1 + num2);
                        break;
                    case '-':
                        Push(&opnd, num1 - num2);
                        break;
                    case '*':
                        Push(&opnd, num1 * num2);
                        break;
                    case '/':
                        Push(&opnd, num1 / num2);
                        break;
                }
            }
            Pop(&optr); // 弹出'('
        } else { // 运算符
            while (Priority(GetTop(&optr)) >= Priority(ch)) {
                tmp = Pop(&optr);
                int num2 = Pop(&opnd);
                int num1 = Pop(&opnd);
                switch (tmp) {
                    case '+':
                        Push(&opnd, num1 + num2);
                        break;
                    case '-':
                        Push(&opnd, num1 - num2);
                        break;
                    case '*':
                        Push(&opnd, num1 * num2);
                        break;
                    case '/':
                        Push(&opnd, num1 / num2);
                        break;
                }
            }
            Push(&optr, ch);
        }
    }
    while (GetTop(&optr) != '#') {
        tmp = Pop(&optr);
        int num2 = Pop(&opnd);
        int num1 = Pop(&opnd);
        switch (tmp) {
            case '+':
                Push(&opnd, num1 + num2);
                break;
            case '-':
                Push(&opnd, num1 - num2);
                break;
            case '*':
                Push(&opnd, num1 * num2);
                break;
            case '/':
                Push(&opnd, num1 / num2);
                break;
        }
    }
    return Pop(&opnd);
}
