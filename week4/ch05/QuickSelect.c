#include<stdio.h>
typedef int ElementType;
#define Cutoff (3)
void Swap(int* u, int* v)
{
	int temp;
	temp = *u;
	*u = *v;
	*v = temp;
}
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];

}
void Insertionsort(ElementType A[], int N)
{
	int j, P;
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
void Qselect(ElementType A[], int k, int Left, int Right)
{
	int i, j;
	ElementType Pivot;
	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left; j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		if (k <= i)
			Qselect(A, k, Left, i - 1);
		else if (k > i + 1)
			Qselect(A, k, i + 1, Right);
	}
	else
		Insertionsort(A + Left, Right - Left + 1);
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
	int a[10] = { 8,1,4,9,0,3,5,2,7,6 };
	Qselect(a,9,0,9);
	PrintSort(a, 10);
}
