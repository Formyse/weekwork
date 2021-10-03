## 1. 单链表

###      1.1 例程

#### 1.`Lish.h`文件

```
#pragma once
#ifndef List.h
struct Node; //定义一个结构体
typedef struct Node *ptrToNode; //定义一个指向结构体的指针
typedef ptrToNode List; //该指针起别名
typedef ptrToNode Position;//起别名

typedef int ElementType;//int类型测试类型，若是其他类型数据，更改即可

List CreateList();//创建链表节点
List MakeEmpty(List L);//将链表清空
int IsEmpty(List L);//判断是否为空
int IsLast(Position P, List L);//判断是否是链表尾部
void PrintList(const List L);//打印链表
Position Find(ElementType X, List L);//查询某值第一次出现的位置
void Delete(ElementType X, List L);//删除某元素
Position FindPrevious(ElementType X, List L);//查询某值的前一节点位置
void Insert(ElementType X, List L, Position P);//插入节点
void DeleteList(List L);//删除链表
Position Header(List L);//头节点
Position First(List L);//第一个节点
Position Advance(Position P);//返回某节点的下一节点
ElementType Data(Position P);//返回该位置的值

#endif // List.h


```

#### 2.`Lish.c`文件

```
#include"List.h"
#include<malloc.h>
#include<stdio.h>

struct Node
{
	ElementType Element;
	Position Next;
};

List CreateList()
{
	List L =(Node *) malloc(sizeof(struct Node));//分配空间
	if (L == NULL)
		printf("out of memory");
	L->Next = NULL;//创建的新节点都会指向空
	return L;
}
List MakeEmpty(List L)
{
	if (L != NULL)//不为空就删除
		DeleteList(L);
	L = (Node*)malloc(sizeof(struct Node));//控制空间分配
	if (L == NULL)
		printf("Out of memory");
	L->Next = NULL;//直到为空
	return L;
}
int IsEmpty(List L)
{
	return L->Next == NULL;//判断链表是否指向空
}
int IsLast(Position P, List L)
{
	return P->Next == NULL;//判断该节点是否指向空
}
void PrintList(const List L)
{
	Position P = Header(L);//指向头节点，从头节点开始

	if (IsEmpty(L))//判断是否为空
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))//不为空，就打印输出
		{
			P = Advance(P);
			printf("%d ", Data(P));
		} 
		printf("\n");
	}


}
Position Find(ElementType X, List L)
{
	Position P;
	P = L->Next;
	while (P != NULL&&P->Element != X)若不为空且值不等于X
	{
		P = P->Next;//指向下一节点
	}
	return P;
}
void Delete(ElementType X, List L)
{
	Position P;
	P = FindPrevious(X, L);//找到前一节点
	if (!IsLast(P, L)) //如果不为最后一个，就删除
	{
		Position TmpCell = P->Next;//利用临时变量来删除
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
Position FindPrevious(ElementType X, List L)
{
	Position P;
	P = L;
	while (P->Next != NULL&&P->Next->Element != X)
		P = P->Next;
	return P;
}
void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;//定义临时变量

	TmpCell = (Node *)malloc(sizeof(struct Node));//分配空间
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element = X;//利用临时变量来插入节点
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
void DeleteList(List L)
{
	Position p;
	p = L->Next;
	L->Next = NULL;
	while (p != NULL) {
		Position tmp;//借助临时变量来删除节点
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
Position Header(List L)
{
	return L;//返回头节点指针
}
Position First(List L)
{
	return L->Next;//返回第一节点指针
}
Position Advance(Position P)
{
	return P->Next;//返回指针
}
ElementType Data(Position P)
{
	return P->Element;//返回数据
}
```

#### 3.`testLish.c`文件

```
#include"List.h"
#include<stdio.h>

int main()
{
	List L;//初始化各项数据
	Position P;
	int i;
	L = MakeEmpty(NULL);
	P = Header(L);
	PrintList(L);//打印

	for (i = 0; i < 10; i++)
	{
		Insert(i, L, P);//插入节点
		PrintList(L);//打印链表
		P = Advance(P);//移动节点
	}
	for (i = 0; i < 10; i += 2)
		Delete(i, L);//删除偶数节点

	for (i = 0; i < 10; i++)
		if ((i % 2 == 0) == (Find(i, L) != NULL))//判断偶节点值是否不为0
			printf("Find fails\n");

	printf("Finished deletions\n");

	PrintList(L);//打印链表

	DeleteList(L);//删除链表
	getchar();
	return 0;

	
}
```

### 1.2 链表游标实现

####   1. `Cursor.h`文件

