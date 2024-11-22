#include <stdio.h>

// 定义节点结构
define struct node
{
    int data;
    struct node *next;
};

node* createNode(int data)