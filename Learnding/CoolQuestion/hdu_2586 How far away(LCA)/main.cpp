//trajan������lca
//dfs����������ڵ�ǰ�ڵ㣬�Ƚ��丸�ڵ㸳Ϊ�Լ���Ȼ�����
//�����������ڵ㣬������ɺ�Ҫ�����ӽڵ�ĸ��ڵ����Ϊ
//�Լ�(�൱�ڲ��鼯���������ӽڵ���µ��Լ����ڵ���)��
//Ȼ��������Լ��йص�����ѯ�ʣ����ѯ���е���һ����
//�Ѿ��������ˣ�������һ���ڵ�Ĳ��鼯�ĸ��������ΪLCA
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=2586
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 40010;
int cnt, hd[maxn], qe[maxn], nex[3*maxn], to[3*maxn], id[3*maxn];
int ans[maxn], dis[maxn], fa[maxn], vis[maxn];
void init();
int get_fa(int x);
void trajan_lca(int u);
void add(int *h, int f, int t, int p);

int main()
{
	int t, n, i, fr, to, p, m;
	scanf("%d", &t);
	while(t--)
	{
		init();
		scanf("%d %d", &n, &m);
		for(i=1;i<n;i++){
			scanf("%d %d %d", &fr, &to, &p);
			add(hd, fr, to, p);
			add(hd, to, fr, p);
		}
		for(i=1;i<=m;i++){
			scanf("%d %d", &fr, &to);
			add(qe, fr, to, i);
			add(qe, to, fr, i);
		}
		dis[1] = 0;
		trajan_lca(1);
		for(i=1;i<=m;i++){
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}

void add(int *h, int f, int t, int p)
{
	to[++cnt] = t;
	id[cnt] = p;
	nex[cnt] = h[f];
	h[f] = cnt;
}

void init()
{
	cnt = 0;
	memset(fa, 0, sizeof(fa));
	memset(vis, 0, sizeof(vis));
	memset(qe, 0, sizeof(qe));
	memset(hd, 0, sizeof(hd));
}
//��ѯu���������� 
void trajan_lca(int u)
{
	vis[u] = 1;
	fa[u] = u;
	//�����������ӽڵ㣬
	for(int i=hd[u];i;i=nex[i]){
		int v = to[i];
		if(!vis[v]){
			dis[v] = dis[u] + id[i];
			trajan_lca(v);
			fa[v] = u;
		}
	}
	//���ʺ�u�йص�����ѯ�� 
	for(int i=qe[u];i;i=nex[i]){
		int v = to[i];
		//�����һ���ڵ㱻���ʹ�
		//����һ���ڵ����ڵĲ��鼯���ڵ㼴ΪLCA 
		if(vis[v]){
			int tmp = get_fa(v);
			ans[id[i]] = dis[u]+dis[v]-2*dis[tmp];
		}
	}
}
//��x�����ڲ��鼯�ĸ��ڵ� 
int get_fa(int x)
{
	if(x == fa[x])return x;
	return fa[x] = get_fa(fa[x]);
}