```
#pragma once
#ifndef Cursor.h
#define SpaceSize 100 //定义数组大小
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;


typedef int ElementType;
void InitializeCursorSpace(void);//初始化游标大小

List MakeEmpty(List L);//置空
int IsEmpty(const List L);//判断是否为空
int IsLast(const Position P, const List L);//判断是否为尾
void PrintList(const List L);//打印链表
Position Find(ElementType X, const List L);//查询位置
void Delete(ElementType X, List L);//删除某值
Position FindPrevious(ElementType X, const List L);//查寻某值的前一节点
void Insert(ElementType X, List L, Position P);//插入节点
void DeleteList(List L);//删除链表
Position Header(const List L);//头节点
Position First(const List L);//第一个节点
Position Advance(const Position P);//移动节点
ElementType Retrieve(const Position P);//返回节点数据

#endif // !Cursor.h

```

#### 2.`Cursor.c`文件

```
#include "cursor.h"
#include<stdio.h>


struct Node//定义结构体
{
	ElementType Element;
	Position    Next;
};


struct Node CursorSpace[SpaceSize];//节点数组来模拟内存分配


static Position CursorAlloc(void)
{
	Position P;

	P = CursorSpace[0].Next;//P初始化为数组第一个元素
	CursorSpace[0].Next = CursorSpace[P].Next;//数组第一个元素为P

	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

void InitializeCursorSpace(void)//用数组来模拟指针
{
	int i;

	for (i = 0; i < SpaceSize; i++)
		CursorSpace[i].Next = i + 1;
	CursorSpace[SpaceSize - 1].Next = 0;
}

List MakeEmpty(List L)//置空操作
{
	if (L != NULL)
		DeleteList(L);
	L = CursorAlloc();
	if (L == 0)
		printf("Out of memory!");
	CursorSpace[L].Next = 0;
	return L;
}

int IsEmpty(List L)//判断是否为空
{
	return CursorSpace[L].Next == 0;
}
int IsLast(Position P, List L)//判断是否为尾
{
	return CursorSpace[P].Next == 0;
}
void PrintList(const List L)//打印链表
{
	Position P = Header(L);

	if (IsEmpty(L))//判断是否为空
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))//若不为空，移动节点，打印数据
		{
			P = Advance(P);
			printf("%d ", Retrieve(P));
		}
		printf("\n");
	}

}
Position Find(ElementType X, List L)//查询某值的位置
{
	Position P;

	P = CursorSpace[L].Next;
    while (P && CursorSpace[P].Element != X)//P不为空且数据不等于X
		   P = CursorSpace[P].Next;//移动到下一节点

    return P;
}
void Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L))  
	{                      
		TmpCell = CursorSpace[P].Next;
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree(TmpCell);
	}
}

Position FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (CursorSpace[P].Next &&
		CursorSpace[CursorSpace[P].Next].Element != X)
	 P = CursorSpace[P].Next;

	return P;
}

void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;

	TmpCell = CursorAlloc();
	if (TmpCell == 0)
		printf("Out of space!!!");

	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
}

void DeleteList(List L)
{
	Position P, Tmp;//定义临时变量

	P = CursorSpace[L].Next;  //P初始化为头节点
	CursorSpace[L].Next = 0;
	while (P != 0)
	{
		 Tmp = CursorSpace[P].Next;//利用临时变量删除节点
		 CursorFree(P);
		 P = Tmp;
	}
}

Position Header(List L)//头节点
{
	return L;
}

Position First(List L)//第一个节点
{
	return CursorSpace[L].Next;
}

Position Advance(Position P)//移动节点
{
	return CursorSpace[P].Next;
}

ElementType Retrieve(Position P)//指向节点数据
{
	return CursorSpace[P].Element;
}
```

#### 3.`testCursor.c`文件

```
#include<stdio.h>
#include"Cursor.h"


int main()
{
	List L;
	Position P;
	int i;

	InitializeCursorSpace();
	L = MakeEmpty(NULL);
	P = Header(L);
	PrintList(L);

	for (i = 0; i < 10; i++)
	{
		Insert(i, L, P);
		PrintList(L);
		P = Advance(P);
	}
	for (i = 0; i < 10; i += 2)
		Delete(i, L);

	for (i = 0; i < 10; i++)
		if ((i % 2 == 0) == (Find(i, L) != NULL))
			printf("Find fails\n");

	printf("Finished deletions\n");

	PrintList(L);

	DeleteList(L);
	getchar();
	return 0;

}
```



## 2.栈

###        2.1 数组实现栈

####       1.`Stack.h`文件

```
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

```

#### 2.`Stack.c`文件

```
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
```

