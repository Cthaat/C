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
    if (head == NULL)
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
    node *temp = A->next;
    while (temp != NULL)
    {
        if (temp->data < 0)
        {
            append(*B, temp);
        }
        else
        {
            append(*C, temp);
        }
        temp = temp->next;
    }
}

// 主函数
int main()
{
    int arr[] = {1, -2, 3, -4, 5, -6};
    int size = sizeof(arr) / sizeof(arr[0]);
    node *head = createList(arr, size);
    printList(head);
    return 0;
}