#include <stdio.h>
#include <stdlib.h>

#define Free 0 //空虚状态
#define Busy 1 //占用状态
#define OK 1    //内存分配完成
#define ERROR 0 //内存分配出错

typedef int Status;
int flag;

typedef struct freearea //定义一个空闲区说明表结构
{
    long size;   //分区大小
    long address; //分区地址
    int state;    //状态
} ElemType;

//空闲链表存储结构
typedef struct LNode
{
    ElemType data;
    struct LNode *next;  
} LNode, *LinkList;

LinkList block_first,block_last; //头结点

Status alloc(int);   //分配内存
Status free_mem(int); //内存回收
Status First_fit(int); //首次适应算法
Status Best_fit(int);  //最佳适应算法
Status Worst_fit(int); //最差适应算法
void show();          //查看分配
Status Initblock();    //空闲链表初始化

Status Initblock() //头节点指向空闲链表
{
    LNode *p,*q;
	
    block_first = (LinkList)malloc(sizeof(LNode));
    block_last = (LinkList)malloc(sizeof(LNode));
    block_first->next = block_last;
    block_last->next = NULL;
    block_last->data.address = 0;
    block_last->data.size = 40;
    block_last->data.state = Busy;
	
    p = (LNode *)malloc(sizeof(LNode));
    p->data.address = 40;
    p->data.size = 50;
    p->data.state = Free;
    p->next = NULL;
    block_last->next = p;
	
    q = (LNode *)malloc(sizeof(LNode));
    q->data.address = 90;
    q->data.size = 20;
    q->data.state = Busy;
    p->next = q;
    return OK;
}

//分配内存
Status alloc(int ch)
{
    int request = 0;
    printf("请输入需要分配的内存空间大小（单位：KB）：");
    scanf("%d", &request);
    while (request < 0 || request == 0)
    {
        printf("请重新输入需要分配的内存空间大小\n");
        return ERROR;
    }

    if (ch == 2) //选择最佳适应算法
    {
        if (Best_fit(request) == OK)
            printf("分配成功\n");
        else
            printf("内存不足，分配失败\n");
        return OK;
    }
    if (ch == 3) //选择最差适应算法
    {
        if (Worst_fit(request) == OK)
            printf("分配成功\n");
        else
            printf("内存不足，分配失败\n");
        return OK;
    }
    else //默认首次适应算法
    {
        if (First_fit(request) == OK)
            printf("分配成功\n");
        else
            printf("内存不足，分配失败\n");
        return OK;
    }
}

//首次适应算法
Status First_fit(int request)
{
    //为申请作业开辟新空间并初始化
    LinkList temp = (LinkList)malloc(sizeof(LNode));
    temp->data.size = request;
    temp->data.state = Busy;

    LNode *q = block_first;
    LNode *p = block_first->next;
    while (p)
    {
        if (p->data.state == Free && p->data.size == request)
        { //有大小恰好合适的空闲块
            temp->data.address = p->data.address;
            temp->next = p->next;
            q->next = temp;
            free(p);
            return OK;
        }
        if (p->data.state == Free && p->data.size > request)
        { //有空闲块能满足但大于需求
            temp->data.address = p->data.address;
            p->data.address = p->data.address + request;
            p->data.size = p->data.size - request;
            temp->next = p;
            q->next = temp;
            return OK;
        }
        q = p;
        p = p->next;
    }
    return ERROR;
}

