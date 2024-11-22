#include <stdio.h>

// 定义节点结构
typedef struct node
{
    int data;
    struct node *next;
} node;

node* createNode(int data)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

node* 