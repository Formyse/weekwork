#include"Binomal_Queue.h"


struct BinNode
{
	ElementType Element;
	Position leftChild;
	Position nextSibling;

};

struct Collection
{
	int currentSize;
	BinTree theTrees[MaxSize];
};

BinQueue initialize()
{
	BinQueue H = (BinQueue)calloc(1, sizeof(struct Collection));
	if (H == NULL)
	{
		printf("not enough memory");
		exit(1);
	}
	H->currentSize = 0;
	return H;
}
bool isEmpty(BinQueue H)
{
	return H == NULL;
}

BinTree CombineTrees(BinTree T1, BinTree T2)
{
	if (T1->Element > T2->Element)
		return CombineTrees(T2, T1);

	T2->nextSibling = T1->leftChild;
	T1->leftChild = T2;
	return T1;
}
BinQueue merge(BinQueue H1, BinQueue H2)
{
	BinTree T1, T2, Carry = NULL;
	int i, j;

	if (H1->currentSize + H2->currentSize > Capacity)
	{
		printf("out of space");
		exit(1);
	}
	H1->currentSize += H2->currentSize;

	for (i = 0, j = 1; j <= H1->currentSize; i++, j *= 2)
	{
		T1 = H1->theTrees[i];
		T2 = H2->theTrees[i];

		switch (!!T1 + 2 * !!T2 + 4 * !!Carry)
		{
		case 0:/* not Trees*/
		case 1:/* only H1 */
			break;

		case 2: /*only H2 */
			H1->theTrees[i] = T2;
			H2->theTrees[i] = NULL;
			break;

		case 4: /* only carry */
			H1->theTrees[i] = Carry;
			Carry = NULL;
			break;

		case 3: /* H1 and H2 */
			Carry = CombineTrees(T1, T2);
			H1->theTrees[i] = H2->theTrees[i] = NULL;
			break;
		case 5: /* H1 and Cartry */
			Carry = CombineTrees(T1, Carry);
			H1->theTrees[i] = NULL;
			break;
		case 6: /* H2 and Carry */
			Carry = CombineTrees(T2, Carry);
			H2->theTrees[i] = NULL;
			break;
		case 7: /* H1 and H2 and Carry */
			H1->theTrees[i] = Carry;
			Carry = CombineTrees(T1, T2);
			H2->theTrees[i] = NULL;
			break;

		}
	}
	return H1;
}
void insert(ElementType X, BinQueue H)
{
	BinQueue temp = initialize();
	BinTree newone = (BinTree)malloc(sizeof(struct BinNode));
	if (newone == NULL)
	{
		printf("out of space");
		exit(1);
	}
	newone->Element = X;
	newone->leftChild = newone->nextSibling = NULL;

	temp->currentSize = 1;
	temp->theTrees[0] = newone;

	merge(H, temp);
	free(temp);
}

int findMin(BinQueue H)
{
	int i, min;
	ElementType minvalue = 0x7FFFFFFF;

	if (isEmpty(H))
		return NULL;

	for (i = 0; i < MaxSize; i++)
	{
		if (H->theTrees[i])
			if (H->theTrees[i]->Element < minvalue)
			{
				minvalue = H->theTrees[i]->Element;
				min = i;
			}
	}
	return min;
}
ElementType DeleteMin(BinQueue H)
{
	int i;
	if (isEmpty(H))
	{
		printf("empty\n");
		exit(1);
	}
	int min = findMin(H);
	ElementType minValue;

	BinTree DeletedTree, OldTree;
	BinQueue DeletedQueue;

	OldTree = H->theTrees[min];
	minValue = OldTree->Element;
	DeletedTree = OldTree->leftChild;
	free(OldTree);
	DeletedQueue = initialize();
	DeletedQueue->currentSize = (1 << min) - 1;
	for (i = min - 1; i >= 0; i--)
	{
		DeletedQueue->theTrees[i] = DeletedTree;
		DeletedTree = DeletedTree->nextSibling;
		DeletedQueue->theTrees[i]->nextSibling = NULL;
	}

	H->theTrees[min] = NULL;
	H->currentSize -= DeletedQueue->currentSize + 1;
	merge(H, DeletedQueue);
	return minValue;
}
