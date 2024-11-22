#include <stdio.h>
#include <stdlib.h>

// 定义链表结点结构
typedef struct Node {
    int data;               // 数据域
    struct Node* next;      // 指针域
} Node;

// 创建链表
Node* createList(int arr[], int size) {
    Node* head = (Node*)malloc(sizeof(Node)); // 创建头结点
    head->next = NULL;
    Node* tail = head; // 尾指针
    for (int i = 0; i < size; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        tail->next = newNode; // 尾插法
        tail = newNode;
    }
    return head;
}

// 打印链表
void printList(Node* head) {
    Node* current = head->next; // 跳过头结点
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 分解链表 A 为 B 和 C
void splitList(Node* A, Node** B, Node** C) {
    *B = (Node*)malloc(sizeof(Node)); // 创建链表 B 的头结点
    (*B)->next = NULL;
    Node* bTail = *B;

    *C = (Node*)malloc(sizeof(Node)); // 创建链表 C 的头结点
    (*C)->next = NULL;
    Node* cTail = *C;

    Node* current = A->next; // 跳过链表 A 的头结点
    while (current) {
        if (current->data < 0) {
            bTail->next = current;
            bTail = current;
        } else if (current->data > 0) {
            cTail->next = current;
            cTail = current;
        }
        current = current->next;
    }

    // 终止链表
    bTail->next = NULL;
    cTail->next = NULL;
}

int main() {
    int arr[] = {3, -5, 8, -2, 7, -6};
    int size = sizeof(arr) / sizeof(arr[0]);

    Node* A = createList(arr, size);
    Node* B = NULL;
    Node* C = NULL;

    printf("原链表 A: ");
    printList(A);

    splitList(A, &B, &C);

    printf("链表 B (值 < 0): ");
    printList(B);

    printf("链表 C (值 > 0): ");
    printList(C);

    return 0;
}
