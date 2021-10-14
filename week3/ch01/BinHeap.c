#include"BinHeap.h"
#define MinData (-32767)
struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};
PirorityQueue Initialize(int MaxElements)
{
	PirorityQueue H;
	H=(HeapStruct*)malloc(sizeof(struct HeapStruct));
	if (H == NULL)
		printf("Out of space");
	H->Elements=(ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
	if (H->Elements == NULL)
		printf("Out of space");
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;

	return H;
}
void Destory(PirorityQueue H)
{
	free(H->Elements);
	free(H);
}
void MakeEmpty(PirorityQueue H)
{
	H->Size = 0;
}
void Insert(ElementType X, PirorityQueue H)
{
	int i;
	if (IsFull(H))
	{
		printf("Pirority is Full");
		return;
	}
	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
	
}
ElementType DeleteMin(PirorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;
	if (IsEmpty(H))
	{
		printf("Pirority Queue is empty");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];
	for (i = 1; i * 2 <= H->Size; i = Child)
	{
		Child = i * 2;
		if (Child != H->Size && H->Elements[Child + 1]
			< H->Elements[Child])
			Child++;

		if (LastElement > H->Elements[Child])
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
ElementType FindMin(PirorityQueue H)
{
	if (!IsEmpty(H))
		return H->Elements[1];
	printf("Priority Queue is Empty");
	return H->Elements[0];
}
int IsFull(PirorityQueue H)
{
	return H->Size == H->Capacity;
}
int IsEmpty(PirorityQueue H)
{
	return H->Size == NULL;
}
