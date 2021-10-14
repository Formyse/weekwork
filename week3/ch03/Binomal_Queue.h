#pragma once
#ifndef Binomal_Queue.h
#include<stdlib.h>
#include<stdio.h>
typedef int ElementType;
struct BinNode;
struct Collection;

typedef struct Collection * BinQueue;
typedef struct BinNode * Position;
typedef struct BinNode * BinTree;
#define MaxSize 30
#define Capacity 255

BinQueue initialize();
bool isEmpty(BinQueue H);
bool isFUll(BinQueue H);
void insert(ElementType X, BinQueue H);
int findMin(BinQueue H);
void destroy(BinQueue H);
BinQueue merge(BinQueue H1, BinQueue H2);
ElementType DeleteMin(BinQueue H);

#endif // !Binomal_Queue.h
