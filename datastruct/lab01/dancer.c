#include <stdio.h>
#include <stdlib.h>

#define MAX_DANCER 100

// 定义舞者结构体
typedef struct {
    // 姓名
    char name[20];
    // 性别 F 女 M 男
    char sex;
} Dancer;

// 定义舞者队列结构体
typedef struct {
    Dancer *base;
    int front;
    int rare;
} DancerQueue;

// 定义两个舞者队列
DancerQueue MaleQueue, FemaleQueue;

// 初始化舞者队列
void InitDancerQueue (DancerQueue *queue) {
    queue->base = (Dancer *) malloc (MAX_DANCER * sizeof (Dancer));
    queue->front = 0;
    queue->rare = 0;
}

// 添加舞者到队列
void AddDancer (DancerQueue *queue, Dancer dancer) {
    if (queue->front == MAX_DANCER) {
        printf ("队列已满！\n");
        return;
    }
    queue->base[queue->front] = dancer;
    queue->front++;
}

// 从队列中移除舞者
Dancer RemoveDancer (DancerQueue *queue) {
    if (queue->front == 0) {
        printf ("队列为空！\n");
        return;
    }
    Dancer dancer = queue->base[queue->front - 1];
    queue->front--;
    return dancer;
}

// 对舞者队列进行排序
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

// 匹配舞者
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
