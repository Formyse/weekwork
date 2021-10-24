#include<stdio.h>

typedef int ElementType;
#define LeftChild(i) (2*(i)+1)

void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;
	for (Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}
void Swap(ElementType *p1, ElementType*p2)
{
	ElementType Tmp;
	Tmp = *p1;
	*p1 = *p2;
	*p2 = Tmp;
}
void HeapSort(ElementType A[], int N)
{
	int i;
	for (i = N / 2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}

int main()
{
	int a[7] = { 53,31,41,26,58,59,97 };
	HeapSort(a, 7);
	PrintSort(a, 7);
}
