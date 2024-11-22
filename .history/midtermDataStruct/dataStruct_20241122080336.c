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
