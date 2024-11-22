#include <stdio.h>

// 定义节点结构
typedef struct node node;
{
    int data;
    struct node *next;
} node;

node* createNode(int data)