#include"BinHeap.h"


int main()
{
	PirorityQueue H = Initialize(50);
	int ar[] = { 32, 21, 16, 24, 31, 19, 68, 65, 26, 13 };
	int i;
	for (i = 0; i < 10; i++)
		Insert(ar[i], H);
	for (i = 0; i < 10; i++)
	{
		printf("%d\n", DeleteMin(H));

	}
	return 0;
}
