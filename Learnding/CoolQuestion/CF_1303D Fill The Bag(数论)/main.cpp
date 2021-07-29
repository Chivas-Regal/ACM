/***************************************************************
数论+贪心

有一个大小为n的包，还有m个物体，每个物体的大小为ai，ai为2的k(k>=0)次幂。物体可能太大，
可以进行一次操作，将大小为ai的物体变为2个大小为ai/2的物体。求是否存在方案装满包，如果可以，求最少的操作
次数。

思路：给的ai都是2的整数次幂，考虑从这方面入手。显然如果a1+a2+a3+...+an<n时无解，否则可以填满。
那么接下来考虑最小化操作次数，首先将n分解为2^p0+2^p1+...+2^px的形式。另外统计物体中
大小为2^i的有多少个。因为ai都是2的整数次幂，所以可以将n看做是x个小包，大小分别为2^p0,2^p1...
2^px。
从小到大依次填x个包，为了最小化操作数，如果一个小包能由许多个小的物体填满，则用多个小
物体填满，如果小物体无法填满，则考虑拆分大方块。判断体积小于等于2^pi次幂的未使用物体的和
是否大于2^pi即可。如果小于，那么则考虑拆分为2^pi次幂需要操作数最小的那个物体即可。

题目链接：https://codeforces.com/problemset/problem/1303/D
*********************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 80;
const int mod = 1000000007;
int b[maxn], c[maxn], d[maxn];
LL B[maxn];
map<LL,int> mp;
void hua(LL n, int a[]);

int main()
{
	int t, m, i, j, k;
	B[0] = 1, b[0] = 0;
	mp[1] = 0;
	for(i=1;i<=60;i++)
		b[i] = i, B[i] = B[i-1]*2, mp[B[i]] = i;
	scanf("%d", &t);
	while(t--)
	{
		int ans = 0, sig = 1;
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));

		LL n, sum = 0;
		scanf("%I64d %d", &n, &m);
		for(i=0;i<m;i++){
			scanf("%d", &j);
			c[mp[(LL)j]]++;
		}
		hua(n, d);
		for(i=0;i<=60;i++)
		{
			sum += c[i] * B[i];
			if(d[i] == 1)
			{
				if(sum >= B[i]){
					sum -= B[i];
				}
				else
				{
					sig = 0;
					for(j=i+1;j<=60;j++)
						if(c[j]>0)
						{
							c[j]--;
							sig = 1;
							ans += j-i;
							sum += B[j] - B[i];
							break;
						}
				}
			}
		}
		if(sig)printf("%d\n", ans);
		else printf("-1\n");
	}
	
	return 0;
}

void hua(LL n, int a[])
{
	for(int i=60;i>=0;i--)
		if(n>=B[i]){
			n-=B[i];
			a[i]++;
		}
}