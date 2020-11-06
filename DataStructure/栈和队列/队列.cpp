#include<iostream>
#define maxSize 10
using namespace std;

//顺序队列定义
typedef struct SeQueue
{
    int data[maxSize];
    int front;//队首指针
    int rear;//队尾指针
}SeQueue;

//链队定义
//队结点定义
typedef struct QNode
{
    int data;//数据域
    struct QNode *next;//指针域
}QNode;

typedef struct LiQueue
{
    QNode *front;//队头指针
    QNode *rear;//队尾指针
}LiQueue;

//顺序队列方法
void initQueue(SeQueue &qu);//初始化顺序队列
int isQueuEmpty(SeQueue qu);//判断队空
int isQueueFull(SeQueue qu);//判断队满
int enQueue(SeQueue &qu, int x);//进队

//链队方法
void initQueue(LiQueue *&lqu); //初始化链队

int main ()
{

}

//初始化队列算法
void initQueue(SeQueue &qu)
{
    qu.front = qu.rear = 0;
}

//判断队空
int isQueuEmpty(SeQueue qu)
{
    if(qu.rear==qu.front)
        return 1;//队空
    else
        return 0;
}

//判断队满
int isQueueFull(SeQueue qu)
{
    if((qu.rear+1)%maxSize==qu.front)
        return 1;
    else
        return 0;
}

//进队
int enQueue(SeQueue &qu,int x)
{
    if((qu.rear+1)%maxSize==qu.front)
        return 0;
    else
    {
        qu.rear = (qu.rear + 1) % maxSize;
        qu.data[qu.rear] = x;
        return 1;
    }
}

//出队
int deQueue(SeQueue &qu,int &x)
{
    if(qu.front==qu.rear)
        return 0;
    else
    {
        qu.front = (qu.front + 1) % maxSize;
        x = qu.data[qu.front];       
        return 1;
    }
}

//初始化链队
void initQueue(LiQueue *&lqu)
{
    lqu = (LiQueue *)malloc(sizeof(LiQueue));
    lqu->front = lqu->rear = NULL;
}