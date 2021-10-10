#include"HashSep.h"


struct ListNode
{
	ElementType Key;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	List *TheLists;
};
int NextPrime(int N)
{
	if (N % 2 == 0)
		N++;
	int i;
	int NotPrime = 0;
	for (;; N += 2)
	{
		NotPrime = 0;
		for (i = 3; i * i <= N; i += 2)
			if (N % i == 0)
			{
				NotPrime = 1;
				break;
			}
		if (!NotPrime)
			return N;
	}
}
Index Hash(const int Key, int TableSize)
{
	return Key % TableSize;
}
int Same(ElementType e1, ElementType e2)
{
	return e1 == e2;
}
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if ((H = (HashTable)malloc(sizeof(struct HashTbl))) == NULL)
	{
		printf("Error! Out of memory! \n");
		return NULL;
	}
	H->TableSize = NextPrime(TableSize);
	H->TheLists = (Position *)malloc(H->TableSize * sizeof(Position));
	for (i = 0; i < H->TableSize; i++)
	{
		if ((H->TheLists[i] = (List)malloc(sizeof(struct ListNode))) == NULL)
		{
			printf("Error! Out of memory! \n");
			return NULL;
		}
		H->TheLists[i]->Next = NULL;
	}
	return H;
}
void DestroyTable(HashTable H)
{
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		Position p, q;
		q = H->TheLists[i];
		p = q->Next;
		while (p)
		{
			free(q);
			q = p;
			p = p->Next;
		}
	}
	free(H);
}
Position Find(ElementType Key, HashTable H)
{
	Position p;
	p = H->TheLists[Hash(Key, H->TableSize)]->Next;
	while (p)
	{
		if (Same(p->Key, Key))
			break;
		p = p->Next;
	}
	return p;
}
void Insert(ElementType Key, HashTable H)
{
	Position p;
	List L;
	if (Find(Key, H) != NULL)
		return;
	if ((p = (Position)malloc(sizeof(struct ListNode))) == NULL)
	{
		printf("Error! Out of memory! \n");
		return;
	}
	p->Key = Key;
	L = H->TheLists[Hash(Key, H->TableSize)];
	p->Next = L->Next;
	L->Next = p;
}
