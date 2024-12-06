#include <stdio.h>
#include <stdlib.h>

#define MAX_DANCER 100

typedef struct {
    // 姓名
    char name[20];
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

void DancerQueueSort (DancerQueue *queue) {
    InitDancerQueue (&MaleQueue);
    InitDancerQueue (&FemaleQueue);
    for (int i = 0; i < queue->front; i++) {
        if (queue->base[i].sex == 'M') {
            AddDancer (&MaleQueue, queue->base[i]);
        }
        else if (queue->base[i].sex == 'F') {
            AddDancer (&FemaleQueue, queue->base[i]);
        }
    }
}

void DancerPartner (DancerQueue *MaleQueue, DancerQueue *FemaleQueue) {
    printf ("开始匹配...\n");
    while (MaleQueue->front > 0 && FemaleQueue->front > 0) {
        Dancer male = RemoveDancer (MaleQueue);
        Dancer female = RemoveDancer (FemaleQueue);
        printf ("%s 和 %s 匹配成功！\n", male.name, female.name);
    }
    if (MaleQueue->front > 0) {
        printf ("首个待匹配的男队选手是 %s!\n", MaleQueue->base[MaleQueue->front - 1].name);
        printf ("男队还有 %d 位选手未匹配！\n", MaleQueue->front);
    }
    if (FemaleQueue->front > 0) {
        printf ("首个待匹配的女队选手是 %s!\n", FemaleQueue->base[FemaleQueue->front - 1].name);
        printf ("女队还有 %d 位选手未匹配！\n", FemaleQueue->front);
    }
    printf ("匹配结束！\n");
}

int main () {
    Dancer A[] = {{"A", 'M'}, {"B", 'M'}, {"C", 'M'}, {"D", 'M'}, {"E", 'M'}, {"F", 'M'}, {"G", 'M'}, {"H", 'M'}, {"I", 'M'}, {"J", 'M'}, {"K", 'F'}, {"L", 'F'}, {"M", 'F'}, {"N", 'F'}, {"O", 'F'}, {"P", 'F'}, {"Q", 'F'}, {"R", 'F'}, {"S", 'F'}, {"T", 'F'}, {"U", 'F'}, {"V", 'F'}, {"W", 'F'}, {"X", 'F'}, {"Y", 'F'}, {"Z", 'F'}};
    DancerQueue AQueue;
    AQueue.base = A;
    AQueue.front = sizeof (A) / sizeof (Dancer);
    AQueue.rare = 0;
    DancerQueueSort (&AQueue);
    DancerPartner (&MaleQueue, &FemaleQueue);
}