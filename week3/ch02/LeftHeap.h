#pragma once
#ifndef LeftHeap.h
#include<stdlib.h>
#include<stdio.h>
typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PriorityQueue;
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);
void PrintTree(PriorityQueue T);
#endif // !LeftHeap.h
