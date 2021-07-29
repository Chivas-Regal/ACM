#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
	int N, i;
	long long int a[50020], b[50020]={0}, max1 = 0;
	scanf("%d", &N);
	for(i=0;i<N;i++)
	{
		scanf("%lld", &a[i]);
		max1 = max(max1, a[i]);
	 } 
	if(max1 == 0)
		printf("0\n");
	else
	{
		b[0] = a[0];
		max1 = b[0];
		for(i=1;i<N;i++)
		{
			if(b[i-1] > 0)
				b[i] = b[i-1] + a[i];
			else
				b[i] = a[i];
			if(b[i] > max1)
				max1 = b[i];
		} 
		for(i=0;i<N;i++)
		{
			printf("%lld ", b[i]);
		} 
		printf("%lld\n", max1);
	}
	return 0;
 } 
