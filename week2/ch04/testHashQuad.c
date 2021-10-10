#include "HashQuad.h"    

int main()
{
	HashTable H = InitializeTable(10);
	printf("Hash Table: \n");
	Insert(9, H);
	Insert(19, H);
	Insert(20, H);
	Insert(63, H);
	Insert(75, H);
	Position P1 = Find(9, H);
	Position P2 = Find(19, H);
	Position P3 = Find(20, H);
	Position P4 = Find(63, H);
	Position P5 = Find(75, H);
	printf("%d:%d\n",9, P1);
	printf("%d:%d\n", 19, P2);
	printf("%d:%d\n", 20, P3);
	printf("%d:%d\n", 63, P4);
	printf("%d:%d\n", 75, P5);
	return 0;
}
