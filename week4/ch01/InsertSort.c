#include<stdio.h>
typedef int ElementType;


void Insertionsort(ElementType A[], int N)
{
	int j,P;
	ElementType Tmp;
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > Tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = Tmp;
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
	int a[6] = { 34,8,64,51,32,21 };
	Insertionsort(a, 6);
	PrintSort(a, 6);
}
