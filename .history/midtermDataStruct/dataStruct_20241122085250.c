#include <stdio.h>
#include <stdlib.h>

// 定义节点结构
typedef struct node
{
    // 节点数据
    int data;
    // 指向下一个节点
    struct node *next;
} node; // 节点结构体

// 创建节点
node* createNode(int data)
{
    // 申请内存空间
    node *newNode = (node*)malloc(sizeof(node));
    // 初始化节点数据
    newNode->data = data;
    newNode->next = NULL;
    return newNode; // 返回新创建的节点
}

// 插入节点
node* insert(node *head, int data)
{
    // 创建新节点
    node *newNode = createNode(data);
    // 如果链表为空，则直接插入新节点
    if (head == NULL)
    {
        head->next = newNode; // 如果链表为空，直接插入新节点
    }
    // 如果链表不为空，则遍历链表，找到插入位置
    else
    {
        node *temp = head;
        while (temp->next!= NULL)
        {
            temp = temp->next; // 遍历到链表末尾
        }
        temp->next = newNode; // 将新节点插入到链表末尾
    }
    return head; // 返回头节点
}

// 尾插法
void append(node *head, node *newNode)
{
    if (head->next == NULL)
    {
        head->next = newNode; // 如果链表为空，直接插入新节点
    }
    // 如果链表不为空，则遍历链表，找到插入位置
    else
    {
        // 遍历链表，找到链表末尾
        node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next; // 遍历到链表末尾
        }
        temp->next = newNode; // 将新节点插入到链表末尾
    }
}

// 打印链表
void printList(node *head)
{
    // 遍历链表，打印节点数据
    node *temp = head->next;
    // 如果链表为空，则打印空链表
    if (temp == NULL)
    {
        printf("空链表\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%d ", temp->data); // 打印节点数据
        temp = temp->next; // 移动到下一个节点
    }
    printf("\n"); // 打印换行符
}

// 创建链表
node* createList(int arr[], int size)
{
    // 创建头节点
    node *head = (node*)malloc(sizeof(node));
    // 初始化头节点数据
    head->next = NULL;
    // 遍历数组，逐个插入到链表中
    for (int i = 0; i < size; i++)
    {
        node *newNode = createNode(arr[i]);
        append(head, newNode); // 将数组元素逐个插入到链表中
    }
    return head; // 返回头节点
}

// 分解链表 A 为 B 和 C
void split(node *A, node **B, node **C)
{
    // 定义两个空链表
    *B = (node*)malloc(sizeof(node));
    *C = (node*)malloc(sizeof(node));
    // 指向头节点
    (*B)->next = NULL;
    (*C)->next = NULL;
    // 遍历链表 A
    while (A->next != NULL)
    {
        // 如果 A 的下一个节点的数据小于 0，则将该节点插入 B 链表，否则插入 C 链表
        if (A->next->data < 0)
        {
            //
            node *temp = A->next;
            A->next = A->next->next;
            temp->next = NULL;
            append(*B, temp); // 将节点插入到 B 链表中
        }
        else
        {
            node *temp = A->next;
            A->next = A->next->next;
            temp->next = NULL;
            append(*C, temp); // 将节点插入到 C 链表中
        }
    }
}

// 主函数
int main()
{
    int n = 0;
    printf("请输入链表长度：");
    scanf("%d", &n); // 输入链表长度
    int arr[n];
    printf("请输入链表元素：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]); // 输入链表元素
    }
    node *head = createList(arr, n); // 创建链表
    printf("原链表：");
    printList(head); // 打印原链表
    node *B, *C;
    split(head, &B, &C); // 分解链表
    printf("B链表：");
    printList(B); // 打印 B 链表
    printf("C链表：");
    printList(C); // 打印 C 链表
    return 0; // 程序结束
}