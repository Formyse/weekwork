## 1. 单链表

###      1.1 例程

#### 1.`Lish.h`文件

```
#pragma once
#ifndef List.h
struct Node;
typedef struct Node *ptrToNode;
typedef ptrToNode List;
typedef ptrToNode Position;

typedef int ElementType;

List CreateList();
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void PrintList(const List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Data(Position P);

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
	List L =(Node *) malloc(sizeof(struct Node));
	if (L == NULL)
		printf("out of memory");
	L->Next = NULL;
	return L;
}
List MakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = (Node*)malloc(sizeof(struct Node));
	if (L == NULL)
		printf("Out of memory");
	L->Next = NULL;
	return L;
}
int IsEmpty(List L)
{
	return L->Next == NULL;
}
int IsLast(Position P, List L)
{
	return P->Next == NULL;
}
void PrintList(const List L)
{
	Position P = Header(L);

	if (IsEmpty(L))
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))
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
	while (P != NULL&&P->Element != X)
	{
		P = P->Next;
	}
	return P;
}
void Delete(ElementType X, List L)
{
	Position P;
	P = FindPrevious(X, L);
	if (!IsLast(P, L)) {
		Position TmpCell = P->Next;
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
	Position TmpCell;

	TmpCell = (Node *)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
void DeleteList(List L)
{
	Position p;
	p = L->Next;
	L->Next = NULL;
	while (p != NULL) {
		Position tmp;
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
Position Header(List L)
{
	return L;
}
Position First(List L)
{
	return L->Next;
}
Position Advance(Position P)
{
	return P->Next;
}
ElementType Data(Position P)
{
	return P->Element;
}
```

#### 3.`testLish.c`文件

```
#include"List.h"
#include<stdio.h>

int main()
{
	List L;
	Position P;
	int i;
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

### 1.2 链表游标实现

####   1. `Cursor.h`文件

```
#pragma once
#ifndef Cursor.h
#define SpaceSize 100
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;


typedef int ElementType;
void InitializeCursorSpace(void);

List MakeEmpty(List L);
int IsEmpty(const List L);
int IsLast(const Position P, const List L);
void PrintList(const List L);
Position Find(ElementType X, const List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, const List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(const List L);
Position First(const List L);
Position Advance(const Position P);
ElementType Retrieve(const Position P);

#endif // !Cursor.h

```

#### 2.`Cursor.c`文件

```
#include "cursor.h"
#include<stdio.h>


struct Node
{
	ElementType Element;
	Position    Next;
};


struct Node CursorSpace[SpaceSize];


static Position CursorAlloc(void)
{
	Position P;

	P = CursorSpace[0].Next;
	CursorSpace[0].Next = CursorSpace[P].Next;

	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

void InitializeCursorSpace(void)
{
	int i;

	for (i = 0; i < SpaceSize; i++)
		CursorSpace[i].Next = i + 1;
	CursorSpace[SpaceSize - 1].Next = 0;
}

List MakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = CursorAlloc();
	if (L == 0)
		printf("Out of memory!");
	CursorSpace[L].Next = 0;
	return L;
}

int IsEmpty(List L)
{
	return CursorSpace[L].Next == 0;
}
int IsLast(Position P, List L)
{
	return CursorSpace[P].Next == 0;
}
void PrintList(const List L)
{
	Position P = Header(L);

	if (IsEmpty(L))
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))
		{
			P = Advance(P);
			printf("%d ", Retrieve(P));
		}
		printf("\n");
	}

}
Position Find(ElementType X, List L)
{
	Position P;

	P = CursorSpace[L].Next;
    while (P && CursorSpace[P].Element != X)
		   P = CursorSpace[P].Next;

    return P;
}
void Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L))  /* Assumption of header use */
	{                      /* X is found; delete it */
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
	Position P, Tmp;

	P = CursorSpace[L].Next;  
	CursorSpace[L].Next = 0;
	while (P != 0)
	{
		 Tmp = CursorSpace[P].Next;
		 CursorFree(P);
		 P = Tmp;
	}
}

