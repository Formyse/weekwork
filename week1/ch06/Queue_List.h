#pragma once
#include<malloc.h>
#include<stdio.h>
typedef int ElementType;
#ifndef Queue2.h
struct QNode;
struct Node;
typedef QNode *QNodePtr;
typedef Node *PtrToNode;
typedef PtrToNode Queue;

int IsEmpty(Queue Q);                       //判断队列是否为空Q->Rear == Q->Front;
Queue CreateQueue();                         //构造队列
void DisposeQueue(Queue Q);                //删除整个队列，回收空间
void MakeEmpty(Queue Q);                  //释放队列空间，将其置为空
void EnQueue(ElementType X, Queue Q);     //在队列尾端插入元素
ElementType Front(Queue Q);              //取出队头元素，但不删除
void Dequeue(Queue Q);                   //删除队头元素
ElementType FrontAndDequeue(Queue Q);   //
void PrintQueue(Queue Q);               //打印队列

#endif // !Queue2.h

