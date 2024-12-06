#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *data;
    int top;
    int size;
} Stack;

void initStack(Stack *s, int size) {
    s->data = (int *)malloc(size * sizeof(int));
    s->top = -1;
    s->size = size;
}

void push(Stack *s, int value) {
    if (s->top < s->size - 1) {
        s->data[++s->top] = value;
    } else {
        printf("Stack overflow\n");
    }
}

int pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[s->top--];
    } else {
        printf("Stack underflow\n");
        return 0;
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[s->top];
    } else {
        printf("Stack is empty\n");
        return 0;
    }
}

int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
        default:
            return -1;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    Stack ops;
    initStack(&ops, strlen(infix));
    int i = 0, j = 0;
    char ch;
    while (infix[i] != '\0') {
        ch = infix[i];
        if (ch == ' ') {
            i++;
            continue;
        }
        if (isdigit(ch) || (ch == '-' && (i == 0 || infix[i-1] == '(' || infix[i-1] == '+' || infix[i-1] == '-' || infix[i-1] == '*' || infix[i-1] == '/' || infix[i-1] == '('))) {
            // 读取完整的数字，包括负数
            while (isdigit(ch) || ch == '-') {
                postfix[j++] = ch;
                ch = infix[++i];
            }
            postfix[j++] = ' '; // 用空格分隔数字
            i--;
        } else if (ch == '(') {
            push(&ops, ch);
            i++;
        } else if (ch == ')') {
            while (!isEmpty(&ops) && peek(&ops) != '(') {
                postfix[j++] = pop(&ops);
            }
            if (!isEmpty(&ops) && peek(&ops) == '(') {
                pop(&ops); // 弹出左括号，不加入后缀表达式
            }
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!isEmpty(&ops) && precedence(peek(&ops)) >= precedence(ch)) {
                postfix[j++] = pop(&ops);
            }
            push(&ops, ch);
            i++;
        } else {
            // 非法字符
            printf("Invalid character: %c\n", ch);
            i++;
        }
    }
    while (!isEmpty(&ops)) {
        postfix[j++] = pop(&ops);
    }
    postfix[j] = '\0';
}

int evaluatePostfix(char *postfix) {
    Stack stack;
    initStack(&stack, strlen(postfix));
    int i = 0;
    int operand1, operand2, result;
    while (postfix[i] != '\0') {
        if (postfix[i] == ' ') {
            i++;
            continue;
        }
        if (isdigit(postfix[i])) {
            // 读取完整的数字
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(&stack, num);
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch(postfix[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        printf("Division by zero error\n");
                        exit(1);
                    }
                    break;
                default:
                    printf("Invalid operator: %c\n", postfix[i]);
                    exit(1);
            }
            push(&stack, result);
            i++;
        } else {
            printf("Invalid character in postfix expression: %c\n", postfix[i]);
            exit(1);
        }
    }
    return pop(&stack);
}

int main() {
    char infix[100];
    char postfix[100];
    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    // 去掉换行符
    infix[strcspn(infix, "\n")] = 0;
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}