#### 3.`testStack.c`文件

```
#include"Stack.h"
#include<stdio.h>

int main()
{
	Stack S;
	int i;

	S = CreateStack(12);
	for (i = 0; i < 10; i++)
		Push(i, S);

	while (!IsEmpty(S))
	{
		printf("%d\n", Top(S));
		Pop(S);
	}

	DisposeStack(S);
	return 0;

}
```

### 2.2 链表实现栈

#### 1.`Stack.h`文件

```
#pragma once

#ifndef Stack.h
#include <stdio.h>
#include <malloc.h>
 
struct _Node;//定义结构体
typedef struct _Node Node;
typedef Node *PtrToNode;//结构体指针
typedef PtrToNode Stack;

typedef int ElementType;
 
int IsEmpty(Stack S);//判断是否为空
Stack CreateStack();//创建栈
void DisposeStack(Stack S);//摧毁释放栈
void MakeEmpty(Stack S);//置空
void Push(ElementType X, Stack S);//压栈
ElementType Top(Stack S);//返回栈顶数据
void Pop(Stack S);//出栈
#endif // !Stack.h
```

#### 2.`Stack.c`文件

```
#include "Stack.h"

struct _Node//结构体
{
	ElementType Element;
	struct _Node *Next;
};

int IsEmpty(Stack S)//若为NULL即为空
{
	return S->Next == NULL;
}

Stack CreateStack()//创建栈
{
	Stack ret;
	if ((ret = (Stack)malloc(sizeof(Node))) != NULL)//分配空间
	{
		ret->Next = NULL;
		return ret;
	}
	printf("Error! Out of memory! \n");
	return 0;
}

void DisposeStack(Stack S)//定义临时变量释放栈
{
	PtrToNode p = S;
	while (S != NULL)
	{
		S = S->Next;
		free(p);
		p = S;
	}
}

void MakeEmpty(Stack S)//置空
{
	if (S == NULL)
	{
		printf("Error! It's not a Stack!\n");
		return;
	}
	while (!IsEmpty(S))
		Pop(S);
}

void Push(ElementType X, Stack S)//压栈操作
{
	PtrToNode t;
	if ((t = (PtrToNode)malloc(sizeof(Node))) != NULL)
	{
		t->Element = X;
		t->Next = S->Next;
		S->Next = t;
		return;
	}
	printf("Error! Out of memory! \n");
}

ElementType Top(Stack S)
{
	if (S->Next == NULL)
	{
		printf("Error! The stack is empty! \n");
		return 0;
	}
	return S->Next->Element;
}

void Pop(Stack S)
{
	PtrToNode p = S->Next;
	if (p == NULL)
	{
		printf("Error! The stack is empty! \n");
		return;
	}
	S->Next = p->Next;
	free(p);
}
void PrintStack(Stack S)
{
	for (PtrToNode p = S->Next; p; p = p->Next)
	{
		printf("%d ", p->Element);
	}
	printf("\n");
}
```

#### 3.`testStack.c`文件

```
#include"Stack.h"
int main()
{
	Stack s = CreateStack();
	PrintStack(s);
	Pop(s);
	printf("%d\n", Top(s));
	Push(2, s);
	Push(3, s);
	Push(5, s);
	PrintStack(s);
	Pop(s);
	PrintStack(s);
	MakeEmpty(s);
	PrintStack(s);
	DisposeStack(s);
	getchar();
}
```

## 3.队列

###    3.1 数组队列

####         1.`Queue.h`文件

```
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

```

####        2.`Queue.c`文件

```
#include"Queue.h"

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;//数组
};

static int
Succ(int value, Queue Q)
{
	if (++value == Q->Capacity)
		value = 0;
	return value;
}
int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

int IsFull(Queue Q)
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue(int MaxElements)
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QueueRecord));//动态分配内存
	if (Q == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxElements);//动态分配内存
	if (Q->Array == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Capacity = MaxElements;//给域赋值
	MakeEmpty(Q);//置空
	return Q;

	
}

void DisposeQueue(Queue Q)//释放队列
{
	if (Q)
	{
		free(Q->Array);
		free(Q);
	}
}

void MakeEmpty(Queue Q)//置空
{
	Q->Size = 0;//大小为0
	Q->Front = 1;
	Q->Rear = 0;

}

void Enqueue(ElementType X, Queue Q)//入队操作
{
	if (IsFull(Q))//满了
	{
		printf("Queue is full!\n");
		return;
	}
	else
	{
		Q->Size++;//大小+1
		Q->Rear = Succ(Q->Rear, Q);     //Q->Rear = (Q->Rear + 1) % Q->Capacity ? Q->Rear + 1 : 0;
		Q->Array[Q->Rear] = X;//移动队列然后赋值
	}

	
}

ElementType Front(Queue Q)//返回队头数据
{
	if (!IsEmpty(Q))
		return Q->Array[Q->Front];//返回队头数据
	printf("Empty queue");
	return 0;
}

void Dequeue(Queue Q)//出队列
{
	if (!IsEmpty(Q))
	{
		Q->Size--;//大小-1
		Q->Front = Succ(Q->Front, Q);
	}
	else
	{
		printf("Queue is Empty!\n");
	}
	;
}

ElementType FrontAndDequeue(Queue Q)
{
	ElementType X = 0;

	if (IsEmpty(Q))
		printf("Empty queue");
	else
	{
		Q->Size--;
		X = Q->Array[Q->Front];
		Q->Front = Succ(Q->Front, Q);
	}
	return X;


}

```

