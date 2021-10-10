## 1. 二叉查找树

二叉查找树的简单操作声明：

### 1.`Tree.h`

```
#pragma once
#include<stdlib.h>
#include<stdio.h>
#ifndef Tree.h
typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
SearchTree MakeEmpty(SearchTree T);//置空操作
Position Find(ElementType X, SearchTree T);//查找
Position FindMin(SearchTree T);//查找最小
Position FindMax(SearchTree T);//查找最大
SearchTree Insert(ElementType X, SearchTree T);//插入节点
SearchTree Delete(ElementType X, SearchTree T);//删除节点
ElementType Retrieve(Position P);//返回数值
#endif // !Tree.h
```

### 2.`Tree.c`

```
#include"Tree.h"
struct  TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
	
}
Position Find(ElementType X, SearchTree T)
{
	if (T == NULL)
		return NULL;
	if (X < T->Element)
		return Find(X, T->Left);
	else
		if (X > T->Element)
			return Find(X, T->Right);
		else
			return T;

}
Position FindMin(SearchTree T)
{
	if (T == NULL)
		return NULL;
	else
		if (T->Left == NULL)
			return T;
		else
			return FindMin(T->Left);
}
Position FindMax(SearchTree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;

	return T;

}
SearchTree Insert(ElementType X, SearchTree T)
{
	if (T == NULL)
	{
		
		     T = (TreeNode *)malloc(sizeof(struct TreeNode));
	         if (T == NULL)
			            printf("Out of space!!!");
		else
		{
			             T->Element = X;
			             T->Left = T->Right = NULL;
		}
	}
	else
	if (X < T->Element)
		T->Left = Insert(X, T->Left);
	else
	if (X > T->Element)
		T->Right = Insert(X, T->Right);
	
   return T; 
}
SearchTree Delete(ElementType X, SearchTree T)
{
	Position TmpCell;

	if (T == NULL)
		printf("Element not found");
	else
	if (X < T->Element)  
			T->Left = Delete(X, T->Left);
	else
	if (X > T->Element)  
		T->Right = Delete(X, T->Right);
	else  
	if (T->Left && T->Right)  
		{
		
			TmpCell = FindMin(T->Right);
			T->Element = TmpCell->Element;
			T->Right = Delete(T->Element, T->Right);
		}
	else  
		{
			TmpCell = T;
			if (T->Left == NULL) 
				T = T->Right;
			else if (T->Right == NULL)
				T = T->Left;
			free(TmpCell);
		}

	return T;

}
ElementType Retrieve(Position P)
{
	return P->Element;
}
```

### 3.`testTree.c`

```
#include"Tree.h"

int main()
{
	SearchTree T;
	Position P;
	int i;
	int j = 0;

	T = MakeEmpty(NULL);
	for (i = 0; i < 50; i++, j = (j + 7) % 50)
		T = Insert(j, T);
	for (i = 0; i < 50; i++)
		if ((P = Find(i, T)) == NULL || Retrieve(P) != i)
			printf("Error at %d\n", i);

	for (i = 0; i < 50; i += 2)
		T = Delete(i, T);

	for (i = 1; i < 50; i += 2)
		if ((P = Find(i, T)) == NULL || Retrieve(P) != i)
			printf("Error at %d\n", i);
	for (i = 0; i < 50; i += 2)
		if ((P = Find(i, T)) != NULL)
			printf("Error at %d\n", i);

	printf("Min is %d, Max is %d\n", Retrieve(FindMin(T)),
		Retrieve(FindMax(T)));

	return 0;

}
```

## 2.表达式树

### 1.前序遍历

  遍历顺序：（节点，左，右）

### 2.中序遍历

遍历顺序：（左，节点，右）

### 3.后序遍历

遍历顺序：（左，右，节点）

## 3.文件系统中的目录

### 1.先序遍历

在先序遍历中，对节点的处理是在对其诸儿子之前进行的。

### 2.后序遍历

在后序遍历中，对节点的处理是在对其诸儿子之后进行的。

## 4.`AVL`树

### 1.概念

`AVL`树是带有平衡条件的二叉查找树。

### 2.平衡条件

一棵`AVL`树是其每个节点的左子树和右子树的高度最多差1的二叉查找树。

### 3.旋转

#### 1.单旋转

左---左        右---右

#### 2.双旋转

左---右      右---左

### 4.`AVL`树的实现

