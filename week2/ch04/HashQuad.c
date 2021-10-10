#include "HashQuad.h"

enum KindOfEntry
{
	Legitimate,
	Empty,
	Deleted
};

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

struct HashTbl
{
	int TableSize;
	Cell *TheCells;
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


Index Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if ((H = (HashTable)malloc(sizeof(struct HashTbl))) == NULL)
	{
		printf("Error!\n");
		return NULL;
	}
	H->TableSize = NextPrime(TableSize);
	if ((H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize)) == NULL)
	{
		printf("Error!\n");
		return NULL;
	}
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;
	return H;

}

void DestroyTable(HashTable H)
{
	free(H->TheCells);
	free(H);
}

Position Find(ElementType Key, HashTable H)
{
	Index id = Hash(Key, H->TableSize);
	int i = 0;
	while (H->TheCells[id].Info != Empty && H->TheCells[id].Element != Key)
	{
		id += 2*++i - 1;
		if (id >= H->TableSize)
			id -= H->TableSize;
	}
	return id;
}

void Insert(ElementType Key, HashTable H)
{
	Position p = Find(Key, H);
	if (H->TheCells[p].Info != Legitimate)
	{
		H->TheCells[p].Element = Key;
		H->TheCells[p].Info = Legitimate;
	}
}

ElementType Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].Element;
}

HashTable ReHash(HashTable H)
{
	int i;
	int OldSize;
	Cell *OldCells;
	OldCells = H->TheCells;
	OldSize = H->TableSize;
	H = InitializeTable(2 * OldSize);
	for (i = 0; i < H->TableSize; i++)
		if (OldCells[i].Info == Legitimate)
			Insert(OldCells[i].Element, H);
	free(OldCells);
	return H;
}
