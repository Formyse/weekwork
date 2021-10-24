#include"DisjSet.h"
#include<stdio.h>

int main()
{
	DisjSet S = { 1,2,3,4,5,6,7,8 };
	Initilialize(S);
	SetUnion(S, 5, 6);
	SetUnion(S, 7, 8);
	SetUnion(S, 5, 7);
	int result=Find(8, S);
	printf("%d", result);
}