#### 1.`AVL.h`

```
#pragma once
#ifndef AVL.h
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
struct _AvlNode;
typedef struct _AvlNode AvlNode;
typedef AvlNode *Position;
typedef AvlNode *AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);
void print_tree(int depth, int left, AvlTree T);
void test();
#endif // !AVL.h

```

#### 2.`AVL.c`

```
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


```

#### 3.`testAVL.c`

```
#include"AVL.h"


int main()
{
	test();
	return 0;
}
```

### 5.树的遍历

#### 1.中序遍历

#### 2.后序遍历

#### 3.层序遍历

#### 4.先序遍历

## 5.`B`树

### 1.概念

阶为M的B树是一棵具有下列结构特性的树：

- 树的根或者是一片树叶，或者其儿子数在2和M之间。
- 除根外，所以非树叶节点的儿子数在[M/2]和M之间。
- 所以的树叶都在相同的深度上。

## 6.散列

### 1.概述

​          散列表`ADT`只支持二叉查找树所允许的一部分操作，散列表的实现常常叫做散列。散列是一种以常数平均时间执行插入、删除和查找的技术。但是，那些需要元素间任何排序信息的操作将不会得到有效的支持。

### 2.实现

​          理想的散列表数据结构只不过是一个包含有关关键字的具有固定大小的数组。典型情况下，一个关键字就是一个带有相关值的字符串。我们把表的大小记作`TableSize`，并将其理解为散列数据结构的一部分而不仅仅是浮动于全局的某个变量。通常的习惯是让表从0到`TableSize`-1变化。每个关键字被映射到从0到`TableSize-1`这个范围中的某个数，并且被放到适当的单元中。这个映射就叫做散列函数，理想情况下它应该运算简单并且应该保证任何两个不同的关键字映射到不同的单元。不过，这是不可能的，因为单元的数目是有限的，而关键字实际上是用不完的。因此，我们寻找一个散列函数，该函数要在单元之间均匀地分配关键字。

​          这就是散列的基本想法。剩下的问题则是要选择一个函数，决定当两个关键字散列到同一个值的时候（称为冲突（collision））应该做什么以及如何确定散列表的大小。

如果输入的关键字是整数，则一般合理的方法就是直接返回“`Key mod Tablesize”`的结果，除非Key碰巧具有某些不理想的性质。在这种情况下，散列函数的选择需要仔细考虑。

　　解决冲突的方法有几种，我们将讨论其中最简单的两种：分离链接法和开放定址法。

### 3.分离链接法

其做法是将散列到同一个值的所有元素保留到一个表中

#### 1.`HashSep.h`

```
#pragma once
#ifndef HashSep.h
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;
typedef Position List;
HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
Index Hash(const int Key, int TableSize);
#endif // !HashSep.h

```

#### 2.`HashSep.c`

```
#include"HashSep.h"


struct ListNode
{
	ElementType Key;
	Position Next;
};

struct HashTbl
{
	int TableSize;
	List *TheLists;
};
int NextPrime(int N)
{
	if (N % 2 == 0)
		N++;
	int i;
	int NotPrime = 0;
	for (;; N += 2)
	{
		NotPrime = 0;
		for (i = 3; i * i <= N; i += 2)
			if (N % i == 0)
			{
				NotPrime = 1;
				break;
			}
		if (!NotPrime)
			return N;
	}
}
Index Hash(const int Key, int TableSize)
{
	return Key % TableSize;
}
int Same(ElementType e1, ElementType e2)
{
	return e1 == e2;
}
HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if ((H = (HashTable)malloc(sizeof(struct HashTbl))) == NULL)
	{
		printf("Error! Out of memory! \n");
		return NULL;
	}
	H->TableSize = NextPrime(TableSize);
	H->TheLists = (Position *)malloc(H->TableSize * sizeof(Position));
	for (i = 0; i < H->TableSize; i++)
	{
		if ((H->TheLists[i] = (List)malloc(sizeof(struct ListNode))) == NULL)
		{
			printf("Error! Out of memory! \n");
			return NULL;
		}
		H->TheLists[i]->Next = NULL;
	}
	return H;
}
void DestroyTable(HashTable H)
{
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		Position p, q;
		q = H->TheLists[i];
		p = q->Next;
		while (p)
		{
			free(q);
			q = p;
			p = p->Next;
		}
	}
	free(H);
}
Position Find(ElementType Key, HashTable H)
{
	Position p;
	p = H->TheLists[Hash(Key, H->TableSize)]->Next;
	while (p)
	{
		if (Same(p->Key, Key))
			break;
		p = p->Next;
	}
	return p;
}
void Insert(ElementType Key, HashTable H)
{
	Position p;
	List L;
	if (Find(Key, H) != NULL)
		return;
	if ((p = (Position)malloc(sizeof(struct ListNode))) == NULL)
	{
		printf("Error! Out of memory! \n");
		return;
	}
	p->Key = Key;
	L = H->TheLists[Hash(Key, H->TableSize)];
	p->Next = L->Next;
	L->Next = p;
}
```

