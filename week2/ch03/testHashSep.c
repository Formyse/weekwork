#include"HashSep.h"

int main()
{
	HashTable H = InitializeTable(10);
	int i;
	printf("HashTable:\n");
	for (i = 0; i < 10; i++)
	{
		Insert(i * i, H);
		printf("%d:%d\n", i*i, Hash(i * i, 10));
	}
	return 0;
}
