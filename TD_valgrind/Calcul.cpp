#include "Calcul.h"
#include <assert.h>

int intAdd (const int a, const int b)
{
	return a+b;
}

int intMul (const int a, const int b)
{
	return a*b;
}

int intDiv (const int a, const int b)
{
	assert( b!=0 );
	return ((int)(a/b));
}

int intFactoriel (const int n)
{
	if (n<=0) return 0;
	else if (n==1) return 1;
	else return intMul(n,intFactoriel(intAdd(n,-1)));
}
