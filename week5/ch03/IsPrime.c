#include<stdio.h>
#define HugeInt long
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

	return (double)Seed / M;

}
void Initialize(unsigned long InitVal)
{
	Seed = InitVal;
}
HugeInt Witness(HugeInt a, HugeInt i, HugeInt N)
{
	HugeInt X, Y;
	if (i == 0)
		return 1;
	X = Witness(a, i / 2, N);
	if (X == 0)
		return 0;

	Y = (X*X) % N;
	if (Y == 1 && X != 1 && X != N - 1)
		return 0;

	if (i % 2 != 0)
		Y = (a*Y) % N;

	return Y;
}

int IsPrime(HugeInt N)
{
	return Witness((long)Random() % N, N - 1, N) == 1;
}

int main()
{
	Initialize(548932);
	int result = IsPrime(3);
	for (int i = 0; i < 50; i++)
	{
	printf("%d\n", result);

	}
}
