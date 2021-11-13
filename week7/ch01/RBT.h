#include <cstdlib>

typedef int ElementType;
struct RedBlackNode;
typedef struct RedBlackNode * RedBlackTree;
typedef RedBlackTree Position;

typedef enum ColorType
{
	Red, Black
}ColorType;

struct RedBlackNode
{
	ElementType Elememt;
	RedBlackTree left;
	RedBlackTree right;
	ColorType color;

};

void DoPrint(RedBlackTree T, int depth);

inline void PrintTree(RedBlackTree T)
{
	DoPrint(T->right, 0);
}

RedBlackTree Initialize();

//需要进行旋转的时候进行旋转，旋转之前应先进行判定
static Position Rotate(ElementType item, RedBlackTree Parent);

//两个孩子都是红色节点时，交换父亲和孩子节点的颜色，有必要的时候进行旋转
static void HandleReorient(ElementType item, RedBlackTree T);

//插入节点，如果节点已经存在，则什么也不做
RedBlackTree insert(ElementType item, RedBlackTree T);

//删除节点
RedBlackTree Delete(ElementType item, RedBlackTree T);

//右旋转
RedBlackTree rightSingleRotate(RedBlackTree T);

//左旋转
RedBlackTree leftSingleRotate(RedBlackTree k1);
