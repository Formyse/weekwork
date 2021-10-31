#include<stdio.h>

int fib(int n)
{
	if (n < 2)
		return n;
	int Last,NextToLast,Answer;
	Last = NextToLast = 1;
	for (int i = 2; i <= n; i++)
	{
		Answer = Last + NextToLast;
		NextToLast = Last;
		Last = Answer;
	}
	return Answer;
}
int Fib(int n)
{
	if (n <= 1)
		return 1;
	else
		return Fib(n - 1) + Fib(n - 2);
}
int main(void)
{
	int n;
	printf("输入fib第几项：");
	scanf_s("%d", &n);
	int result = fib(n);
	printf("fib第%d项为：", n);
	printf("%d", result);
	getchar();
	return 0;
}
