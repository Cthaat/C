#include <stdio.h>

#define MAX_DANCER 100

typedef struct {
    // 姓名
    chat name[20];
    // 性别 F 女 M 男
    char sex;
} Dancer;

typedef struct {
    Dancer *base;
    int front;
    int rare;
} DancerQueue;

DancerQueue MaleQueue, FemaleQueue;

void InitDancerQueue (DancerQueue *queue) {
    queue->base = (Dancer *) malloc (MAX_DANCER * sizeof (Dancer));
    queue->front = 0;
    queue->rare = 0;
}

void AddDancer (DancerQueue *queue, Dancer dancer) {
    if (queue->front == MAX_DANCER) {
        printf ("队列已满！\n");
        return;
    }
    queue->base[queue->front] = dancer;
    queue->front++;
}

Dancer RemoveDancer (DancerQueue *queue) {
    if (queue->front == 0) {
        printf ("队列为空！\n");
        return;
    }
    Dancer dancer = queue->base[queue->front - 1];
    queue->front--;
    return dancer;
}

void DancerParnter (Dancer dancer[] , int num) {
    InitDancerQueue (&MaleQueue);
    InitDancerQueue (&FemaleQueue);
    for (int i = 0; i < num; i++) {
        if (dancer[i].sex == 'M') {
            AddDancer (&MaleQueue, dancer[i]);
        }
        else if (dancer[i].sex == 'F') {
            AddDancer (&FemaleQueue, dancer[i]);
        }
    }
}

