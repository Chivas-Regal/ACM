/***************************************************
KM算法
有n个公司和m个工程，公司i负责工程j的效率为a[i][j]，每个公司只能负责
一个工程，每个工程只能分给一个公司，现在已有一个分配方案，求重新分配后
效率最多提高多少，且尽量少更改原匹配

思路：对于每一条边，将其权值乘以n+1,对于原匹配边，在此基础上边权再加1，
然后求最大匹配，将其除以n+1,就是最大匹配。将所有边按上述方法处理后，
当最大匹配确定时，会优先取原匹配边，因为原匹配边的权值更大。即使选了所有
的原边，也不会对最大匹配产生影响，因为n条原边，n/(n+1)=0，这也是为什么
前面所有边的权值都乘n+1了。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=2853
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
const int maxn = 56;
const int mod = 2009;
int n, m, a[maxn][maxn], px[maxn], py[maxn], cx[maxn], cy[maxn];
int ux[maxn], uy[maxn], slack[maxn], b[maxn];
int km();
bool Find(int x);

int main()
{
	int i, j, k, ks, sum1, sum2;
	while(~scanf("%d %d", &n, &m))
	{
		sum1 = sum2 = 0;
		ks = n+1;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				scanf("%d", &a[i][j]);
				a[i][j] *= ks;
			}
		for(i=1;i<=n;i++){
			scanf("%d", &b[i]);
			a[i][b[i]]++;
			sum1 += a[i][b[i]];
		}
		int ans = km();
		for(i=1;i<=n;i++)
			if(px[i] != b[i])sum2++;
		printf("%d %d\n", sum2, (ans/ks)-(sum1/ks));
	}
	return 0;
}

int km()
{
	memset(cy, 0, sizeof(cy));
	memset(px, 0, sizeof(px));
	memset(py, 0, sizeof(py));
	int i, j, k, ans;
	for(i=1;i<=n;i++){
		int d = 0;
		for(j=1;j<=m;j++){
			if(a[i][j] == INF)continue;
			d = max(d, a[i][j]);
		}
		cx[i] = d;
		px[i] = 0;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
			slack[j] = INF;
		while(1)
		{
			int d = INF;
			memset(ux, 0, sizeof(ux));
			memset(uy, 0, sizeof(uy));
			if(Find(i))break;
			for(j=1;j<=m;j++)
				if(!uy[j] && d >slack[j])
					d = slack[j];
			if(d == INF)return -1;
			for(j=1;j<=n;j++)
				if(ux[j])cx[j] -= d;
			for(j=1;j<=m;j++)
				if(uy[j])cy[j] += d;
				else slack[j] -= d;
		}
	}
	ans = 0;
	for(i=1;i<=n;i++)
		ans += a[i][px[i]];
	return ans;
}

bool Find(int x)
{
	ux[x] = 1;
	for(int i=1;i<=m;i++)
	{
		if(!uy[i] && a[x][i] != INF)
		{
			int t = cx[x] + cy[i] - a[x][i];
			if(t == 0)
			{
				uy[i] = 1;
				if(py[i] == 0 || Find(py[i]))
				{
					px[x] = i;
					py[i] = x;
					return true;
				}
			}
			else if(t>0)
				slack[i] = min(slack[i], t);
		}
	}
	return false;
}