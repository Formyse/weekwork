#include<stdio.h>
typedef int ElementType;

void ShellSort(ElementType A[], int N)
{
	int i, j, Increment;
	ElementType Tmp;

	for (Increment = N / 2; Increment > 0; Increment /= 2)
		for (i = Increment; i < N; i++)
		{
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
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
	int a[13] = { 81,94,11,96,12,35,17,95,28,58,41,75,15 };
	ShellSort(a, 13);
	PrintSort(a, 13);
}
