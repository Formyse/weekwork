# 排序

## 1.插入排序

### 1.概念

插入排序由n-1趟排序组成。对于P=1趟到P=n-1趟，插入排序保证从位置0到位置P上的元素为已排序状态。

### 2.实现

```
#include<stdio.h>
typedef int ElementType;


void Insertionsort(ElementType A[], int N)
{
	int j,P;
	ElementType Tmp;
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > Tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = Tmp;
	}
}


void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}

int main()
{
	int a[6] = { 34,8,64,51,32,21 };
	Insertionsort(a, 6);
	PrintSort(a, 6);
}
```

### 3.分析

由于嵌套循环每趟花费N次迭代，因此插入排序为O（N^2）

1. N个互异数的数组的平均逆序数是N（N-1）/4
2. 通过交换相邻元素进行排序的任何算法平均需要Ω（N^2）时间(冒泡排序、选择排序)

## 2.希尔排序

### 1.概念

希尔排序通过比较相距一定间隔的元素来工作，各趟比较所用的距离随着算法的进行而减小，直到只比较相邻元素的最后一趟排序为止。**希尔排序也叫作缩小增量排序**

### 2.实现

```
#include<stdio.h>
typedef int ElementType;

void ShellSort(ElementType A[], int N)
{
	int i, j, Increment;
	ElementType Tmp;

	for (Increment = N / 2; Increment > 0; Increment /= 2)
		for (i = Increment; i < N; i++)
		{
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			A[j] = Tmp;
		}
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}

int main()
{
	int a[13] = { 81,94,11,96,12,35,17,95,28,58,41,75,15 };
	ShellSort(a, 13);
	PrintSort(a, 13);
}
```

### 3.分析

1. 使用希尔增量时希尔排序的最坏情形运行时间为（N^2）
2. 使用`Hibbard`增量的希尔排序的最坏情形运行时间为（N^3/2）
3. `Sedgewick`增量序列最坏的情形运行时间为（N^4/3）

## 3.堆排序

### 1.概念

基于优先队列排序想法的算法叫作堆排序

### 2.实现

为避免使用第二个数组的聪明做法是利用这样的事实：在每次`DeleteMin`之后，堆缩小了1.因此堆中最后的单元可以用来存放刚刚删去的元素。该数组将以递减的顺序包含这些元素。

`DeleteMax`得到的数组将以递增的顺序包含这些元素。

```
#include<stdio.h>

typedef int ElementType;
#define LeftChild(i) (2*(i)+1)

void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;
	for (Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}
void Swap(ElementType *p1, ElementType*p2)
{
	ElementType Tmp;
	Tmp = *p1;
	*p1 = *p2;
	*p2 = Tmp;
}
void HeapSort(ElementType A[], int N)
{
	int i;
	for (i = N / 2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}

int main()
{
	int a[7] = { 97,53,59,26,41,58,31 };
	HeapSort(a, 7);
	PrintSort(a, 7);
}
```

### 3.分析

1. 经验指出：堆排序是一个非常稳定的算法：它平均使用的比较只比最坏情况界指出的略少。
2. 对N个互异项的随机排列进行堆排序，所用的平均比较次数为`2NlogN-O（NloglogN）`。
3. 经过复杂论述可以证明，堆排序总是使用至少`NlogN-O（N）`次比较，而且存在输入数据能够达到这个界。

## 4.归并排序

### 1.概念

该算法的基本操作就是合并两个已排序的表。因为这两个表是已排序的，所以若将输出放到第三个表中，则该算法可以通过对输入数据一趟排序来完成。基本的合并算法是取两个输入数组A和B，一个输出数组C，以及三个计数器`Aptr，Bptr，Cptr`，它们初始置于对应数组的开始端。`A[Aptr]`和`B[Bptr]`中的较小者被拷贝到C中的下一个位置，相关计数器向前推进一步。当两个输入表有一个用完的时候，则将另一个表中的剩余部分拷贝到C中。

### 2.实现

