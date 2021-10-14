## 1.二叉堆

### 1.结构性质

- 堆是一棵完全二叉树
- 完全二叉树的高为`[logN]`

### 2.堆序性质

- 使操作快速执行的性质是堆序性
- 最小元是根节点

### 3.基本堆操作

1. Initialize初始化

   - 动态分配内存

   ```
   PirorityQueue Initialize(int MaxElements)
   {
   	PirorityQueue H;
   	H=(HeapStruct*)malloc(sizeof(struct HeapStruct));
   	if (H == NULL)
   		printf("Out of space");
   	H->Elements=(ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
   	if (H->Elements == NULL)
   		printf("Out of space");
   	H->Capacity = MaxElements;
   	H->Size = 0;
   	H->Elements[0] = MinData;
   
   	return H;
   }
   ```

   

2. Insert插入操作

   - 策略为**上滤**

     

```
void Insert(ElementType X, PirorityQueue H)
{
	int i;
	if (IsFull(H))
	{
		printf("Pirority is Full");
		return;
	}
	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
	
}
```

3.`DeleteMin`删除最小元

- 找到最小元容易，删除它不容易

- 删除最小元后根处产生空穴，因此策略为**下滤**

  ```
  ElementType DeleteMin(PirorityQueue H)
  {
  	int i, Child;
  	ElementType MinElement, LastElement;
  	if (IsEmpty(H))
  	{
  		printf("Pirority Queue is empty");
  		return H->Elements[0];
  	}
  	MinElement = H->Elements[1];
  	LastElement = H->Elements[H->Size--];
  	for (i = 1; i * 2 <= H->Size; i = Child)
  	{
  		Child = i * 2;
  		if (Child != H->Size && H->Elements[Child + 1]
  			< H->Elements[Child])
  			Child++;
  
  		if (LastElement > H->Elements[Child])
  			H->Elements[i] = H->Elements[Child];
  		else
  			break;
  	}
  	H->Elements[i] = LastElement;
  	return MinElement;
  }
  ```

  

4.其他操作

```
ElementType FindMin(PirorityQueue H)
{
	if (!IsEmpty(H))
		return H->Elements[1];
	printf("Priority Queue is Empty");
	return H->Elements[0];
}
void Destory(PirorityQueue H)
{
	free(H->Elements);
	free(H);
}
void MakeEmpty(PirorityQueue H)
{
	H->Size = 0;
}
int IsFull(PirorityQueue H)
{
	return H->Size == H->Capacity;
}
int IsEmpty(PirorityQueue H)
{
	return H->Size == NULL;
}
```

## 2.`d`-堆

- d堆是一种类似二叉堆的堆，即就是二叉堆为2-堆，d-堆则为每个节点右d个儿子，因此d-堆要比二叉堆浅的多，但是`DeleteMin`操作要更慢一些。
- 除不能执行Find外，堆的实现最明显的缺点就是：将两个堆合并为一个堆是一件复杂的操作。这种操作叫做合并（Merge）

## 3.左式堆

### 1.性质

- 对于堆中的每一个节点X，左儿子的零路径长至少与右儿子的零路径长一样大。
- 在右路径上有r个节点的左式树必然至少有2^r -1个节点。

### 2.操作

- #### 合并：比较两个堆根值大小，然后将具有大的根值的堆与具有小的根值的堆的右子堆合并，然后再将左子堆与之合并。

- #### 合并之后的根的右子树是左式的，左子树也是左式的，但是整个堆不是左式的，因此需要调整根节点，交换根的左右子树即可，并且更新`Npl`（零路径长）

### 3.实现

1. 左式堆合并操作：

   ```
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
   void switchChildren(PriorityQueue H)
   {
   	if (H == NULL)
   		return;
   
   	PriorityQueue temp;
   	temp = H->Right;
   	H->Right = H->Left;
   	H->Left = temp;
   }
   ```

   

2. 左式堆插入操作，可以看作是一种特殊的合并操作，即就是一个节点和一个大堆的合并。

   ```
   PriorityQueue Insert1(ElementType X, PriorityQueue H)
   {
   	PriorityQueue newone = (PriorityQueue)malloc(sizeof(TreeNode));
   	newone->Element = X;
   	newone->Left = newone->Right = NULL;
   	newone->Npl = 0;
   	H = Merge(H, newone);
   	return H;
   }
   ```

   

3. 左式堆的删除最小值操作：

   ```
   PriorityQueue DeleteMin1(PriorityQueue H)
   {
   	if (H == NULL)
   		return H;
   	PriorityQueue Leftchild, Rightchild;
   	Leftchild = H->Left;
   	Rightchild = H->Right;
   	free(H);
   	return Merge(Leftchild, Rightchild);//删除后需要合并操作返回一个左式堆
   }
   ```

   

4. 左式堆的查找最小值操作：

```
ElementType FindMin(PriorityQueue H)
{
	return H->Element;//根即为最小
}
```

### 4.斜堆与左式堆的区别：

1. 斜堆是左式堆的自调节形式，左式堆和斜堆的关系类似于伸展树和`AVL`树的关系。斜堆具有堆序的性质，但是没有结构的限制，这样的话一次操作最坏的情况是O（n），但是连续m次操作总的复杂度`O（mlogn）`
2. 如果一个空斜堆与一个非空斜堆合并，返回非空斜堆。
3. 如果两个斜堆都非空，那么比较两个根节点，取较小堆的根节点。将“较小堆的根节点的右孩子”和“较大堆”进行合并。
4. **合并交换新堆根节点的左孩子和右孩子。**（与左式堆合并最大区别，没有了零距离概念）

## 4.二项队列

### 1.概念

二项队列不同于我们已经看到的所有优先队列的实现之处在于，一个二项队列不是一棵堆序的树，而是堆序树的集合，称为森林。

### 2.操作

主要操作是**合并**

**合并与插入操作看课本例子即可，很好理解**

- 2个`B0`树合成`B1`树
- 2个`B1`树合成`B2`树
- 剩下同理

### 3.实现

1. 二项队列编码之前，要明白如何表示二项队列。因为二项队列的根节点所指向的节点可能是无限的，所以不能像二叉树那样使用两个指针来指向两个儿子。

2. 每个树节点有三个元素，`Element，Leftchild，NextSibling.`

3. `NextSibling`指的是和它本身同级的兄弟

4. `Leftchild`指向的是有最多孩子的节点

5. 操作实现

   ```
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
   
   ```

   

