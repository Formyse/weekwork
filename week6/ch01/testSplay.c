#include "Splay.h"
#include <iostream>

int main()
{
	int i;
	SplayTree One;
	One = NULL;

	/*插入数据，先插入10，再分别按偶数奇数插入0-20*/
	One = Insert(10, One);

	for (i = 0; i < 10; i++)
	{
		One = Insert(2 * i, One);
	}

	for (i = 0; i < 10; i++)
	{
		One = Insert(2 * i + 1, One);
	}
	/*打印出树，每一级深度加一个4个空格，先打印左子树再打印右子数*/
	PrintTree(One, 0);
	printf("\n\n\n\n");

	/*寻找5之后的树*/
	One = Find(5, One);
	PrintTree(One, 0);
	printf("\n\n\n\n");

	/*删除元素之后的树*/
	One = Remove(11, One);
	One = Remove(3, One);
	One = Remove(21, One);
	printf("\n\n\n\n");
	printf("\n\n\n\n");

	One = Remove(3, One);
	One = Remove(8, One);
	One = Remove(16, One);
	PrintTree(One, 0);

	std::cout << std::endl;
}
