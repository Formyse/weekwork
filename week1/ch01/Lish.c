#include"List.h"
#include<malloc.h>
#include<stdio.h>

struct Node
{
	ElementType Element;
	Position Next;
};

List CreateList()
{
	List L =(Node *) malloc(sizeof(struct Node));
	if (L == NULL)
		printf("out of memory");
	L->Next = NULL;
	return L;
}
List MakeEmpty(List L)
{
	if (L != NULL)
		DeleteList(L);
	L = (Node*)malloc(sizeof(struct Node));
	if (L == NULL)
		printf("Out of memory");
	L->Next = NULL;
	return L;
}
int IsEmpty(List L)
{
	return L->Next == NULL;
}
int IsLast(Position P, List L)
{
	return P->Next == NULL;
}
void PrintList(const List L)
{
	Position P = Header(L);

	if (IsEmpty(L))
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))
		{
			P = Advance(P);
			printf("%d ", Data(P));
		} 
		printf("\n");
	}


}
Position Find(ElementType X, List L)
{
	Position P;
	P = L->Next;
	while (P != NULL&&P->Element != X)
	{
		P = P->Next;
	}
	return P;
}
void Delete(ElementType X, List L)
{
	Position P;
	P = FindPrevious(X, L);
	if (!IsLast(P, L)) {
		Position TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
Position FindPrevious(ElementType X, List L)
{
	Position P;
	P = L;
	while (P->Next != NULL&&P->Next->Element != X)
		P = P->Next;
	return P;
}
void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;

	TmpCell = (Node *)malloc(sizeof(struct Node));
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element = X;
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
void DeleteList(List L)
{
	Position p;
	p = L->Next;
	L->Next = NULL;
	while (p != NULL) {
		Position tmp;
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
Position Header(List L)
{
	return L;
}
Position First(List L)
{
	return L->Next;
}
Position Advance(Position P)
{
	return P->Next;
}
ElementType Data(Position P)
{
	return P->Element;
}
