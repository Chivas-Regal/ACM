//���ۣ���Ԫ��LCM(1,2..n); 
//(n+1)*LCM(C(n,0),C(n,1)..C(n,n))=LCM(1,2,3..n);
//��������Ĳ��ͣ�������������Ϊʲô�����b�ĵ�n+1���n+1 
//��ⲩ�ͣ�https://www.cnblogs.com/liyinggang/p/5578654.html
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
//������Ĳ��� 
void init()
{
	int i, j;
	for(i=0;i<maxn-4;i++)
		prime[i] = i;
	//ɸѡ������������ 
	for(i=2;i<maxn-4;i++)
	{
		if(prime[i] == i)
			for(j=i+i;j<maxn;j+=i)
				prime[j] = i;
	}
	/*for(i=2;i<20;i++)
		printf("%d ", prime[i]);
	printf("\n");*/
	/*���������ܱ�һ����������������f[i] = f[i-1] * prime[i] % mod
	����8=2�����η���ֻ��һ��������2��LCM(1,2..8)�϶�Ҫ��
	3��2��ǰ���4�Ѿ�����2��2������ֻ���ٳ�һ��2������������*/
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
