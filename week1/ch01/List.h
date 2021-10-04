#pragma once
#ifndef List.h
struct Node;
typedef struct Node *ptrToNode;
typedef ptrToNode List;
typedef ptrToNode Position;

typedef int ElementType;

List CreateList();
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void PrintList(const List L);
Position Find(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Data(Position P);

#endif // List.h

