#include"Stack.h"
#include<stdio.h>
#include<malloc.h>

struct StackRecord {
	int Capacity;//域
	int TopOfStack;//栈顶
	ElementType *Array;//数组
};
int IsEmpty(Stack S)//判断是否为空
{
	return S->TopOfStack == -1;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity - 1;//判断是否为满
}

Stack CreateStack(int MaxElements)
{
	Stack ret;
	if ((ret = (Stack)malloc(sizeof(struct StackRecord))) != NULL)//分配内存
	{
		ret->TopOfStack = -1;//栈顶置-1
		ret->Capacity = MaxElements;//域 为最大
		if ((ret->Array = (ElementType*)malloc(MaxElements * sizeof(ElementType))) != NULL)
			return ret;
		free(ret);//释放
	}
	printf("Error! Out of memory! \n");
	return NULL;
}

void DisposeStack(Stack S)
{
	if (S != NULL)//若不为0，释放空间
	{
		free(S->Array);
		free(S);
	}
}

void MakeEmpty(Stack S)//置空
{
	S->TopOfStack = -1;
}

void Push(ElementType X, Stack S)//让某值进栈压栈
{
	if (IsFull(S))//若满了，抛出错误
	{
		printf("Error! The stack is full! \n");
		return;
	}
	(S->Array)[++(S->TopOfStack)] = X;否则，栈顶为该值
}

ElementType Top(Stack S)//返回栈顶数据
{
	if (IsEmpty(S))
	{
		printf("Error! The stack is empty! \n");
		return 0;
	}
	return (S->Array)[(S->TopOfStack)];
}

void Pop(Stack S)//出栈
{
	if (IsEmpty(S))
	{
		printf("Error! The stack is empty! \n");
		return;
	}
	S->TopOfStack -= 1;
}

ElementType TopAndPop(Stack S)
{
	if (IsEmpty(S))
	{
		printf("Error! The stack is empty! \n");
		return 0;
	}
	return (S->Array)[(S->TopOfStack)--];返回栈数据
}
