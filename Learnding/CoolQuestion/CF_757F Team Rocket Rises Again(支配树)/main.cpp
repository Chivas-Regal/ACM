//支配树
//首先对图进行dfs序，重新编号；然后按照编号顺序
//从大到小求各点(不包括dfs树的根点)的半必经点 
//然后通过各点的半必经点求其支配点 
//要注意结点原编号和dfs后的编号的区别 
//参考博客：https://blog.csdn.net/a710128/article/details/49913553 
//参考博客：https://blog.csdn.net/wmdcstdio/article/details/49868575
//题目链接：http://codeforces.com/problemset/problem/757/F 
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
#define dbg printf("...............\n");
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 400200;
const int mod = 100001;
//fa:dfs序上点的父结点，semi：编号最小半必经点
//idom：最近必经点      dom：支配树 
int cnt, fa[maxn], semi[maxn], idom[maxn], dom[maxn];
//a,mi:带权并查集所需数组，dfn：dfs序编号 rk：编号对应原结点 
int a[maxn], mi[maxn], dfn[maxn], rk[maxn];
int tot, g[maxn], rg[maxn], nex[maxn*12], to[maxn*12];
int ans, tt, n, pre[maxn*6], hd[maxn*6], siz[maxn];
LL dis[maxn];
struct node{
	int to, p, nex;
}gs[maxn*6];
void init(int n);
int Find(int x);
void dfs(int p, int u);
void lengauer_trajan(int n);
void add(int h[], int f, int t);
void add1(int i, int j, int k);
void dijkstra(int u);
void getsize(int fa, int u);

int main()
{
    int m, s, i, j, k;
    scanf("%d %d %d", &n, &m, &s);
    init(n);
    while(m--){
    	scanf("%d %d %d", &i, &j, &k);
    	add1(i, j, k), add1(j, i, k);
	}
	dijkstra(s);
	memset(g, 0, sizeof(g));
	for(i=1;i<=n;i++){
		//printf("pre:%d\n", pre[i]);
		for(j=pre[i];j;j=nex[j]){
			add(g, i, to[j]);
			add(rg, to[j], i);
			//printf("%d %d\n", to[j], i);
		}
	}
	dfs(s, s);
	lengauer_trajan(cnt);
	getsize(s, s);
	printf("%d\n", ans);
    return 0;
}

void add1(int i, int j, int k)
{
	gs[++tt].p = k;
	gs[tt].to = j;
	gs[tt].nex = hd[i];
	hd[i] = tt;
}

void dijkstra(int u)
{
	for(int i=0;i<=n;i++)
		dis[i] = (LL)1e17, g[i] = 0;
	dis[u] = 0;
	priority_queue<P,vector<P>, greater<P> > que;
	que.push(P(0, u));
	while(!que.empty())
	{
		P p = que.top();que.pop();
		if(dis[p.second]< p.first || g[p.second])continue;
		g[p.second] = 1;
		for(int i=hd[p.second];i;i=gs[i].nex){
			if(p.first + gs[i].p < dis[gs[i].to]){
				dis[gs[i].to] = p.first+gs[i].p;
				pre[gs[i].to] = 0;
				add(pre, gs[i].to, p.second);
				que.push(P(dis[gs[i].to], gs[i].to));
			}
			else if(p.first + gs[i].p == dis[gs[i].to])
				add(pre, gs[i].to, p.second);
		}
	}
}

void init(int n)
{
	for(int i=0;i<=n;i++){
		a[i] = mi[i] = semi[i] = idom[i] = i;
		g[i] = rg[i] = dfn[i] = hd[i] = dom[i] = 0;
	}
	ans = cnt = tot = tt = 0;
}

void add(int h[], int f, int t)
{
	to[++tot] = t;
	nex[tot] = h[f];
	h[f] = tot;
}

int Find(int x)
{
	if(x == a[x])return x;
	int fa=a[x], y = Find(a[x]);
	if(dfn[semi[mi[x]]] > dfn[semi[mi[fa]]])mi[x] = mi[fa];
	return a[x] = y;
}

void dfs(int p, int u)
{
	fa[u] = p;
	dfn[u] = ++cnt;
	rk[cnt] = u;
	for(int i=rg[u];i;i=nex[i]){
		if(!dfn[to[i]])
			dfs(u, to[i]);
	}
}
//n为当前这个连通图的结点数量 
void lengauer_trajan(int n)
{
	for(int i=n;i>=2;i--)
	{
		//访问所有能到达y结点的边
		int y = rk[i], tmp = n;
		for(int j=g[y];j;j=nex[j])
		{
			int v = to[j];
			//这句我也不知道为啥，反正加不加好像都一样 
			if(!dfn[v])continue;
			//如果dfn[v]<dfn[y]则v是y的一个半必经点 
			if(dfn[v] < dfn[y])tmp = min(tmp, dfn[v]);
			//如果dfn[v]>dfn[y],
			else Find(v), tmp = min(tmp, dfn[semi[mi[v]]]);
		}
		semi[y] = rk[tmp];
		a[y] = fa[y];
		//在原图添加一条semi[y]->y的边 
		add(rg, semi[y], y);
		//我们求出深搜树后，考虑原图中所有非树边（即不在树上的边），我们将这些边删掉，
		//加入一些新的边 {(semi[w],w)|w∈V{(semi[w],w)|w∈V andand w≠r}w≠r}，我们会
		//发现构建出的新图中每一个点的支配点是不变的，
		//通过这样的改造我们使得原图变成了DAG
		y = rk[i-1];
		for(int j=rg[y];j;j=nex[j]){
			int v = to[j];
			Find(v);
			if(semi[mi[v]] == y)idom[v] = y;
			else idom[v] = mi[v];
		}
	}
	//构造支配树
	for(int i=2;i<=n;i++){
		int id = rk[i];
		if(idom[id] != semi[id])
			idom[id] = idom[idom[id]];
		add(dom, idom[id], id);
	}
}

void getsize(int fa, int u)
{
	siz[u] = 1;
	for(int i=dom[u];i;i=nex[i]){
		if(to[i] != fa){
			getsize(u, to[i]);
			siz[u] += siz[to[i]];
		}
	}
	if(fa != u)
		ans = max(ans, siz[u]);
}
