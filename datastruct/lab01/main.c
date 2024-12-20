#include "Expression.c" // 引入表达式求值的实现文件
#include "Ploy.c"      // 引入多项式处理的实现文件
#include "dancer.c"    // 引入舞者处理的实现文件

// 处理多项式问题的函数
void PloyQuestion () {
    Node *poly1 = NULL; // 声明第一个多项式链表
    Node *poly2 = NULL; // 声明第二个多项式链表
    
    // 添加多项式1的节点
    addNode(&poly1, create(1, 2)); // 2x^1
    addNode(&poly1, create(2, 1)); // 1x^2
    addNode(&poly1, create(3, 0)); // 0x^3

    // 添加多项式2的节点
    addNode(&poly2, create(2, 2)); // 2x^2
    addNode(&poly2, create(3, 1)); // 1x^3
    addNode(&poly2, create(4, 0)); // 0x^4

    // 计算两个多项式的和
    Node *result = addPloy(poly1, poly2);
    print(result); // 打印结果多项式
}

// 处理表达式问题的函数
void ExpressionQuestion () {
    char exp[MAXSIZE]; // 定义字符数组以存储输入的表达式
    printf("请输入表达式："); // 提示用户输入表达式
    scanf("%s", exp); // 读取用户输入的表达式
    int result = Evaluate(exp); // 调用表达式求值函数
    printf("结果为：%d\n", result); // 输出结果
    return 0; // 结束函数
}

// 处理舞者问题的函数
void DancerQuestion () {
    // 定义舞者数组，分别包含男性和女性舞者
    Dancer A[] = {
        {"A", 'M'}, {"B", 'M'}, {"C", 'M'}, {"D", 'M'},
        {"E", 'M'}, {"F", 'M'}, {"G", 'M'}, {"H", 'M'},
        {"I", 'M'}, {"J", 'M'}, {"K", 'F'}, {"L", 'F'},
        {"M", 'F'}, {"N", 'F'}, {"O", 'F'}, {"P", 'F'},
        {"Q", 'F'}, {"R", 'F'}, {"S", 'F'}, {"T", 'F'},
        {"U", 'F'}, {"V", 'F'}, {"W", 'F'}, {"X", 'F'},
        {"Y", 'F'}, {"Z", 'F'} // 男性舞者用'M'表示，女性舞者用'F'表示
    };

    DancerQueue AQueue; // 定义舞者队列
    AQueue.base = A; // 设置队列的基础指针
    AQueue.front = sizeof(A) / sizeof(Dancer); // 设置队列的前指针
    AQueue.rare = 0; // 设置队列的尾指针

    DancerQueueSort (&AQueue); // 对舞者队列进行排序
    DancerPartner (&MaleQueue, &FemaleQueue); // 找到舞者的伙伴配对
}

// 主函数
int main () {
    printf("Welcome to lab01\n"); // 输出欢迎信息
    int question = 1; // 选项变量，初始为1

    a: // 标签，便于循环返回
    printf("Choose a question:\n1. Ploy\n2. Expression\n3. Dancer\n0. Exit\n"); // 显示菜单
    scanf("%d", &question); // 读取用户选择

    // 根据用户选择执行相应的操作
    switch (question) {
        case 0:
            printf("Exiting...\n"); // 输出退出提示
            return 0; // 退出程序
        case 1:
            PloyQuestion(); // 调用处理多项式的函数
            break;
        case 2:
            ExpressionQuestion(); // 调用处理表达式的函数
            break;
        case 3:
            DancerQuestion(); // 调用处理舞者的函数
            break;
        default:
            printf("Invalid question number\n"); // 提示用户输入无效
            break;
    }
    goto a; // 返回菜单重新选择
}
