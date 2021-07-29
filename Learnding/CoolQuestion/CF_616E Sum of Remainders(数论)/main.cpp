//数论 
//求n%1 + n%2 + n%3 + ...... + n%m
//此题关键可以想到是求n%1 + n%2 + .... + n%(min(n,m))部分
//然后可以每个可以转化为n - n/i*i;
//一直累加到m就是n*m - (n/1*1+n/2*2 + ... + n/m*m)
//可以发现括号内的有一段是等差序列，显然对于某些i可以发现n/i相等
//或者打个表吧 
//首项为n/i+i, 首项下标为i，尾项下标为min(n/(n/i), m)
//然后求和公式就好了，注意运算符的优先级问题
//题目链接： http://codeforces.com/contest/616/problem/E
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 1000000007;

int main()
{
	LL ans = 0, sum = 0, n, m, k;
	scanf("%I64d %I64d", &n, &m);
	ans = ((n%mod) * (m%mod))%mod;
	m = min(n, m);
	sum = 0;
	for(LL i=1;i<=m;){
		LL l = i, r = min(n/(n/i), m);
		LL a1 = n/i*i, d = n/i;
		//注意下优先级问题 
		if((r-l)%2 == 0)
			sum = (sum+((r-l+1)%mod * (a1 %mod)) %mod + (((((r-l)/2)%mod)*((r-l+1)%mod)%mod) * d)%mod)%mod;
		else
			sum = (sum+((r-l+1)%mod * (a1 %mod)) %mod + ((((r-l)%mod)*(((r-l+1)/2)%mod)%mod) * d)%mod)%mod;
		i = r+1;
	}
	printf("%I64d\n", ((ans-sum)%mod+mod)%mod);
	return 0;
}

