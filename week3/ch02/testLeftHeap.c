#include"LeftHeap.h"

int main()
{
	PriorityQueue One;
	One = NULL;
	One = Insert1(3, One);
	One = Insert1(10, One);
	One = Insert1(8, One);
	One = Insert1(21, One);
	One = Insert1(14, One);
	One = Insert1(17, One);
	One = Insert1(23, One);
	One = Insert1(26, One);
	PriorityQueue Two;
	Two = NULL;
	Two = Insert1(6, Two);
	Two = Insert1(12, Two);
	Two = Insert1(7, Two);
	Two = Insert1(18, Two);
	Two = Insert1(24, Two);
	Two = Insert1(37, Two);
	Two = Insert1(18, Two);
	Two = Insert1(33, Two);
	PriorityQueue T = Merge(One, Two);
	for (int i = 0; i < 15; i++)
	{
		printf("%d\n", FindMin(T));
		T = DeleteMin1(T);
	}
}
