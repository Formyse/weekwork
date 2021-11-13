#include "RedBlackTree.h"
#include <iostream>
#define Infinity 0x7FFFFFFF
#define NegInfinity 0x8FFFFFFF
Position NullNode = NULL;

static Position X, P, GP, GGP, BRO;

//右旋转
RedBlackTree rightSingleRotate(RedBlackTree T)
{
	RedBlackTree k1;

	k1 = T->left;
	T->left = k1->right;
	k1->right = T;
	return k1;
}
//左旋转
RedBlackTree leftSingleRotate(RedBlackTree k1)
{
	Position k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	return k2;
}

//打印红黑树
void DoPrint(RedBlackTree T, int depth)
{
	if (T != NullNode)
	{
		DoPrint(T->left, depth + 1);
		for (int i = 0; i < depth; i++)
			printf("    ");
		printf("%d,%s\n", T->Elememt, T->color == Red ? "Red" : "Black");

		DoPrint(T->right, depth + 1);
	}
}


//初始化红黑树，如果NullNode未被初始化则给其分配空间
RedBlackTree Initialize()
{
	if (NullNode == NULL)
	{
		NullNode = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
		if (NullNode == NULL)
			exit(1);
		NullNode->color = Black;
		NullNode->left = NullNode->right = NullNode;
		NullNode->Elememt = Infinity;
	}

	RedBlackTree T;
	T = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	if (T == NULL)
		exit(1);

	T->Elememt = NegInfinity;
	T->left = T->right = NullNode;
	T->color = Black;

	return T;
}

//需要进行旋转的时候进行旋转，旋转之前应先进行判定
static Position Rotate(ElementType item, RedBlackTree Parent)
{
	if (item < Parent->Elememt)
		return Parent->left = item < Parent->left->Elememt ?
		rightSingleRotate(Parent->left) :
		leftSingleRotate(Parent->left);
	else
		return Parent->right = item < Parent->right->Elememt ?
		rightSingleRotate(Parent->right) :
		leftSingleRotate(Parent->right);
}

//两个孩子都是红色节点时，交换父亲和孩子节点的颜色，有必要的时候进行旋转
static void HandleReorient(ElementType item, RedBlackTree T)
{
	X->color = Red;
	X->left->color = Black;
	X->right->color = Black;

	if (P->color == Red)
	{
		GP->color = Red;
		if ((item < P->Elememt) != (item < GP->Elememt))
			//P = Rotate(item, GP);
			Rotate(item, GP);

		X = Rotate(item, GGP);
		X->color = Black;

	}
	T->right->color = Black;
}

//插入节点，如果节点已经存在，则什么也不做
RedBlackTree insert(ElementType item, RedBlackTree T)
{
	X = P = GP = T;
	NullNode->Elememt = item;
	while (X->Elememt != item)
	{
		GGP = GP; GP = P; P = X;
		if (item < X->Elememt)
			X = X->left;
		else
			X = X->right;
		if (X->left->color == Red && X->right->color == Red)
			HandleReorient(item, T);
	}
	if (X != NullNode)
		return NullNode;

	X = (RedBlackTree)malloc(sizeof(struct RedBlackNode));
	X->Elememt = item;
	X->left = X->right = NullNode;

	if (item < P->Elememt)
		P->left = X;
	else
		P->right = X;

	HandleReorient(item, T);
	return T;
}