#### 3.`testHashSep.c`

```
#include"HashSep.h"

int main()
{
	HashTable H = InitializeTable(10);
	int i;
	printf("HashTable:\n");
	for (i = 0; i < 10; i++)
	{
		Insert(i * i, H);
		printf("%d:%d\n", i*i, Hash(i * i, 10));
	}
	return 0;
}
```

### 4.开放定址法(平方探测法)

还有线性探测法、双散列

#### 1.`HashQuad.h`

```
#pragma once
#ifndef HashQuad.h
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int Index;
typedef Index Position;
typedef int ElementType;
struct HashTbl;
typedef struct HashTbl *HashTable;

typedef struct HashEntry Cell;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable ReHash(HashTable H);
Index Hash(ElementType Key, int TableSize);
#endif // !HashQuad.h

```

#### 2.`HashQuad.c`

```
#include "HashQuad.h"

enum KindOfEntry
{
	Legitimate,
	Empty,
	Deleted
};

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

struct HashTbl
{
	int TableSize;
	Cell *TheCells;
};


int NextPrime(int N)
{
	if (N % 2 == 0)
		N++;
	int i;
	int NotPrime = 0;
	for (;; N += 2)
	{
		NotPrime = 0;
		for (i = 3; i * i <= N; i += 2)
			if (N % i == 0)
			{
				NotPrime = 1;
				break;
			}
		if (!NotPrime)
			return N;
	}
}


Index Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;
	if ((H = (HashTable)malloc(sizeof(struct HashTbl))) == NULL)
	{
		printf("Error!\n");
		return NULL;
	}
	H->TableSize = NextPrime(TableSize);
	if ((H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize)) == NULL)
	{
		printf("Error!\n");
		return NULL;
	}
	for (i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = Empty;
	return H;

}

void DestroyTable(HashTable H)
{
	free(H->TheCells);
	free(H);
}

Position Find(ElementType Key, HashTable H)
{
	Index id = Hash(Key, H->TableSize);
	int i = 0;
	while (H->TheCells[id].Info != Empty && H->TheCells[id].Element != Key)
	{
		id += 2*++i - 1;
		if (id >= H->TableSize)
			id -= H->TableSize;
	}
	return id;
}

void Insert(ElementType Key, HashTable H)
{
	Position p = Find(Key, H);
	if (H->TheCells[p].Info != Legitimate)
	{
		H->TheCells[p].Element = Key;
		H->TheCells[p].Info = Legitimate;
	}
}

ElementType Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].Element;
}

HashTable ReHash(HashTable H)//再散列
{
	int i;
	int OldSize;
	Cell *OldCells;
	OldCells = H->TheCells;
	OldSize = H->TableSize;
	H = InitializeTable(2 * OldSize);
	for (i = 0; i < H->TableSize; i++)
		if (OldCells[i].Info == Legitimate)
			Insert(OldCells[i].Element, H);
	free(OldCells);
	return H;
}
```

#### 3.`testHashQuad.c`

```
#include "HashQuad.h"    

int main()
{
	HashTable H = InitializeTable(10);
	printf("Hash Table: \n");
	Insert(9, H);
	Insert(19, H);
	Insert(20, H);
	Insert(63, H);
	Insert(75, H);
	Position P1 = Find(9, H);
	Position P2 = Find(19, H);
	Position P3 = Find(20, H);
	Position P4 = Find(63, H);
	Position P5 = Find(75, H);
	printf("%d:%d\n",9, P1);
	printf("%d:%d\n", 19, P2);
	printf("%d:%d\n", 20, P3);
	printf("%d:%d\n", 63, P4);
	printf("%d:%d\n", 75, P5);
	return 0;
}
```

