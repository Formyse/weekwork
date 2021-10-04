#pragma once
#ifndef Queue.h
#include <stdio.h>
#include<malloc.h>

struct QueueRecord;//定义结构体
typedef struct QueueRecord *Queue;//定义结构体指针
typedef int ElementType;
int IsEmpty(Queue Q);//判断是否为空
int IsFull(Queue Q);//判断是否为满
Queue CreateQueue(int MaxElements);//创建队列
void DisposeQueue(Queue Q);//释放队列
void MakeEmpty(Queue Q);//置空
void Enqueue(ElementType X, Queue Q);//入队操作
ElementType Front(Queue Q);//返回头元素
void Dequeue(Queue Q);//出队操作
ElementType FrontAndDequeue(Queue Q);//数据全部出队
#endif // !Queue.h

