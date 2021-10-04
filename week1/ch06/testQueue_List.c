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
