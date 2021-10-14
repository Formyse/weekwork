#pragma once
#ifndef BinHeap.h
#include<stdlib.h>
#include<stdio.h>
typedef int ElementType;
struct HeapStruct;
typedef struct HeapStruct *PirorityQueue;
PirorityQueue Initialize(int MaxElements);
void Destory(PirorityQueue H);
void MakeEmpty(PirorityQueue H);
void Insert(ElementType X, PirorityQueue H);
ElementType DeleteMin(PirorityQueue H);
ElementType FindMin(PirorityQueue H);
int IsFull(PirorityQueue H);
int IsEmpty(PirorityQueue H);
#endif // !BinHeap.h
