# 贪婪算法

## 1.简单的调度问题

### 1.非预占调度

一旦开始一个作业，就必须把该作业运行完。

### 2.调度总代价

总代价=执行该调度的时间+等待时间。

**很关键**

这就是为什么先执行运行时间少的调度，因为后面的调度等待时间短，因此最终总代价小，故平均代价也就小。

### 3.多处理器问题

当调度总数是处理器的**整数倍**时，这时得到的最优调度顺序可能有**很多种**。

## 2.`Huffman`编码

### 1.文件压缩

利用编码技术进行文件压缩

如果一个文件中所有字符都以相同的频率出现，那么要节省空间是**不可能的**。

### 2.前缀编码

只要没有字符代码是别的字符代码的前缀即就是前缀编码。

### 3.`Huffman`算法

如何构建最优编码树：

将所有字符的权按序排列，最小的两个合并，他们的父节点权是它们两个的和，将“和”与剩下的字符权排序，重复操作，最终就可以生成最优编码树。

## 3.近似装箱问题（详细分析看书）

### 1.下项适合算法

### 2.首次适合算法

### 3.最佳适合算法

### 4.首次适合递减算法（效果很好）

### 5.最佳适合递减算法

# 分治算法

## 1.分治算法运行时间

运用算法设计与分析中，分治算法运行时间一般是求递归运行的时间，可以用递归算法公式求得运行时间。

## 2.最近点问题

## 3.选择问题

选择问题讲的是要求我们找出第k个最小的元素。

相当于之前学习快速排序中的快速选择问题，即就是找到第k个最小元素。

## 4.降低比较的平均次数

## 5.一些运算问题的改进

### 1.整数相乘

把一个整数相乘问题，划分为几个子问题，这样只适合一些非常大的数，小的数反而会增加开销。

### 2.矩阵相乘

长期以来认为矩阵乘法需要工作量Ω（N^3）的。

`Strassen`算法打破了屏障，它的基本思想是把每一个矩阵都分成四块，比如两个N×N矩阵乘法，划分为8个N/2×N/2阶矩阵，这样花费依然没变，为了减少开销，我们需要把子问题简化到8个以下。最后简化到7个乘法，8个加法得到最终答案。

我们可以很容易直到矩阵加法比矩阵乘法花费小。最终`Strassen`算法性能为O（N^2.81）。

和整数相乘一样，`Strassen`算法在N不够大时不如矩阵直接相乘。而且只有有限的适用性。

# 动态规划

## 1.概念

将递归算法重新写成非递归算法，把子问题的答案系统地记录在一个表内，这种方法的一种技巧叫作动态规划。

## 2.用一个表代替递归

### 1.斐波那契数列

1. 经典递归算法

   ```
   int Fib(int n)
   {
   	if (n <= 1)
   		return 1;
   	else
   		return Fib(n - 1) + Fib(n - 2);
   }
   ```

2. 线性算法

   ```
   int fib(int n)
   {
   	if (n < 2)
   		return n;
   	int Last,NextToLast,Answer;
   	Last = NextToLast = 1;
   	for (int i = 2; i <= n; i++)
   	{
   		Answer = Last + NextToLast;
   		NextToLast = Last;
   		Last = Answer;
   	}
   	return Answer;
   }
   ```

### 2.计算一个递归关系

1. 经典递归算法

```
double Eval(int n)
{
	int i;
	double sum;
	if (n == 0)
		return 1.0;
	else
	{
		sum = 0.0;
		for (i = 0; i < n; i++)
			sum += Eval(i);
		return 2.0*sum / n + n;
	}
}
```



1. 用一个表来存储

```
double eval(int n)
{
	int i, j;
	double sum, answer;
	double *c;
	c = (double*)malloc(sizeof(double)*(n + 1));
	if (c == NULL)
		printf("Out of spcae!!!");
	c[0] = 1.0;
	for (i = 1; i <= n; i++)
	{
		sum = 0.0;
		for (j = 0; j < i; j++)
			sum += c[j];
		c[i] = 2.0*sum / i + i;
	}
	answer = c[n];
	free(c);
	return answer;
}

```

## 3.矩阵乘法的顺序安排

## 4.最优二叉查找树

Dijkstra算法提供了动态规划算法的想法：我们依序选择这些顶点。我们将只使用`v1，v2。。vk`作为中间顶点的最短路径的权

## 5.随机化算法

- 在算法期间随机数至少有一次用于决策。该算法运行时间不止依赖于特定的输入，而且依赖于所发生的随机数。
- 一个随机化算法的最坏情形运行时间几乎总是和非随机化算法的最坏情形运行时间相同。重要的区别在于，好的随机化算法没有不好的输入，而只有坏的随机数（相对于特定的输入）。
- 比如快排中枢纽元的选取，方法A是用第一个元素作为枢纽元，方法B是随机选取

### 1.随机数发生器

方法：线性同余发生器

实现：

```
#include<stdio.h>

static unsigned long Seed = 1;

#define A 48271L
#define M 2147483647L
#define Q (M/A)
#define R (M%A)
double Random(void)
{
	long TmpSeed;

	TmpSeed = A * (Seed%Q) - R * (Seed / Q);
	if (TmpSeed >= 0)
		Seed = TmpSeed;
	else
		Seed = TmpSeed + M;

	return (double) Seed / M;

}
void Initialize(unsigned long InitVal)
{
	Seed = InitVal;
}

int main()
{
	double r1, r2;
	Initialize(4528);
	r1 = Random();
	r2 = Random();
	printf("%d\n", r1);
	printf("%d\n", r2);
}
```

### 2.素性测试

```
HugeInt Witness(HugeInt a, HugeInt i, HugeInt N)
{
	HugeInt X, Y;
	if (i == 0)
		return 1;
	X = Witness(a, i / 2, N);
	if (X == 0)
		return 0;

	Y = (X*X) % N;
	if (Y == 1 && X != 1 && X != N - 1)
		return 0;

	if (i % 2 != 0)
		Y = (a*Y) % N;

	return Y;
}

int IsPrime(HugeInt N)
{
	return Witness((long)Random() % N, N - 1, N) == 1;
}

```

# 回溯算法

沿着一种方法往前走，如果走不通往回走一步，然后继续往前走，不通继续后退，最后如果可以走通即可有解，如果不通就无解。
