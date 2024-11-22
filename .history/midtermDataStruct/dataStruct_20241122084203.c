#include <stdio.h>
#include <stdlib.h>

// 定义节点结构
typedef struct node
{
    int data;
    struct node *next;
} node;

// 创建节点
node* createNode(int data)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 插入节点
node* insert(node *head, int data)
{
    node *newNode = createNode(data);
    if (head == NULL)
    {
        head->next = newNode;
    }
    else
    {
        node *temp = head;
        while (temp->next!= NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return head;
}

// 尾插法
void append(node *head, node *newNode)
{
    if (head->next == NULL)
    {
        head->next = newNode;
    }
    else
    {
        node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 打印链表
void printList(node *head)
{
    node *temp = head->next;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 创建链表
node* createList(int arr[], int size)
{
    node *head = (node*)malloc(sizeof(node));
    head->next = NULL;
    for (int i = 0; i < size; i++)
    {
        node *newNode = createNode(arr[i]);
        append(head, newNode);
    }
    return head;
}

// 分解链表 A 为 B 和 C
void split(node *A, node **B, node **C)
{
    *B = (node*)malloc(sizeof(node));
    *C = (node*)malloc(sizeof(node));
    (*B)->next = NULL;
    (*C)->next = NULL;
    while (A->next != NULL)
    {
        if (A->next->data < 0)
        {
            node *temp = A->next;
            A->next = A->next->next;
            temp->next = NULL;
            append(*B, temp);
        }
        else
        {
            
        }
    }
}

// 主函数
int main()
{
    int n = 0;
    printf("请输入链表长度：");
    scanf("%d", &n);
    int arr[n];
    printf("请输入链表元素：");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    node *head = createList(arr, n);
    printf("原链表：");
    printList(head);
    node *B, *C;
    split(head, &B, &C);
    printf("B链表：");
    printList(B);
    printf("C链表：");
    printList(C);
    return 0;
}