```
#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd)
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];
	while(Lpos<=LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while(Rpos<=RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];

	for (i = 0; i < NumElements; i++, RightEnd--)
	{
		A[RightEnd] = TmpArray[RightEnd];
	}
}
void MSort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right)/2;
		MSort(A, TmpArray, Left, Center);
		MSort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}

void MergeSort(ElementType A[], int N)
{
	ElementType *TmpArray;
	TmpArray =(ElementType*)malloc(N * sizeof(ElementType));
	if (TmpArray != NULL)
	{
		MSort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
	else
		printf("No space for tmp array");
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}
int main()
{
	int a[8] = { 24,13,26,1,2,27,38,15 };
	MergeSort(a, 8);
	PrintSort(a, 8);

}
```

### 3.分析

虽然归并排序的运行时间是`O（NlogN）`，但是它很难用于主存排序，主要问题在于合并两个排序的表需要线性附加内存，在整个算法中还要花费将数据拷贝到临时数组再拷贝回来这样一些附加的工作，其结果是严重放慢了排序的速度。

## 5.快速排序

### 1.概念

快速排序的平均运行时间是`O（NlogN）`，最坏情形的性能为`O（N^2）`，像归并排序一样，也是一种分治的递归算法，步骤为下列四步：

1. 如果S中元素个数是0或1，则返回。
2. 取S中任意元素v,称之为枢纽元。
3. 将S-{v}(S中其余元素)分为两个不相交集合：
4. 返回两个分别的排序。

### 2.选取枢纽元

1. 错误方法，选第一个元素
2. 安全方法，随机选取枢纽元
3. 三数中值分割法

### 3.分割策略

1. 首先枢纽元与最后一个元素交换。
2. 利用i j不停滑动，直到i j交错。
3. 最后i与枢纽元交换。

### 4.小数组

对于很小的数组（N<=20），快速排序不如插入排序好。

### 5.实现

```
#include<stdio.h>
typedef int ElementType;
#define Cutoff (3)
void Swap(int* u, int* v)
{
	int temp;
	temp = *u;
	*u = *v;
	*v = temp;
}
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];

}
void Insertionsort(ElementType A[], int N)
{
	int j, P;
	ElementType Tmp;
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > Tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = Tmp;
	}
}
void Qsort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left; j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		Qsort(A, Left, i - 1);
		Qsort(A, i + 1, Right);

	}
	else
		Insertionsort(A + Left, Right - Left + 1);
}
void QuickSort(ElementType A[], int N)
{
	Qsort(A, 0, N - 1);
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}
int main()
{
	int a[10] = { 8,1,4,9,0,3,5,2,7,6 };
	QuickSort(a, 10);
	PrintSort(a, 10);
}
```

### 6.分析

1. 最坏情形分析：`O（N^2）`
2. 最好情形分析：`O（NlogN）`
3. 平均情形分析：`O（NlogN)`

### 7.快速选择

经过快速排序简单的修改，与快速排序相比，快速选择只做了一次递归调用而不是两次，算法终止时，第k个最小元就在位置k上，虽然破坏了原来的排序。

```
#include<stdio.h>
typedef int ElementType;
#define Cutoff (3)
void Swap(int* u, int* v)
{
	int temp;
	temp = *u;
	*u = *v;
	*v = temp;
}
ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);

	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];

}
void Insertionsort(ElementType A[], int N)
{
	int j, P;
	ElementType Tmp;
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (j = P; j > 0 && A[j - 1] > Tmp; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = Tmp;
	}
}
void Qselect(ElementType A[], int k, int Left, int Right)
{
	int i, j;
	ElementType Pivot;
	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left; j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot) {}
			while (A[--j] > Pivot) {}
			if (i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);

		if (k <= i)
			Qselect(A, k, Left, i - 1);
		else if (k > i + 1)
			Qselect(A, k, i + 1, Right);
	}
	else
		Insertionsort(A + Left, Right - Left + 1);
}
void PrintSort(ElementType A[], int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", A[i]);
	}
}
int main()
{
	int a[10] = { 8,1,4,9,0,3,5,2,7,6 };
	Qselect(a,9,0,9);
	PrintSort(a, 10);
}
```

## 6.大型结构的排序

### 1.方法

