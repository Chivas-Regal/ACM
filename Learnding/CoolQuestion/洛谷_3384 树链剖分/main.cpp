//树链剖分
//对于一颗树，将其分解为许多条链，然后可以使用线段树
//等数据结构来维护链上的值，一棵树保证其子树编号连续
//重链上的编号连续。
//对l到r路径上所有子树可以进行快速的加减、统计操作
//对某结点子树也可以进行加减、统计操作
//题目链接：https://www.luogu.org/problem/P3384
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1e9;
struct node{
	LL sum, lazy;
}p[maxn*4];
//fa：存放结点的父结点 son：存放结点的重儿子
//de：结点的深度       size：结点子树大小
//id：重新编号后其原结点得应的编号
//rk：重新编号后其编号对应的原结点 
int cnt, fa[maxn], son[maxn], de[maxn], size[maxn], top[maxn];
int id[maxn], rk[maxn];
int n, a[maxn], b[maxn];
LL ans, modd;
vector<int> g[maxn];
void dfs1(int f, int u, int d);
void dfs2(int t, int u);
void bulit(int l, int r, int k);
void upd(int l, int r, int al, int ar, int x, int k);
void down(int k, int l);
void query(int l, int r, int al, int ar, int k);
void quiry(int l, int r);
void road_upd(int l, int r, int x);

int main()
{
	int t, i, j, k, m, l, r, root;
	scanf("%d %d %d %lld", &n, &m, &root, &modd);
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]);
	for(i=1;i<n;i++){
		scanf("%d %d", &j, &k);
		g[j].push_back(k);
		g[k].push_back(j);
	}
	dfs1(-1, root, 1);
	dfs2(root, root);
	for(i=1;i<=n;i++)
		b[id[i]] = a[i];
	bulit(1, n, 1);
	while(m--){
		int x;
		scanf("%d", &t);
		switch(t){
			case 1:
				scanf("%d %d %d", &l, &r, &x);
				road_upd(l, r, x);
				break;
			case 2:
				scanf("%d %d", &l, &r);
				quiry(l, r);
				printf("%lld\n", ans);
				break;
			case 3:
				//l所有子树加上r，即id[l]+size[l]-1 
				scanf("%d %d", &l, &r);
				upd(1, n, id[l], id[l]+size[l]-1, r, 1);
				break;
			case 4:
				scanf("%d", &x);
				ans = 0;
				query(1, n, id[x], id[x]+size[x]-1, 1);
				printf("%lld\n", ans);
				break;
		}
	}
	return 0;
}

void dfs1(int f, int u, int d){
	//记录各点子树结点数量，最多的为重儿子 
	int mx = -1;
	fa[u] = f;
	size[u] = 1;
	de[u] = d;
	for(int i=0;i<g[u].size();i++){
		if(g[u][i] != f){
			dfs1(u, g[u][i], d+1);
			size[u] += size[g[u][i]];
			if(mx == -1 || size[g[u][i]]>size[mx])
				mx = g[u][i];
		}
	}
	son[u] = mx;
}
//t:u的父结点，u当前结点 
void dfs2(int t, int u){
	top[u] = t;
	id[u] = ++cnt;
	rk[cnt] = u;
	//先遍历重儿子，以保证重链编号连续 
	if(son[u]==-1)return;
	dfs2(t, son[u]);
	for(int i=0;i<g[u].size();i++){
		if(g[u][i] != fa[u] && g[u][i] != son[u])
			dfs2(g[u][i], g[u][i]);
	}
}

void bulit(int l, int r, int k)
{
	p[k].lazy = 0;
	if(l == r){
		p[k].sum = b[l] % modd;
		return;
	}
	int mid = (l+r)/2;
	bulit(l, mid, 2*k);
	bulit(mid+1, r, 2*k+1);
	p[k].sum = (p[2*k].sum + p[2*k+1].sum) % modd;
}

void upd(int l, int r, int al, int ar, int x, int k){
	//将当前的lazy标记计算完成 
	down(k, r-l+1);
	if(l == al && r == ar){
		p[k].lazy = x;
		down(k, r-l+1);
		return;
	}
	//[al,ar]区间都加上x，则当前区间总和加上(ar-al+1)*x;
	p[k].sum = (p[k].sum + (ar-al+1)*x%modd) % modd;
	int mid = (l+r)/2;
	if(ar <= mid)
		upd(l, mid, al, ar, x, 2*k);
	else if(al>mid)
		upd(mid+1, r, al, ar, x, 2*k+1);
	else{
		upd(l, mid, al, mid, x, 2*k);
		upd(mid+1, r, mid+1, ar, x, 2*k+1);
	}
}

void query(int l, int r, int al, int ar, int k){
	down(k, r-l+1);
	if(l == al && r == ar){
		ans = (ans + p[k].sum)%modd;
		return;
	}
	int mid = (l+r)/2;
	if(ar <= mid)
		query(l, mid, al, ar, 2*k);
	else if(al>mid)
		query(mid+1, r, al, ar, 2*k+1);
	else{
		query(l, mid, al, mid, 2*k);
		query(mid+1, r, mid+1, ar, 2*k+1);
	}
}

//将当前区间的lazy标记加到sum中，并将lazy标记下移
//以保证当前区间sum值正确 
void down(int k, int l){
	p[k].sum = (p[k].sum +  p[k].lazy * l % modd)%modd;
	if(l != 1){
		p[2*k].lazy = (p[2*k].lazy+p[k].lazy) % modd;
		p[2*k+1].lazy = (p[2*k+1].lazy+p[k].lazy) % modd;	
	}
	p[k].lazy = 0;
}
//将l到r的路径上的所有点加上x 
//寻找LCA，可通过top数组 
void road_upd(int l, int r, int x){
	//如果两点不在一条重链上，则将重链根结点深度较大 
	//的链先计算(如果先移动深度较小的，可能错过LCA) 
	while(top[l] != top[r]){
		if(de[top[l]] > de[top[r]]){
			//更新重链，将其更改为重链根节点的父结点 
			upd(1, n, id[top[l]], id[l], x, 1); 
			l = fa[top[l]];
		}else{
			upd(1, n, id[top[r]], id[r], x, 1);
			r = fa[top[r]];
		}
	}
	//在同一条重链上，更新即可 
	if(de[l] > de[r])
		upd(1, n, id[r], id[l], x, 1);
	else
		upd(1, n, id[l], id[r], x, 1);
}

void quiry(int l, int r){
	ans = 0;
	while(top[l] != top[r]){
		if(de[top[l]] > de[top[r]]){
			query(1, n, id[top[l]], id[l], 1);
			l = fa[top[l]];
		}
		else{
			query(1, n, id[top[r]], id[r], 1);
			r = fa[top[r]];
		}
	}
	if(de[l] > de[r])
		query(1, n, id[r], id[l], 1);
	else
		query(1, n, id[l], id[r], 1);
}
