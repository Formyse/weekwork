#include<stdio.h>

static unsigned long Seed = 1;

#define A 48271L
#define M 2147483647L
#define Q (M/A)
#define R (M%A)
double Random(void)
{
	long TmpSeed;

	TmpSeed = A * (Seed%Q) - R * (Seed / Q);
	if (TmpSeed >= 0)
		Seed = TmpSeed;
	else
		Seed = TmpSeed + M;

	return (double) Seed / M;

}
void Initialize(unsigned long InitVal)
{
	Seed = InitVal;
}

int main()
{
	double r1, r2;
	Initialize(4528);
	r1 = Random();
	r2 = Random();
	printf("%d\n", r1);
	printf("%d\n", r2);
}