对于所有的算法来说，基本的操作就是交换，不过这里交换两个结构可能是非常昂贵的操作，因为结构实际很大。在这种情况下，实际的解法是让输入数组包含指向结构的指针。我们通过比较指针指向的关键字，并在必要时交换指针来进行排序。这意味着，所有的数据运动基本上就像我们对整数排序那样进行。我们称之为间接排序，可以使用这种方法处理我们已经描述过的大部分数据结构。

## 7.排序的一般下界

### 1.决策树

1. 用于证明下界的抽象概念，决策树是一棵二叉树。每个节点表示在元素之间一组可能的排序，它与已经进行的比较一致。比较的结果是树的边。
2. 令T是深度为d的二叉树，则T最多有2^d片树叶。
3. 具有L片树叶的二叉树的深度至少是[log L]。
4. 只使用元素间比较的任何排序算法在最坏情形下至少需要[log(N!)]次比较。
5. 只使用元素间比较的任何算法需要进行`Ω(NlogN)`次比较。

## 8.桶式排序

### 1.概念

使用一个大小为M称为Count的数组，它被初始化为全0。于是，Count有M个单元（称为桶），这些桶初始化为空。当读入`Ai`时，`Count[Ai]`增1。在所有的输入数据读入后，扫描数组Count，打印出排序后的表。

## 9.外部排序

### 1.概念

外部排序算法，输入数据量太大装不进内存，设计主要用来处理很大的输入的。

### 2.为什么需要新算法

如果有一个大的文件，读入数据很慢。。。

### 3.简单算法

具体例子看书上。。。

原来有13个数，M=3，分成了4组，由Ta输出到Tb，然后每两组进行合并排序由Tb输出到Ta，现在Ta共有2组，继续2组合并排序由Ta输出到Tb，最后Tb与剩下一个数合并排序输出到Ta中。

### 4.多路合并

在原有的2路合并排序的基础上，扩充为k路合并排序

比如：书上3路合并的例子

### 5.多相合并

有34个顺串，如果T2,T3各17，将合并结果合并到T1上，如果想继续合并，必须把T1的前8个顺串从T1拷贝到T2，然后再合并，这样就附加了很多操作。

多相合并要求34顺串不均匀分成2份，假如21分给`T2`，13个分给`T3`，分配要最优，如果顺串个数是一个斐波那契数`FN`，那么分配的最好方式就是分成两个斐波那契数`FN-1、FN-2`。

### 6.替换选择

**书本上的顺串构建的例**

# 不相交集

## 1.等价关系

三个性质：

1. 自反性
2. 对称性
3. 传递性

电气连接是一个等价关系。

## 2.动态等价性问题

输入数据最初是N个集合的类，每个集合含有一个元素。初始的描述是所有的关系为false。每个集合都有一个不同的元素，任何两个交集为空，这使得这些集合不相交。

**不相交集的Union/Find算法**

## 3.实现

```
#include"DisjSet.h"

void Initilialize(DisjSet S)
{
	int i;

	for (i = NumSets; i > 0; i--)
	{
		S[i] = 0;
	}
}
void SetUnion(DisjSet S, SetType Root1, SetType Root2)
{
	if (S[Root2] < S[Root1])
		S[Root1] = Root2;
	else
	{
		if (S[Root1] == S[Root2])
			S[Root1]--;
		S[Root2] = Root1;
	}
}
SetType Find(ElementType X, DisjSet S)
{
	if (S[X] <= 0)
		return X;
	else
		return S[X]=Find(S[X], S);
}
```

## 4.灵巧求并算法

1. 书上首先给出的Union方法执行是相当随意的，它通过使第二棵树成为第一棵树的子树而完成合并。对其简单改进可以打破现有关系，使得总让小树成为较大的树的子树；这种方法叫作按大小求并。
2. 按大小求并
3. 按高度求并

## 5.路径压缩

如果执行Find比Union多的多，那么算法的运行时间很不好，因此为使算法加速而诞生的操作就是路径压缩。

路径压缩的效果使，从X到根的路径上的每一个节点都使它的父节点变成根。（书上有例子）

路径压缩与按大小求并完全兼容，这使得两个例程可以同时实现

路径压缩不完全与按高度求并兼容，因为路径压缩可以改变树的高度。

