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
