#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100 // 定义栈的最大容量

// 定义顺序栈结构
typedef struct {
    char data[MAXSIZE]; // 栈数据
    int top; // 栈顶指针，初始为-1表示栈空
} SeqStack;

// 初始化栈
void InitStack(SeqStack *S) {
    S->top = -1; // 设置栈顶指针为-1
}

// 判断栈空
int IsEmpty(SeqStack *S) {
    return S->top == -1; // 如果栈顶指针为-1，则栈为空
}

// 入栈
void Push(SeqStack *S, char x) {
    if (S->top == MAXSIZE - 1) { // 检查栈是否满
        printf("栈满\n"); // 输出栈满提示
        return;
    }
    S->data[++S->top] = x; // 将元素入栈，并更新栈顶指针
}

// 出栈
char Pop(SeqStack *S) {
    if (IsEmpty(S)) { // 检查栈是否空
        printf("栈空\n"); // 输出栈空提示
        return '\0'; // 返回空字符表示出栈失败
    }
    return S->data[S->top--]; // 返回栈顶元素并更新栈顶指针
}

// 获取栈顶元素
char GetTop(SeqStack *S) {
    if (IsEmpty(S)) { // 检查栈是否空
        printf("栈空\n"); // 输出栈空提示
        return '\0'; // 返回空字符表示获取失败
    }
    return S->data[S->top]; // 返回栈顶元素
}

// 判断运算符优先级，数字越大优先级越高
int Priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1; // 加法和减法优先级为1
        case '*':
        case '/':
            return 2; // 乘法和除法优先级为2
        default:
            return 0; // 非运算符的优先级为0
    }
}

// 表达式求值
int Evaluate(char *exp) {
    SeqStack opnd, optr; // 定义操作数栈和运算符栈
    InitStack(&opnd); // 初始化操作数栈
    InitStack(&optr); // 初始化运算符栈
    Push(&optr, '#'); // 将一个标志符号'#'入栈作为栈底标志
    int i = 0; // 字符串索引
    char ch, tmp; // 当前字符和临时字符

    while (exp[i] != '\0') { // 遍历输入表达式
        ch = exp[i++]; // 获得当前字符并递增索引
        if (ch >= '0' && ch <= '9') { // 如果是操作数
            Push(&opnd, ch - '0'); // 将字符转换为数字并入栈
        } else if (ch == '(') { // 如果是左括号
            Push(&optr, ch); // 入运算符栈
        } else if (ch == ')') { // 如果是右括号
            while (GetTop(&optr) != '(') { // 直到遇到左括号
                tmp = Pop(&optr); // 弹出运算符
                int num2 = Pop(&opnd); // 弹出第二个操作数
                int num1 = Pop(&opnd); // 弹出第一个操作数
                // 根据运算符进行相应的操作并将结果入栈
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
        } else { // 如果是运算符
            while (Priority(GetTop(&optr)) >= Priority(ch)) { // 处理运算符优先级
                tmp = Pop(&optr); // 弹出运算符
                int num2 = Pop(&opnd); // 弹出第二个操作数
                int num1 = Pop(&opnd); // 弹出第一个操作数
                // 根据运算符进行相应的操作并将结果入栈
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
            Push(&optr, ch); // 将当前运算符入栈
        }
    }
    // 处理剩余的运算符
    while (GetTop(&optr) != '#') {
        tmp = Pop(&optr); // 弹出运算符
        int num2 = Pop(&opnd); // 弹出第二个操作数
        int num1 = Pop(&opnd); // 弹出第一个操作数
        // 根据运算符进行相应的操作并将结果入栈
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
    return Pop(&opnd); // 返回最终结果
}
