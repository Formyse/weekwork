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

