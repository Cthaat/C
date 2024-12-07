#include <stdio.h>
#include <stdlib.h>

// 定义多项式节点结构
typedef struct Node {
    int coeff;  // 系数
    int exp;    // 指数
    struct Node *next;  // 指向下一个节点的指针
} Node;

// 创建一个新的多项式节点并初始化其系数和指数
Node *create(int coeff, int exp) {
    Node *p = (Node *)malloc(sizeof(Node)); // 动态分配内存
    p->coeff = coeff; // 设置节点的系数
    p->exp = exp;     // 设置节点的指数
    p->next = NULL;   // 初始化下一个指针为空
    return p; // 返回新创建的节点
}

// 打印多项式
void print(Node *head) {
    Node *p = head; // 从链表头开始遍历
    while (p) { // 遍历链表
        printf("%dx^%d ", p->coeff, p->exp); // 打印当前节点的系数和指数
        p = p->next; // 移动到下一个节点
    }
    printf("\n"); // 换行
}

// 向多项式链表中添加节点
void addNode(Node **head, Node *node) {
    if (*head == NULL) { // 如果链表为空
        *head = node; // 直接将新节点设置为头节点
    } else {
        Node *p = *head; // 从头节点开始
        while (p->next) { // 遍历到链表的最后一个节点
            p = p->next;
        }
        p->next = node; // 将新节点添加到链表末尾
    }
}

// 合并两个多项式，返回结果多项式
Node* addPloy(Node *poly1, Node *poly2) {
    Node *result = NULL; // 初始化结果链表
    Node *p1 = poly1; // 指向第一个多项式的当前节点
    Node *p2 = poly2; // 指向第二个多项式的当前节点

    // 遍历两个多项式并进行合并
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) { // 如果第一个多项式的指数更大
            addNode(&result, p1); // 将节点添加到结果链表
            p1 = p1->next; // 移动到下一个节点
        } else if (p1->exp < p2->exp) { // 如果第二个多项式的指数更大
            addNode(&result, p2); // 将节点添加到结果链表
            p2 = p2->next; // 移动到下一个节点
        } else { // 如果两个多项式的指数相同
            // 如果合并后的系数为零，则跳过
            if (p1->coeff + p2->coeff == 0) {
                p1 = p1->next; // 移动到下一个节点
                p2 = p2->next; // 移动到下一个节点
            } else {
                // 生成一个新节点并将其添加到结果链表
                addNode(&result, create(p1->coeff + p2->coeff, p1->exp));
                p1 = p1->next; // 移动到下一个节点
                p2 = p2->next; // 移动到下一个节点
            }
        }
    }
    return result; // 返回合并后的多项式链表
}
