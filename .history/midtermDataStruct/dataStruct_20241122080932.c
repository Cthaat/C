#include <stdio.h>

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
        head = newNode;
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
node* append(node *head, node *newNode)
{
    if (head == NULL)
    {
        head = newNode;
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
}

// 创建链表
node* createList(int arr[], int size)
{
    node *head = (node*)malloc(sizeof(node));
    node *head = NULL;
    node *tail = head;
    for (int i = 0; i < size; i++)
    {
        node *newNode = createNode(arr[i]);

    }
}
