//lca+树上差分
//有一棵树，现有m条新加的边，问共有多少种方法拆一条
//原树上的边和一条新加的边，使图不连通。 
//思路：对于每条原边，如果拆除此条原边，如果原边并不能 
//被其他新加的边所代替，则有m种方案(拆除原边就已经不连通，
//剩下一条新边可以删除任意一条);
//如果原边被覆盖一次，那拆除覆盖原边的新边，在拆除原边
//则可以作为一种方案，且仅此一种；
//如果被覆盖两次及以上，则这条原边无论怎么拆除，都不能使图不连通

//代码实现思路：对于每条新加的边，将其两点在原树上的路径加1
//(因为是树，两点间路径唯一)，此部分可以用树上差分实现，
//思想类似于线性差分，因为统计的是边，所以对于新加入的边
//(s,t)，a[s]++,a[t++],a[lca(s,t)]-=2,因为统计的是边出现次数
//所以lca(s,t)需要减去2，如果是点,则lca(s,t)减1，其父结点减1 
//对于每条边，统计其被覆盖过的次数，如果未被覆盖过
//则ans+=m,如果被覆盖过一次，则ans++,其余情况ans不变。
//ps:此题会卡vector 
//题目链接： http://poj.org/problem?id=3417
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 100000000

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
struct node{
	int num;
	node* nex;
};
int m, a[maxn], root, dep[maxn], par[maxn][20];
LL ans; 
node* head[maxn];
void dfs(int v, int p, int d);
void init(int n);
int lca(int u, int v);
void end_dfs(int u);
void add(int f, int t);

int main()
{
	int n, i, f, t;
	scanf("%d %d", &n, &m);
	for(i=0;i<=n;i++)
		head[i] = NULL;
	ans = 0;
	for(i=1;i<n;i++){
		scanf("%d %d", &f, &t);
		add(f, t);
		add(t, f);
	}
	root = 1;
	init(n);
	for(i=1;i<=m;i++)
	{
		scanf("%d %d", &f, &t);
		if(f == t)continue;
		int fa = lca(f, t);
		//将其两个结点增加1，lca减2 
		a[f]++, a[t]++, a[fa]-=2;
	}
	end_dfs(1);
	printf("%lld\n", ans);
	return 0;
}

void add(int f, int t)
{
	node *p = new node;
	p->nex = head[f];
	p->num = t;
	head[f] = p;
}

void dfs(int v, int p, int d){
	par[v][0] = p;
	dep[v] = d;
	node *q;
	for(q = head[v];q!=NULL;q=q->nex)
		if(q->num != p)dfs(q->num, v, d+1);
}

void init(int n)
{
	dfs(root, -1, 0);
	for(int k=0;k+1<17;k++)
		for(int v=1;v<=n;v++){
			if(par[v][k]<0)par[v][k+1] = -1;
			else par[v][k+1] = par[par[v][k]][k];
		}
}

int lca(int u, int v)
{
	if(dep[u]>dep[v]){
		int t=u;u=v;v=t;
	}
	for(int k=0;k<17;k++){
		if((dep[v]-dep[u])>>k &1)
			v = par[v][k];
	}
	if(u == v)return u;
	for(int k=16;k>=0;k--){
		if(par[u][k] != par[v][k]){
			u = par[u][k];
			v = par[v][k];
		}
	}
	return par[u][0];
}
//递归访问求各结点的值 
void end_dfs(int u)
{
	node *p;
	//当前结点的值等于其所有子结点的值和加上自身值 
	for(p = head[u];p!=NULL;p=p->nex)
	{
		if(par[u][0] == p->num)continue;
		end_dfs(p->num);
		int &e = a[p->num];
		a[u] += e;
		if(e == 0)ans+=m;
		else if(e == 1)ans++;
	}
	
}
