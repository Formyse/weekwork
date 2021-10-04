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

