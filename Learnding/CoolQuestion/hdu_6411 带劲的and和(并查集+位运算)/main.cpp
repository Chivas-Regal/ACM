/***********************************************
并查集+位运算
有一个点带权的无向图，定义f(i,j)，如果存在i到j的路径，
则f(i,j)=1,否则f(i,j)=0.求对于所有的点对(i,j)，
f(i,j)*max(vi,vj)*(vi&vj)的和。

思路：对于答案有贡献的，只有在同一个联通块的两个点才会对答案有
贡献，所有可以先求出联通块。对于同一个联通块内的点，如果暴力，n*n是会
超时的。分析公式最后的vi&vj，当vi和vj的二进制对应的位都为1时，vi&vj
对应位才为1，所以可以将vi,vj，拆分成2^a1+2^a2+...+2^ai的形式，对
每一部分单独计算。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6411
*************************************************/
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
const int maxn = 100100;
const int mod = 1000000007;
int vis[maxn], a[maxn], v[maxn], col[maxn], sum[50];
LL val[40];
vector<int> g[maxn];
int Find(int x);

int main()
{
	int t, n, m, i, j, k;
	LL ans;
	val[0] = 1;
	for(i=1;i<=30;i++)
		val[i] = (val[i-1]*2)%mod;
	scanf("%d", &t);
	while(t--)
	{
		int num = 1;
		ans = 0;
		scanf("%d %d", &n, &m);
		for(i=1;i<=n;i++){
			scanf("%d", &v[i]);
			a[i] = i, col[i] = -1;
			g[i].clear();
		}
		//并查集，求联通块
		while(m--){
			scanf("%d %d", &i, &j);
			int x = Find(i), y = Find(j);
			if(x != y)a[x] = y;
		}
		for(i=1;i<=n;i++){
			a[i] = Find(i);
			if(col[a[i]] == -1)col[a[i]]=num++;
			g[col[a[i]]].push_back(v[i]);
		}
		for(i=1;i<num;i++){
			memset(sum, 0, sizeof(sum));
			sort(g[i].begin(), g[i].end());
			for(j=0;j<30;j++)
				if(g[i][0] & (1<<j))
					sum[j]++;
			//计算当g[i][j]为最大值时，对答案的贡献
			for(j=1;j<g[i].size();j++){
				for(k=0;k<30;k++)
					if(g[i][j] & (1<<k)){
						ans += (val[k]*sum[k]%mod) * g[i][j]%mod;
						ans %= mod;
						sum[k]++;
					}
						
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

int Find(int x)
{
	return a[x]=x==a[x]?x:Find(a[x]);
}