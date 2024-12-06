#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    int data[MAX_LEN];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

Stack getStack() {
    Stack s;
    initStack(&s);
    return s;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    s->top++;
    s->data[s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    int value = s->data[s->top];
    s->top--;
    return value;
}

int get_expression(char* expression) {
    Stack s = getStack();
    for (unsigned int i = 0; i < strlen(expression) - 1; i++) {
        if (expression[i] == ' ') {
            continue;
        }
        char ch = expression[i];
        if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            int value = 0;
            while (s.data[s.top] != '(') {
                if (s.data[s.top] == '+') {
                    value += pop(&s);
                } else if (s.data[s.top] == '-') {
                    value -= pop(&s);
                } else {
                    value = pop(&s);
                }
            }
            push(&s, value);
        } else if (ch == '+' || ch == '-') {
            push(&s, ch);
        } else if (ch == '*' || ch == '/') {
            int value = pop(&s);
            int value2 = pop(&s);
            if (ch == '*') {
                push(&s, value * value2);
            } else {
                push(&s, value / value2);
            }
        } else {
            int value = ch - '0';
            push(&s, value);
        }
    }
    int value = pop(&s);
    while (!isEmpty(&s)) {
        int ch = pop(&s);
        if (ch == '+') {
            value += pop(&s);
        } else {
            value -= pop(&s);
        }
    }
    return value;
}