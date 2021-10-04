#include"List.h"
#include<malloc.h>
#include<stdio.h>

struct Node
{
	ElementType Element;
	Position Next;
};

List CreateList()
{
	List L =(Node *) malloc(sizeof(struct Node));//分配空间
	if (L == NULL)
		printf("out of memory");
	L->Next = NULL;//创建的新节点都会指向空
	return L;
}
List MakeEmpty(List L)
{
	if (L != NULL)//不为空就删除
		DeleteList(L);
	L = (Node*)malloc(sizeof(struct Node));//控制空间分配
	if (L == NULL)
		printf("Out of memory");
	L->Next = NULL;//直到为空
	return L;
}
int IsEmpty(List L)
{
	return L->Next == NULL;//判断链表是否指向空
}
int IsLast(Position P, List L)
{
	return P->Next == NULL;//判断该节点是否指向空
}
void PrintList(const List L)
{
	Position P = Header(L);//指向头节点，从头节点开始

	if (IsEmpty(L))//判断是否为空
		printf("Empty list\n");
	else
	{
		while (!IsLast(P, L))//不为空，就打印输出
		{
			P = Advance(P);
			printf("%d ", Data(P));
		} 
		printf("\n");
	}


}
Position Find(ElementType X, List L)
{
	Position P;
	P = L->Next;
	while (P != NULL&&P->Element != X)若不为空且值不等于X
	{
		P = P->Next;//指向下一节点
	}
	return P;
}
void Delete(ElementType X, List L)
{
	Position P;
	P = FindPrevious(X, L);//找到前一节点
	if (!IsLast(P, L)) //如果不为最后一个，就删除
	{
		Position TmpCell = P->Next;//利用临时变量来删除
		P->Next = TmpCell->Next;
		free(TmpCell);
	}
}
Position FindPrevious(ElementType X, List L)
{
	Position P;
	P = L;
	while (P->Next != NULL&&P->Next->Element != X)
		P = P->Next;
	return P;
}
void Insert(ElementType X, List L, Position P)
{
	Position TmpCell;//定义临时变量

	TmpCell = (Node *)malloc(sizeof(struct Node));//分配空间
	if (TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element = X;//利用临时变量来插入节点
	TmpCell->Next = P->Next;
	P->Next = TmpCell;
}
void DeleteList(List L)
{
	Position p;
	p = L->Next;
	L->Next = NULL;
	while (p != NULL) {
		Position tmp;//借助临时变量来删除节点
		tmp = p->Next;
		free(p);
		p = tmp;
	}
}
Position Header(List L)
{
	return L;//返回头节点指针
}
Position First(List L)
{
	return L->Next;//返回第一节点指针
}
Position Advance(Position P)
{
	return P->Next;//返回指针
}
ElementType Data(Position P)
{
	return P->Element;//返回数据
}
