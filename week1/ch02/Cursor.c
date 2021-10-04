#include "cursor.h"
#include<stdio.h>


struct Node//定义结构体
{
	ElementType Element;
	Position    Next;
};


struct Node CursorSpace[SpaceSize];//节点数组来模拟内存分配


static Position CursorAlloc(void)
{
	Position P;

	P = CursorSpace[0].Next;//P初始化为数组第一个元素
	CursorSpace[0].Next = CursorSpace[P].Next;//数组第一个元素为P

	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

void InitializeCursorSpace(void)//用数组来模拟指针
{
	int i;

	for (i = 0; i < SpaceSize; i++)
		CursorSpace[i].Next = i + 1;
	CursorSpace[SpaceSize - 1].Next = 0;
}

List MakeEmpty(List L)//置空操作
{
	if (L != NULL)
		DeleteList(L);
	L = CursorAlloc();
	if (L == 0)
		printf("Out of memory!");
	CursorSpace[L].Next = 0;
	return L;
}

int IsEmpty(List L)//判断是否为空
{
	return CursorSpace[L].Next == 0;
}
int IsLast(Position P, List L)//判断是否为尾
{
	return CursorSpace[P].Next == 0;
}
void PrintList(const List L)//打印链表
{
	Position P = Header(L);

	if (IsEmpty(L))//判断是否为空
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))//若不为空，移动节点，打印数据
		{
			P = Advance(P);
			printf("%d ", Retrieve(P));
		}
		printf("\n");
	}

}
Position Find(ElementType X, List L)//查询某值的位置
{
	Position P;

	P = CursorSpace[L].Next;
    while (P && CursorSpace[P].Element != X)//P不为空且数据不等于X
		   P = CursorSpace[P].Next;//移动到下一节点

    return P;
}
void Delete(ElementType X, List L)
{
	Position P, TmpCell;

	P = FindPrevious(X, L);

	if (!IsLast(P, L))  
	{                      
		TmpCell = CursorSpace[P].Next;
		CursorSpace[P].Next = CursorSpace[TmpCell].Next;
		CursorFree(TmpCell);
	}
}

Position FindPrevious(ElementType X, List L)
{
	Position P;

	P = L;
	while (CursorSpace[P].Next &&
		CursorSpace[CursorSpace[P].Next].Element != X)
	 P = CursorSpace[P].Next;

	return P;
}

void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;

	TmpCell = CursorAlloc();
	if (TmpCell == 0)
		printf("Out of space!!!");

	CursorSpace[TmpCell].Element = X;
	CursorSpace[TmpCell].Next = CursorSpace[P].Next;
    CursorSpace[P].Next = TmpCell;
}

void DeleteList(List L)
{
	Position P, Tmp;//定义临时变量

	P = CursorSpace[L].Next;  //P初始化为头节点
	CursorSpace[L].Next = 0;
	while (P != 0)
	{
		 Tmp = CursorSpace[P].Next;//利用临时变量删除节点
		 CursorFree(P);
		 P = Tmp;
	}
}

Position Header(List L)//头节点
{
	return L;
}

Position First(List L)//第一个节点
{
	return CursorSpace[L].Next;
}

Position Advance(Position P)//移动节点
{
	return CursorSpace[P].Next;
}

ElementType Retrieve(Position P)//指向节点数据
{
	return CursorSpace[P].Element;
}
