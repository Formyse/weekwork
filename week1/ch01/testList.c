#include"List.h"
#include<stdio.h>

int main()
{
	List L;//初始化各项数据
	Position P;
	int i;
	L = MakeEmpty(NULL);
	P = Header(L);
	PrintList(L);//打印

	for (i = 0; i < 10; i++)
	{
		Insert(i, L, P);//插入节点
		PrintList(L);//打印链表
		P = Advance(P);//移动节点
	}
	for (i = 0; i < 10; i += 2)
		Delete(i, L);//删除偶数节点

	for (i = 0; i < 10; i++)
		if ((i % 2 == 0) == (Find(i, L) != NULL))//判断偶节点值是否不为0
			printf("Find fails\n");

	printf("Finished deletions\n");

	PrintList(L);//打印链表

	DeleteList(L);//删除链表
	getchar();
	return 0;

	
}
