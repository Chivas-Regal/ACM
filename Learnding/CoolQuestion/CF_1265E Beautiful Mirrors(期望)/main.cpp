/**************************************************
期望
有n个镜子，每个镜子有ai/100的概率回答是，初始从1开始，如果询问镜子
回答为是，则下一天将询问第i+1个镜子，当第n个镜子回答是时，游戏结束。
如果镜子回答为否，则下一天将重新访问第1个镜子。求游戏结束的期望步数。

思路：期望题。需要求第n个物品回答为是的期望步数，则肯定需要知道它有机会
进行回答的期望步数step,然后单独考虑n，它需要100/an次才能回答为是，
两者结合考虑，就能得出第n步回答为是的期望步数为(step+1)*100/an。
(至于为什么+1，当然是因为它自己回答的这一步本身也是需要计算的啊)。
同理，也可以得到第i个回答为是的期望步数，从1推到n就好了。

题目链接：https://codeforces.com/problemset/problem/1265/E
*****************************************************/
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 998244353;
int a[maxn];
LL Pow(LL a, LL b);

int main()
{
	int n, i, j;
	LL ans = 0;
	scanf("%d", &n);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		//求单独考虑i,它回答是的期望步数
		LL p = 100*Pow(a[i], mod-2)%mod;
		ans = (ans + 1)*p%mod;
	}
	printf("%lld\n", ans);	
	return 0;
}

LL Pow(LL a, LL b)
{
	LL n=1;
	while(b)
	{
		if(b%2)n = n*a%mod;
		a = a*a % mod;
		b /= 2;
	}
	return n;
}