#include <stdio.h>

// 定义节点结构
t struct node
{
    int data;
    struct node *next;
};

node* createNode(int data)