//数论：逆元，LCM(1,2..n); 
//(n+1)*LCM(C(n,0),C(n,1)..C(n,n))=LCM(1,2,3..n);
//参照下面的博客，不过不懂的是为什么到最后b的第n+1项除n+1 
//题解博客：https://www.cnblogs.com/liyinggang/p/5578654.html
//http://acm.hdu.edu.cn/showproblem.php?pid=5407
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>
#include <queue>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
const ll mod = 1e9+7;
const ll maxn = 1000010;
ll prime[maxn], f[maxn];
bool isone(ll n);
void init();
ll Pow(ll a, ll b);

int main()
{
	init();
	int t, n;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%lld\n", f[n+1]*Pow(n+1, mod-2)%mod);
	}
	return 0;
}
//代码核心部分 
void init()
{
	int i, j;
	for(i=0;i<maxn-4;i++)
		prime[i] = i;
	//筛选出最大的素因数 
	for(i=2;i<maxn-4;i++)
	{
		if(prime[i] == i)
			for(j=i+i;j<maxn;j+=i)
				prime[j] = i;
	}
	/*for(i=2;i<20;i++)
		printf("%d ", prime[i]);
	printf("\n");*/
	/*如果这个数能被一个素因数整除，则f[i] = f[i-1] * prime[i] % mod
	比如8=2的三次方，只有一个素因数2。LCM(1,2..8)肯定要乘
	3个2，前面的4已经乘了2个2，现在只需再乘一个2，其他的类推*/
	f[1] = 1;
	for(i=2;i<maxn-4;i++)
	{
		if(isone(i))
			f[i] = f[i-1] * prime[i] % mod;
		else
			f[i] = f[i-1]; 
	}
	/*for(i=2;i<20;i++)
		printf("%d ", f[i]);*/
}

bool isone(ll n)
{
	ll t = prime[n];
	while(n % t == 0)
		n /= t;
	if(n == 1)return true;
	else return false;
}

ll Pow(ll a, ll b)
{
	ll n = 1;
	while(b>0)
	{
		if(b%2)n = n * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return n;
}
