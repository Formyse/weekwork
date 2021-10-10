#pragma once
#ifndef HashQuad.h
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int Index;
typedef Index Position;
typedef int ElementType;
struct HashTbl;
typedef struct HashTbl *HashTable;

typedef struct HashEntry Cell;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable ReHash(HashTable H);
Index Hash(ElementType Key, int TableSize);
#endif // !HashQuad.h
