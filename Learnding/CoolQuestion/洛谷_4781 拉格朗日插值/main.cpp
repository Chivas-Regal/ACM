//拉格朗日插值
//已知n个点可以唯一确定一个函数
//求该函数在值为k时的值
//可以通过前缀后缀的方式来优化
//题目链接： https://www.luogu.org/problemnew/show/P4781
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 100000000

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 2020;
const LL mod = 998244353;
LL Pow(LL a, LL b);

int main()
{
	int n, i, j;
	LL ans = 0, k, x[maxn], y[maxn];
	scanf("%d %lld", &n, &k);
	//函数上的n个点坐标 
	for(i=1;i<=n;i++)
		scanf("%lld %lld", &x[i], &y[i]);
	/*预处理快速求分子，然而没啥用，时间根本没少
	LL bf[maxn], ed[maxn];
	bf[0] = ed[n+1] = 1;
	for(i=1;i<=n;i++)
		bf[i] = (bf[i-1]*(k-x[i]+mod))%mod;
	for(i=n;i>=1;i--)
		ed[i] = (ed[i+1]*(k-x[i]+mod))%mod;*/
	for(i=1;i<=n;i++)
	{
		LL up, down;
		down = 1;
		up = (bf[i-1]*ed[i+1])%mod;
		for(j=1;j<=n;j++){
			if(i == j)continue;
			up = up * (k-x[j]+mod) % mod;
			down = down * (x[i]-x[j]+mod) % mod;
		}
		LL lei = (y[i] * up % mod)*Pow(down, mod-2)%mod;
		ans = (ans + lei) % mod;
	}
	printf("%lld\n", ans);
	return 0;
 }
 
LL Pow(LL a, LL b)
{
	LL n=1;
	while(b){
		if(b%2)n = n*a % mod;
		a = a*a % mod;
		b /= 2;
	}
	return n;
}