Position Header(List L)
{
	return L;
}

Position First(List L)
{
	return CursorSpace[L].Next;
}

Position Advance(Position P)
{
	return CursorSpace[P].Next;
}

ElementType Retrieve(Position P)
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
struct StackRecord;
typedef struct StackRecord * Stack;

typedef int ElementType;
int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);
#endif // !Stack.h

```

#### 2.`Stack.c`文件

```
#include"Stack.h"
#include<stdio.h>
#include<malloc.h>

struct StackRecord {
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};
int IsEmpty(Stack S)
{
	return S->TopOfStack == -1;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements)
{
	Stack ret;
	if ((ret = (Stack)malloc(sizeof(struct StackRecord))) != NULL)
	{
		ret->TopOfStack = -1;
		ret->Capacity = MaxElements;
		if ((ret->Array = (ElementType*)malloc(MaxElements * sizeof(ElementType))) != NULL)
			return ret;
		free(ret);
	}
	printf("Error! Out of memory! \n");
	return NULL;
}

void DisposeStack(Stack S)
{
	if (S != NULL)
	{
		free(S->Array);
		free(S);
	}
}

void MakeEmpty(Stack S)
{
	S->TopOfStack = -1;
}

void Push(ElementType X, Stack S)
{
	if (IsFull(S))
	{
		printf("Error! The stack is full! \n");
		return;
	}
	(S->Array)[++(S->TopOfStack)] = X;
}

ElementType Top(Stack S)
{
	if (IsEmpty(S))
	{
		printf("Error! The stack is empty! \n");
		return 0;
	}
	return (S->Array)[(S->TopOfStack)];
}

void Pop(Stack S)
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
	return (S->Array)[(S->TopOfStack)--];
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
 
struct _Node;
typedef struct _Node Node;
typedef Node *PtrToNode;
typedef PtrToNode Stack;

typedef int ElementType;
 
int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
#endif // !Stack.h
```

#### 2.`Stack.c`文件

```
#include "Stack.h"

struct _Node
{
	ElementType Element;
	struct _Node *Next;
};

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

Stack CreateStack()
{
	Stack ret;
	if ((ret = (Stack)malloc(sizeof(Node))) != NULL)
	{
		ret->Next = NULL;
		return ret;
	}
	printf("Error! Out of memory! \n");
	return 0;
}

void DisposeStack(Stack S)
{
	PtrToNode p = S;
	while (S != NULL)
	{
		S = S->Next;
		free(p);
		p = S;
	}
}

void MakeEmpty(Stack S)
{
	if (S == NULL)
	{
		printf("Error! It's not a Stack!\n");
		return;
	}
	while (!IsEmpty(S))
		Pop(S);
}

void Push(ElementType X, Stack S)
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

struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;
int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);
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
	ElementType *Array;
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
	Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (Q == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxElements);
	if (Q->Array == NULL)
	{
		printf("Out of space!\n");
		return NULL;
	}
	Q->Capacity = MaxElements;
	MakeEmpty(Q);
	return Q;

	
}

void DisposeQueue(Queue Q)
{
	if (Q)
	{
		free(Q->Array);
		free(Q);
	}
}

void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;

}

void Enqueue(ElementType X, Queue Q)
{
	if (IsFull(Q))
	{
		printf("Queue is full!\n");
		return;
	}
	else
	{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);     //Q->Rear = (Q->Rear + 1) % Q->Capacity ? Q->Rear + 1 : 0;
		Q->Array[Q->Rear] = X;
	}

	
}

ElementType Front(Queue Q)
{
	if (!IsEmpty(Q))
		return Q->Array[Q->Front];
	printf("Empty queue");
	return 0;
}

void Dequeue(Queue Q)
{
	if (!IsEmpty(Q))
	{
		Q->Size--;
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

