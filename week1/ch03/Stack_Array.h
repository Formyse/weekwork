#pragma once

#ifndef Stack.h
struct StackRecord;//定义结构体
typedef struct StackRecord * Stack;//定义指向结构体的栈指针

typedef int ElementType;
int IsEmpty(Stack S);//判断是否为空
int IsFull(Stack S);//判断是否为满
Stack CreateStack(int MaxElements);//创建栈
void DisposeStack(Stack S);
void MakeEmpty(Stack S);//置空
void Push(ElementType X, Stack S);//进栈
ElementType Top(Stack S);//栈顶
void Pop(Stack S);//出栈
ElementType TopAndPop(Stack S);
#endif // !Stack.h
