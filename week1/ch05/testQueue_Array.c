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
