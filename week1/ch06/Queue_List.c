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
