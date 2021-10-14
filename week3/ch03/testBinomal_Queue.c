#include"Binomal_Queue.h"

int main()
{
	BinQueue B1 = initialize(); 
	BinQueue B2 = initialize();
	insert(12, B1);
	insert(24, B1);
	insert(21, B1);
	insert(65, B1);
	insert(14, B2);
	insert(16, B2);
	insert(26, B2);
	insert(18, B2);
	merge(B1, B2);
	for (int i = 0; i < 8; i++)
	{
		printf("%d\n", DeleteMin(B1));
	}
}
