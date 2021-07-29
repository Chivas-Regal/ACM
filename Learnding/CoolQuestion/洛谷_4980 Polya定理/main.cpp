/*************************************************
polya定理
有n个珠子，形成一个环，现在需要给珠子上色，共有n种颜色，问共有多少种不同的
涂法？如果可以通过循环得到，则认为两种方案是一样的。

思路：polya定理，主要需要考虑循环节的求法。通过观察(或者分析)可以发现第i次
移动他的循环节数量是gcd(i,n)，所以需要求出1~n所有与n的gcd，显然，有点麻烦。
可以考虑枚举每个gcd，n的所有因数都是可能的gcd，因为gcd肯定需要n能整除他啊。
然后个数呢？设当前因数为d,n这边一定是n/d，则个数一定是n/d的欧拉数，因为都
除以d的情况下，另一个数一定小于等于n/d，且与n/d互质。所以sqrt(n)的复杂度
即可。

题目链接：https://www.luogu.com.cn/problem/P4980
****************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 10000100;
const int mod = 1000000007;
LL euler_phi(LL n);
LL Pow(LL a, LL b);
LL solve(int n, int m);

int main()
{
	int t, n, i, j;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		LL ans = solve(n, n);
		printf("%lld\n", ans);
	}
	return 0;
}

LL Pow(LL a, LL b)
{
	LL n = 1;
	while(b)
	{
		if(b%2)n = n*a%mod;
		a = a*a % mod;
		b /= 2;
	}
	return n;
}

LL solve(int n, int m)
{
	LL ans = 0;
	for(LL i=1;i*i<=n;i++)
	{
		if(n%i)continue;
		ans = (ans + euler_phi(i)*Pow(m, n/i))%mod;
		if(i*i != n) ans = (ans + euler_phi(n/i)*Pow(m, i))%mod;
	}
	ans = (ans * Pow(m, mod-2))%mod;
	return ans;
}

LL euler_phi(LL n)
{
	LL res = n;
	for(LL i=2;i*i<=n;i++)
	{
		if(n%i == 0)
		{
			res = res*(i-1)/i;
			while(n % i == 0)n /= i;
		}
	}
	if(n != 1)res = res*(n-1)/n;
	return res;
}