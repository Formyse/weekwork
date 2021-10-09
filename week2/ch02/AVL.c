#include "AVL.h"

struct _AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

int Height(AvlTree T)
{
	return T ? T->Height : 0;
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, AvlTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Element < X)
		return Find(X, T->Right);
	else if (T->Element > X)
		return Find(X, T->Left);
	else
		return T;
}

Position FindMin(AvlTree T)
{
	if (T != NULL)
		while (T->Left != NULL)
			T = T->Left;
	return T;
}

Position FindMax(AvlTree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}

AvlTree SingleRotateWithLeft(AvlTree T)
{
	AvlTree temp;
	temp = T->Left;
	T->Left = temp->Right;
	temp->Right = T;
	temp->Height = Height(temp->Left) > Height(temp->Right) ? Height(temp->Left) + 1 : Height(temp->Right) + 1;
	T->Height = Height(T->Left) > Height(T->Right) ? Height(T->Left) + 1 : Height(T->Right) + 1;
	return temp;
}

AvlTree SingleRotateWithRight(AvlTree T)
{
	AvlTree temp;
	temp = T->Right;
	T->Right = temp->Left;
	temp->Left = T;
	temp->Height = Height(temp->Right) > Height(temp->Left) ? Height(temp->Right) + 1 : Height(temp->Left) + 1;
	T->Height = Height(T->Right) > Height(T->Left) ? Height(T->Right) + 1 : Height(T->Left) + 1;
	return temp;
}

AvlTree DoubleRotateWithLeft(AvlTree T)
{
	T->Left = SingleRotateWithRight(T->Left);
	return SingleRotateWithLeft(T);
}

AvlTree DoubleRotateWithRight(AvlTree T)
{
	T->Right = SingleRotateWithLeft(T->Right);
	return SingleRotateWithRight(T);
}

AvlTree Insert(ElementType X, AvlTree T)
{
	if (T == NULL)
	{
		if ((T = (AvlTree)malloc(sizeof(AvlNode))) == NULL)
		{
			printf("Error! Out of space! \n");
			return NULL;
		}
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}
	else if (X < T->Element)
	{
		T->Left = Insert(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (X < T->Right->Element)
				T = DoubleRotateWithRight(T);
			else
				T = SingleRotateWithRight(T);
		}
	}
	T->Height = Height(T->Left) > Height(T->Right) ? Height(T->Left) + 1 : Height(T->Right) + 1;
	return T;
}

AvlTree Delete(ElementType X, AvlTree T)
{
	Position temp;
	if (T == NULL)
	{
		printf("Error! No such node! \n");
		return NULL;
	}
	if (X < T->Element)
	{
		T->Left = Delete(X, T->Left);
		T->Height = Height(T->Left) > Height(T->Right) ? Height(T->Left) + 1 : Height(T->Right) + 1;
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (Height(T->Right->Left) > Height(T->Right->Right))
				T = DoubleRotateWithRight(T);
			else
				T = SingleRotateWithRight(T);
		}
	}
	else if (X > T->Element)
	{
		T->Right = Delete(X, T->Right);
		T->Height = Height(T->Left) > Height(T->Right) ? Height(T->Left) + 1 : Height(T->Right) + 1;
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (Height(T->Left->Left) < Height(T->Left->Right))
				T = DoubleRotateWithLeft(T);
			else
				T = SingleRotateWithLeft(T);
		}
	}
	else
	{
		if (T->Left && T->Right)
		{
			temp = FindMin(T->Right);
			T->Element = temp->Element;
			T->Right = Delete(T->Element, T->Right);
		}
		else
		{
			temp = T;
			if (T->Left == NULL)
				T = T->Right;
			else if (T->Right == NULL)
				T = T->Left;
			free(temp);
		}
	}
	return T;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}

void print_tree(int depth, int left, AvlTree T)
{
	int i;
	if (T) {
		for (i = 0; i < left; i++)
			printf("    ");
		printf("%d\n", T->Element);
		print_tree(depth + 1, left - 1, T->Left);
		print_tree(depth + 1, left + 1, T->Right);
	}
}
void test()
{
	AvlTree t;
	printf("\n ====== test for building the AVLTree ====== \n");
	printf("\n [the left-left single rotate case] test with inserting 3, 2, 1 in trun \n");

	t = NULL;
	t = Insert(1, t);
	t = Insert(2, t);
	t = Insert(3, t);
	t = Insert(4, t);
	t = Insert(5, t);
	t = Insert(6, t);
	
	print_tree(2, 5, t);
}

