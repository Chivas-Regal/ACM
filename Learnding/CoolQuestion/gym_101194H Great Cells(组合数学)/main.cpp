/******************************************** 
组合数学+思路
有一个n*m的矩阵，每个位置的数可能为[1,k],定义great cell为
一个数比如所在行和列的所有其他数都大。定义Ag为矩阵
中共有g个great cell数的方案数。求A0*1+A1*2+A2*3+...+An*m*(n*m+1)
题解： 首先可能会考虑求Ai每个有多少个，然后利用上面的式子进行
计算，但发现很难great all较多的时候，计算数量会很麻烦，分析
目标式，可以发现对于每种矩阵，无论有无great cell，都会对
答案贡献1，然后对于每个greater cell都会对答案贡献1次，如果一个
矩阵有g个great cell，则此矩阵可以贡献g个1(将这个矩阵重复计算g次)。
所以可以考虑枚举每个位置为great cell，此位置可以为[1,k]，
则great cell的位置有n*m种情况，当当前位置为i时，同行同列的其余
位置可以为[1,i-1]，其余位置可以为[1,k]种，所以共有
n*m*((i-1)^(n+m-2))*(k^(n*m-n-m+1))个。同时加上不计算great cell
有的k^(n*m)即可。
PS：说是组合数学，其实更多的是思路 
题目链接：https://codeforces.com/gym/101194 
*******************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator> 
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300100;
const int mod = 1000000007;
LL Pow(LL a, LL b);

int main()
{
	int t, n, m, i, j, k;
	LL ans;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d %d", &n, &m, &k); 
		ans = Pow(k, n*m);
		for(i=1;i<=k;i++)
		{
			LL tmp = (n*m*Pow(i-1, n+m-2)%mod)*Pow(k, n*m-(n+m-1))%mod;
			ans = (ans + tmp)%mod;
		 } 
		 printf("Case #%d: %lld\n", z, ans);
	}
	return 0;
}

LL Pow(LL a, LL b)
{
	LL n = 1;
	while(b)
	{
		if(b%2)n=n*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return n;
}
