/*********************************************************
树链剖分
有一个n个点n条边的无向连通图，每次可以修改一条边的权值或者询问两点间的
最短距离。给出每个询问的答案。

思路：n个点n条边的无向连通图，则一定会有n-1条边组成一棵树，另一条边单独记录处理。对于任意两点(s,t)之间的最短距离，一定是从树上走那条唯一路径，或者经过单独
记录的那条边。设多余的那条边两点为(gu,gv),边权为w，则任意两点的路径可以是直接走树上，或者其中一点走到gu,另一点走到gv,在走(gu,gv)这条边。
所以求min(dis(s,t), dis(s,gu)+w+dis(gv, t), dis(s, gv)+w+dis(gu, t))即可
题目链接：https://www.luogu.com.cn/problem/P4949
************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100200;
const int mod = 998244353;
struct node{
	int to, w;
	node(){}
	node(int a, int b):to(a),w(b){}
};
int dep[maxn], son[maxn], top[maxn], siz[maxn], fa[maxn];
int n, num, gu, gv, gw, id[maxn], a[maxn],b[maxn];
int fr[maxn], to[maxn], w[maxn];
LL p[4*maxn];
vector<node> g[maxn];
int Find(int x);
LL solve(int u, int v);
void dfs2(int u, int root);
void dfs1(int u, int f, int de);
void creat(int l, int r, int k);
void Update(int l, int r, int x, int y, int k);
LL query(int l, int r, int al, int ar, int k);

int main()
{
	int m, i, j, k, f, r, W;
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++)a[i] = i;
	//并查集求多余的那条边
	for(i=1;i<=n;i++)
	{
		scanf("%d %d %d", &f, &r, &W);
		fr[i] = f, to[i] = r, w[i] = W;
		int x = Find(f), y = Find(r);
		if(x == y)gu = f, gv = r, gw = W;
		else{
			a[x] = y;
			g[f].push_back(node(r, W));
			g[r].push_back(node(f, W));
		} 
	}
	num = 1;
	//重链剖分
	dfs1(1, 1, 1);
	b[id[1]] = 0;
	dfs2(1, 1);
	//线段树维护边权信息
	creat(1, n, 1);
	while(m--)
	{
		int op;
		scanf("%d %d %d", &op, &f, &r);
		if(op == 1)
		{
			if(fr[f] == gu  && to[f] == gv)gw = r;
			else if(dep[fr[f]] > dep[to[f]])
				Update(1, n, id[fr[f]], r, 1);
			else 
				Update(1, n, id[to[f]], r, 1);
		}	
		else
		{
			LL ans = solve(f, r);
			ans = min(ans, gw+solve(f, gu)+solve(r, gv));
			ans = min(ans, gw+solve(f, gv)+solve(r, gu));
			printf("%lld\n", ans);
		}
	}
	return 0;
}

int Find(int x)
{
	return a[x] = x==a[x]?x:Find(a[x]);
}

void dfs1(int u, int f, int de)
{
	dep[u] = de;
	fa[u] = f;
	siz[u] = 1;
	son[u] = 0;
	for(int i=0;i<g[u].size();i++)
	{
		int v = g[u][i].to;
		if(v != f)
		{
			dfs1(v, u, de+1);
			siz[u] += siz[v];
			if(son[u] == 0 || siz[v] > siz[son[u]])
				son[u] = v;
		}
	}
}

void dfs2(int u, int root)
{
	top[u] = root;
	id[u] = num++;
	if(son[u])
		dfs2(son[u], root);
	for(int i=0;i<g[u].size();i++)
		if(g[u][i].to != fa[u])
		{
			int v = g[u][i].to;
			if(v != son[u])dfs2(v, v);
			b[id[v]] = g[u][i].w;
		}
}

void creat(int l, int r, int k)
{
	if(l == r){
		p[k] = b[l];return ;
	}
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
	p[k] = p[2*k]+p[2*k+1];
}

void Update(int l, int r, int x, int y, int k)
{
	if(l == r){
		p[k] = y;
		return ;
	}
	int mid = (l+r)/2;
	if(x <= mid)Update(l, mid, x, y, 2*k);
	else Update(mid+1, r, x, y, 2*k+1);
	p[k] = p[2*k] + p[2*k+1];
}

LL query(int l, int r, int al, int ar, int k)
{
	if(al > ar)return 0;
	if(l == al && r == ar)
		return p[k];
	int mid = (l+r)/2;
	if(ar <= mid)return query(l, mid, al, ar, 2*k);
	else if(al > mid)return query(mid+1, r, al, ar, 2*k+1);
	else return query(l, mid, al, mid, 2*k)+
				query(mid+1, r, mid+1, ar, 2*k+1);
}
//求树上u到v的距离
LL solve(int u, int v)
{
	LL res = 0;
	while(top[u] != top[v])
	{
		if(dep[top[u]] > dep[top[v]])
		{
			res += query(1, n, id[top[u]], id[u], 1);
			u = fa[top[u]];
		}
		else
		{
			res += query(1, n, id[top[v]], id[v], 1);
			v = fa[top[v]];
		}
	}
	if(dep[u] < dep[v])
		res += query(1, n, id[u]+1, id[v], 1);
	else 
		res += query(1, n, id[v]+1, id[u], 1);
	return res;
}