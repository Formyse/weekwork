#include<stdio.h>
#include<stdlib.h>
double Eval(int n)
{
	int i;
	double sum;
	if (n == 0)
		return 1.0;
	else
	{
		sum = 0.0;
		for (i = 0; i < n; i++)
			sum += Eval(i);
		return 2.0*sum / n + n;
	}
}
double eval(int n)
{
	int i, j;
	double sum, answer;
	double *c;
	c = (double*)malloc(sizeof(double)*(n + 1));
	if (c == NULL)
		printf("Out of spcae!!!");
	c[0] = 1.0;
	for (i = 1; i <= n; i++)
	{
		sum = 0.0;
		for (j = 0; j < i; j++)
			sum += c[j];
		c[i] = 2.0*sum / i + i;
	}
	answer = c[n];
	free(c);
	return answer;
}

int main()
{
	double a = Eval(5);
	double b = eval(5);
	printf("%d\n", a);
	printf("%d\n", b);
}
