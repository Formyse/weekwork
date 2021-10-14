#include"LeftHeap.h"

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};
void switchChildren(PriorityQueue H)
{
	if (H == NULL)
		return;

	PriorityQueue temp;
	temp = H->Right;
	H->Right = H->Left;
	H->Left = temp;
}
PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = Merge(H1->Right, H2);
		if (H1->Left->Npl < H1->Right->Npl)
			switchChildren(H1);

		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}
ElementType FindMin(PriorityQueue H)
{
	return H->Element;
}
int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)//利用递归实现如果根节点小，则与根大的右子树再Merge
{
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	if (H1->Element < H2->Element)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}
PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue newone = (PriorityQueue)malloc(sizeof(TreeNode));
	newone->Element = X;
	newone->Left = newone->Right = NULL;
	newone->Npl = 0;
	H = Merge(H, newone);
	return H;
}
PriorityQueue DeleteMin1(PriorityQueue H)
{
	if (H == NULL)
		return H;
	PriorityQueue Leftchild, Rightchild;
	Leftchild = H->Left;
	Rightchild = H->Right;
	free(H);
	return Merge(Leftchild, Rightchild);
}
void PrintTree(PriorityQueue T)
{
	if (T == NULL)
	{
		perror("wrong tree");
		exit(1);
	}
	if (T->Left != NULL)
		PrintTree(T->Left);

	printf("%d\n", T->Element);
	if (T->Right != NULL)
		PrintTree(T->Right);
}