####      3.`testQueue.c`文件

```
#include"Queue.h"


int main()
{
	int size;
	printf("Please input queue size: ");
	scanf_s("%d", &size,10);
	Queue Q = CreateQueue(size);
	ElementType temp;
	printf("Please input queue elements(seperate by space): ");
	while (!IsFull(Q))
	{
		scanf_s("%d", &temp,10);
		Enqueue(temp, Q);
	}

	printf("Dequeue queue in turn: ");
	while (!IsEmpty(Q))
	{
		printf("%3d\n", FrontAndDequeue(Q));
	}
	printf("\n");
	DisposeQueue(Q);
	return 0;


}
```

### 3.2 链表队列

#### 1.`Queue.h`文件

```
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

```

#### 2.`Queue.c`文件

```
#include"Queue2.h"

struct QNode
{
	ElementType Element;
	QNodePtr Next;
};

struct Node
{
	QNodePtr Front;
	QNodePtr Rear;
};


int IsEmpty(Queue Q)
{
	return Q->Rear == Q->Front;
}

void MakeEmpty(Queue Q)
{
	if (Q == NULL)
	{
		printf("The queue is empty! Must use CreateQueue first!\n");
		return;
	}
	else
	{
		while (!IsEmpty(Q))
			Dequeue(Q);
	}
}

Queue CreateQueue()
{
	//不仅要为对头(Queue)申请空间，还要为队列元素/节点（QNode）申请空间.
	Queue Q;
	Q = (Queue)malloc(sizeof(struct Node));
	if (Q == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Front = Q->Rear = (QNodePtr)malloc(sizeof(struct QNode));

	if (Q->Front == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Front->Next = NULL;
	return Q;
}

void DisposeQueue(Queue Q)
{
	while (Q->Front != NULL)
	{
		Q->Rear = Q->Front->Next;
		free(Q->Front);
		Q->Front = Q->Rear;
	}
}

void Dequeue(Queue Q)
{
	//删除链队列第一个元素
	if (!IsEmpty(Q))
	{
		QNodePtr P;
		P = Q->Front->Next;
		Q->Front->Next = P->Next;
		if (Q->Rear == P)          //判断队列中是否只有一个元素
			Q->Rear = Q->Front;
		free(P);
	}
	else
	{
		printf("The queue is empty!\n");
	}
}

void EnQueue(ElementType X, Queue Q)
{
	QNodePtr P = (QNodePtr)malloc(sizeof(struct QNode));
	if (P == NULL)
	{
		printf("Out of space!\n");
		return;
	}
	else
	{
		P->Next = NULL;
		P->Element = X;
		Q->Rear->Next = P;
		Q->Rear = P;
	}
}

ElementType Front(Queue Q)
{
	return Q->Front->Next->Element;
}

ElementType FrontAndDequeue(Queue Q)
{
	ElementType X = 0;
	if (!IsEmpty(Q))
	{
		X = Front(Q);
		Dequeue(Q);
	}
	else
	{
		printf("The queue is empty!\n");
	}
	return X;
}

void PrintQueue(Queue Q)
{
	QNodePtr P = Q->Front;
	while (P != Q->Rear)
	{
		P = P->Next;
		printf("%d\n", P->Element);
	}

}
```

#### 3.`testQueue.c`文件

```

#include <stdio.h>
#include "Queue2.h"

int main()
{
	Queue Q;
	int i;

	Q = CreateQueue();

	for (i = 0; i < 10; i++)
		EnQueue(i, Q);

	PrintQueue(Q);

	while (!IsEmpty(Q))
	{
		printf("%d\n", Front(Q));
		Dequeue(Q);
	}

	DisposeQueue(Q);
	getchar();
	return 0;
}
```

