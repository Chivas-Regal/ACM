//快速幂，同余模 
//需要注意的是在进行快速幂运算时，可能会爆long long，
//可以先取余再乘，也可以另写个快速加法函数 
//参考博客： 
//https://blog.csdn.net/u013486414/article/details/46237349
// http://poj.org/problem?id=1845
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
typedef long long int ll;
typedef pair<int,int> P;
const int mod = 9901;
ll Pow(int a, int b);
ll sum(ll a, ll b);
ll mul(ll a);

int main()
{
	ll a, b, ans, c[100005], d[100005];
	int i, n, num;
	while(cin>>a>>b)
	{
		ans = 1;
		num = 0;
		n = (int)sqrt(a+0.0005);
		for(i=2;i<=n;i++)
		{
			if(a % i == 0)
			{
				d[num] = i;
				c[num] = 0;
				while(a % i == 0)
				{
					c[num]++;
					a /= i;
				}
				num++;
			}
		}
		if(a != 1)
		{
			d[num] = a;
			c[num] = 1;
			num++;
		}
		for(i=0;i<num;i++)
		{
			ans = (ans%mod * sum(d[i], b*c[i])%mod)%mod;
		}
		cout<<ans<<endl;
	}
 	return 0;
}

ll Pow(int a, int b)
{
	ll n = 1;
	while(b)
	{
		if(b&1)
			n = n * a % mod;
		//printf("%lld\n", a * a); 
		a = (a % mod) * (a % mod);
		a = a % mod;
		//a = mul(a);
		b /= 2;
	}
	return n;
}

ll sum(ll a, ll b)
{
	if(b == 0)
		return 1;
	ll x = (1+Pow(a, b/2+1))%mod;
	if(b & 1)
		return (x * sum(a,b/2)%mod)%mod;
	else
		return (x * sum(a, (b-1)/2)%mod+Pow(a,b/2)%mod)%mod;
}

ll mul(ll a)
{
	ll b = a, s = 0;
	while(b)
	{
		if(b&1)
			s = (s+a)%mod;
		a = (a+a) % mod;
		b /= 2;
	}
	return s;
}
