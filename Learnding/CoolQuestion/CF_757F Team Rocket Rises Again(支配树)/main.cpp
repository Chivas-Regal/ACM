//֧����
//���ȶ�ͼ����dfs�����±�ţ�Ȼ���ձ��˳��
//�Ӵ�С�����(������dfs���ĸ���)�İ�ؾ��� 
//Ȼ��ͨ������İ�ؾ�������֧��� 
//Ҫע����ԭ��ź�dfs��ı�ŵ����� 
//�ο����ͣ�https://blog.csdn.net/a710128/article/details/49913553 
//�ο����ͣ�https://blog.csdn.net/wmdcstdio/article/details/49868575
//��Ŀ���ӣ�http://codeforces.com/problemset/problem/757/F 
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
//fa:dfs���ϵ�ĸ���㣬semi�������С��ؾ���
//idom������ؾ���      dom��֧���� 
int cnt, fa[maxn], semi[maxn], idom[maxn], dom[maxn];
//a,mi:��Ȩ���鼯�������飬dfn��dfs���� rk����Ŷ�Ӧԭ��� 
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
//nΪ��ǰ�����ͨͼ�Ľ������ 
void lengauer_trajan(int n)
{
	for(int i=n;i>=2;i--)
	{
		//���������ܵ���y���ı�
		int y = rk[i], tmp = n;
		for(int j=g[y];j;j=nex[j])
		{
			int v = to[j];
			//�����Ҳ��֪��Ϊɶ�������Ӳ��Ӻ���һ�� 
			if(!dfn[v])continue;
			//���dfn[v]<dfn[y]��v��y��һ����ؾ��� 
			if(dfn[v] < dfn[y])tmp = min(tmp, dfn[v]);
			//���dfn[v]>dfn[y],
			else Find(v), tmp = min(tmp, dfn[semi[mi[v]]]);
		}
		semi[y] = rk[tmp];
		a[y] = fa[y];
		//��ԭͼ���һ��semi[y]->y�ı� 
		add(rg, semi[y], y);
		//��������������󣬿���ԭͼ�����з����ߣ����������ϵıߣ������ǽ���Щ��ɾ����
		//����һЩ�µı� {(semi[w],w)|w��V{(semi[w],w)|w��V andand w��r}w��r}�����ǻ�
		//���ֹ���������ͼ��ÿһ�����֧����ǲ���ģ�
		//ͨ�������ĸ�������ʹ��ԭͼ�����DAG
		y = rk[i-1];
		for(int j=rg[y];j;j=nex[j]){
			int v = to[j];
			Find(v);
			if(semi[mi[v]] == y)idom[v] = y;
			else idom[v] = mi[v];
		}
	}
	//����֧����
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
