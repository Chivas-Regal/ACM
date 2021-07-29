//trajan
//A->B表示A支持B，求一个人最多被多少个人支持，并输出编号
//首先对图缩点，求每个点最多有多少个点能到达他
//可以对缩点后的图反向建边，然后对于每个入度为0的点dfs
//求它能到达的点的数量，然后记录最大值即可
//题目链接： http://acm.hdu.edu.cn/showproblem.php?pid=3639
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 6020;
const int mod = 1000000007;
int tot, sum, top, dfn[maxn], low[maxn], vis[maxn], sk[maxn];
int cnt, hd[maxn], nex[10*maxn], to[10*maxn], in[maxn], a[maxn], col[maxn];
//g存储缩点后的图，mi存储强连通分量元素的个数 
int mx, su, mi[maxn], g[maxn];
set<P> st;
void init();
void trajan(int u);
void add(int f, int t, int hd[]);
void dfs(int u);

int main()
{
	int n, m, i, j, t;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		st.clear();
		mx = -1;
		init();
		scanf("%d %d", &n, &m);
		while(m--)
		{
			scanf("%d %d", &i, &j);
			add(i, j, hd);
		}
		for(i=0;i<n;i++)
		if(!dfn[i])trajan(i);
		//对缩点后的图，反向建边，用set判重边
		//虽说其实并不用判重边 
		for(i=0;i<n;i++){
			for(j=hd[i];j!=-1;j=nex[j])
			if(col[i] != col[to[j]]){
				if(st.find(P(col[i], col[to[j]])) != st.end())continue;
				st.insert(P(col[i], col[to[j]]));
				add(col[to[j]], col[i], g);
				in[col[i]]++;
			}
		}
		//对每个入度为0的边dfs， 
		for(i=1;i<=sum;i++)
		if(!in[i]){
			memset(vis, 0, sizeof(vis));
			su = 0;
			dfs(i);
			mi[i] = su;
			mx = max(mx, mi[i]);
		}
		int kk = 0;
		printf("Case %d: %d\n", z, mx-1);
		for(i=0;i<n;i++)
		if(mi[col[i]] == mx){
			if(kk)printf(" ");
			printf("%d", i);
			kk = 1;
		}
			
		printf("\n");
	}
	return 0;
}

void init()
{
	tot = sum = top = cnt = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(hd, -1, sizeof(hd));
	memset(g, -1, sizeof(g));
	memset(in, 0, sizeof(in));
}

void dfs(int u)
{
	vis[u] = 1;
	//因为是缩点后的图，所以数量应该加上mi[u]，而非1 
	su+=mi[u];
	for(int i=g[u];i!=-1;i=nex[i])
	{
		if(!vis[to[i]])
		dfs(to[i]);
	}
}

void add(int f, int t, int hd[])
{
	to[++cnt] = t;
	nex[cnt] = hd[f];
	hd[f] = cnt;
}

void trajan(int u)
{
	dfn[u] = low[u] = ++tot;
	vis[u] = 1;
	sk[++top] = u;
	for(int i=hd[u];i!=-1;i=nex[i])
	{
		if(!dfn[to[i]]){
			trajan(to[i]);
			if(low[u] > low[to[i]])
				low[u] = low[to[i]];
		}
		else if(vis[to[i]])
			low[u] = min(low[u], dfn[to[i]]);
	}
	if(low[u] == dfn[u])
	{
		col[u] = ++sum;
		vis[u] = 0;
		mi[sum] = 1;
		while(sk[top] != u){
			mi[sum]++;
			col[sk[top]] = sum;
			vis[sk[top--]] = 0;
		}
		top--;
	}
}
