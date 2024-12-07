#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;  // 系数
    int exp;    // 指数
    struct Node *next;  // 指向下一个节点的指针
} Node;

Node *create(int coeff, int exp) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->coeff = coeff;
    p->exp = exp;
    p->next = NULL;
    return p;
}

void print(Node *head) {
    Node *p = head;
    while (p) {
        printf("%dx^%d ", p->coeff, p->exp);
        p = p->next;
    }
    printf("\n");
}

void addNode(Node **head, Node *node) {
    if (*head == NULL) {
        *head = node;
    } else {
        Node *p = *head;
        while (p->next) {
            p = p->next;
        }
        p->next = node;
    }
}

Node* addPloy (Node *poly1, Node *poly2) {
    Node *result = NULL;
    Node *p1 = poly1;
    Node *p2 = poly2;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp > p2->exp) {
            addNode(&result, p1);
            p1 = p1->next;
        } else if (p1->exp < p2->exp) {
            addNode(&result, p2);
            p2 = p2->next;
        } else {
            if (p1->coeff + p2->coeff == 0) {
                p1 = p1->next;
                p2 = p2->next;
            } else {
                addNode(&result, create(p1->coeff + p2->coeff, p1->exp));
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    return result;
}
