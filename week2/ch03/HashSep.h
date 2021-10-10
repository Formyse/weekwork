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
