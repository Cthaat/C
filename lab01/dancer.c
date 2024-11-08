#include <stdio.h>

#define MAX_DANCERS 100

typedef struct {
    int first;
    int last;
    char name[MAX_DANCERS];
} Queue;

void initQueue(Queue *q) {
    q->first = 0;
    q->last = 0;
}

Queue getQueue() {
    Queue q;
    initQueue(&q);
    return q;
}