//最佳适应算法
Status Best_fit(int request)
{
    LinkList temp = (LinkList)malloc(sizeof(LNode));
    temp->data.size = request;
    temp->data.state = Busy;
    LNode *p = block_first->next;
    LNode *q_prior = block_first;
    LNode *q = NULL; //记录最佳插入位置
    LNode *best_prior = block_first;

    while (p) //初始化最小空间和最佳位置
    {
        if (p->data.state == Free && (p->data.size >= request))
        {
            if (q == NULL)
            {
                q = p;
                best_prior = q_prior;
            }
            else if (q->data.size > p->data.size)
            {
                q = p;
                best_prior = q_prior;
            }
        }
        q_prior = p;
        p = p->next;
    }

    if (q == NULL)
        return ERROR; //没有找到空闲块
    else if (q->data.size == request)
    {
        temp->data.address = q->data.address;
        temp->next = q->next;
        best_prior->next = temp;
        free(q);
    }
    else
    {
        temp->data.address = q->data.address;
        q->data.address = q->data.address + request;
        q->data.size = q->data.size - request;
        temp->next = q;
        best_prior->next = temp;
    }
    return OK;
}
//最差适应算法
Status Worst_fit(int request)
{
    LinkList temp = (LinkList)malloc(sizeof(LNode));
    temp->data.size = request;
    temp->data.state = Busy;
    LNode *p = block_first->next;
    LNode *q = NULL; //记录最佳插入位置
    LNode *worst_prior = block_first;
    LNode *q_prior = block_first;

    while (p) //初始化最大空间和最佳位置
    {
        if (p->data.state == Free && (p->data.size >= request))
        {
            if (q == NULL)
            {
                q = p;
                worst_prior = q_prior;
            }
            else if (p->data.size > q->data.size)
            {
                q = p;
                worst_prior = q_prior;
            }
        }
        q_prior = p;
        p = p->next;
    }

    if (q == NULL)
        return ERROR; //没有找到空闲块
    else if (q->data.size == request)
    {
        temp->data.address = q->data.address;
        temp->next = q->next;
        worst_prior->next = temp;
        free(q);
    }
    else
    {
        temp->data.address = q->data.address;
        q->data.address = q->data.address + request;
        q->data.size = q->data.size - request;
        temp->next = q;
        worst_prior->next = temp;
    }
    return OK;
}

//内存回收
Status free_mem(int flag)
{
    LNode *p = block_first;
    LNode *q = p->next;
    LNode *qn = NULL;
    int i;
    for (i = 0; !q && i  != flag; i++)
	{
		p = q;
		q = q->next;
	}
    if(!q)
    {
            printf("此分区号不存在\n");
            return ERROR;
     }

    if (q->data.state == Free)
    {
        printf("此空间已经回收\n");
        return ERROR;
    }
    q->data.state = Free;
	
	if (q->next != NULL && q->next->data.state == Free) //与后面的空闲块合并
    {
        q->data.size += q->next->data.size;
        qn = q->next;
        q->next = q->next->next;
        free(qn);
        return OK;
    }

      if (p != block_first && p->data.state == Free) //与前面的空闲块合并
    {
        p->data.size += q->data.size;
        p->next = q->next;		
        free(q);
        return OK;
    }	    

    printf("\n未知错误！");
    return ERROR;
}

//显示内存分配情况
void show()
{
    int flag = 0;
    printf("\n内存分配情况:\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n\n");
    LNode *p = block_first->next;
    printf("分区号\t起始地址\t分区大小\t状态\n\n");
    while (p)
    {
        printf("  %d\t", flag++);
        printf("  %ld\t\t", p->data.address);
        printf(" %ldKB\t\t", p->data.size);
        if (p->data.state == Free)
            printf("空闲\n");
        else
            printf("已分配\n");
        p = p->next;
    }
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n\n");
}


int main()
{
    int ch; //分配算法选择
    printf("请输入选择的内存分配算法：\n");
    printf("(1)首次适应算法 (2)最佳适应算法 (3)最差适应算法\n");

    scanf("%d", &ch);
    while (ch < 1 || ch > 3)
    {
        printf("输入有误，请重新输入1-3之间的数据：\n");
        scanf("%d", &ch);
    }

    Initblock(); //空闲链表初始化
    int choice;   //操作选择标记

    while (1)
    {
        show();
        printf("请输入要进行的操作");
        printf("\n1: 分配内存 2: 回收内存 0:退出\n");

        scanf("%d", &choice);
        if (choice == 1)
            alloc(ch); //分配内存
        else if (choice == 2) // 回收内存
        {
            int flag;
            printf("请输入您要释放的分区号");
            scanf("%d", &flag);
            free_mem(flag);
        }
        else if (choice == 0)
            break; //退出
        else //输入数据错误
        {
            printf("输入有误，请重输\n");
            continue;
        }
    }
    return 0;
}
