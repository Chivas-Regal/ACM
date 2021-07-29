//֧����(DAG��)
//��һ��DAGͼ������Ϊ0�ĵ�Ϊ�ؼ��㣬������u��v�����
//DAG������һ�㣬����ʹu��v�޷�����ؼ���
//֧��������ΪʹDAGͼ������ֱ�ӽ��������������ͺ�
//��Ϊ�������㵽�ؼ��㣬���Է��������ˡ�ͼ����һ����ͨ
//����ͨ���ؼ�����0���ߣ���֤һ����ͨ
//����һ����t,���п��Ե�t�Ľ���LCA����Ϊt�ĸ����
//��Ϊ������������t֮ǰ�����п��Ե�t�Ľ�㶼�Ѿ���
//�����ˣ�����ֱ�ӽ���LCA
//���Ӷ�Ϊ��O((n+m)log2n)
//�ο����ͣ� https://blog.csdn.net/a710128/article/details/49913553
//�����Ǹ��Ժ�һ�� 
//�ο����ͣ� https://blog.csdn.net/wmdcstdio/article/details/49868575
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=6604
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
typedef pair<int, int> P;
const int maxn = 100100;
const int maxv = 20;
const int mod = 1e9;
int root, out[maxn], dep[maxn], par[maxn][maxv];
vector<int> g[maxn],  rg[maxn], nt[maxn];
void gettree(int n, int u);
void upd_tree(int f, int u);
int lca(int u, int v);

int main()
{
	int t, n, m, i, j, q, u, v;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d", &n, &m);
		for(i=0;i<=n;i++){
			g[i].clear(), out[i] = 0;
			rg[i].clear();
		}
		while(m--){
			scanf("%d %d", &i, &j);
			g[i].push_back(j);
			rg[j].push_back(i);
			out[i]++;
		}
		for(i=1;i<=n;i++){
			if(out[i] == 0){
				rg[0].push_back(i);
				g[i].push_back(0);
			}	
		}
		gettree(n, 0);
		scanf("%d", &q);
		while(q--)
		{
			scanf("%d %d", &u, &v);
			int lc = lca(u, v);
			printf("%d\n", dep[u]+dep[v]-dep[lc]);
		}
	}
	return 0;
}

void gettree(int n, int u)
{
	int i, j, k;
	queue<int> que;
	dep[0] = 0;
	for(i=0;i<maxv;i++)
		par[0][i] = -1;
	for(i=0;i<rg[u].size();i++){
		que.push(rg[u][i]);
	}
	while(!que.empty()){
		u = que.front();que.pop();
		int lc = g[u][0];
		//�������ܵ�u�Ľ���LCA 
		for(i=1;i<g[u].size();i++)
			lc = lca(lc, g[u][i]);	
		upd_tree(lc, u);
		for(i=0;i<rg[u].size();i++){
			out[rg[u][i]]--;
			if(out[rg[u][i]] == 0)
				que.push(rg[u][i]);
		}
	}
}
//����������֧�����У�������Ԥ���� 
void upd_tree(int f, int u)
{
	nt[f].push_back(u);
	dep[u] = dep[f]+1; 
	par[u][0] = f;
	for(int i=0;i<maxv-1;i++)
		if(par[u][i] < 0)par[u][i+1] = -1;
		else par[u][i+1] = par[par[u][i]][i];
}

int lca(int u, int v)
{
	if(dep[u]>dep[v])
	{
		int t=u;
		u=v;
		v=t;
	}
	//��dep[v]-dep[u] = x, ������x�������ɱ�֤
	//������ͬһ��ȣ�v=par[k][v]��v������2^k�� 
	for(int k=0;k<maxv;k++){
		if((dep[v]-dep[u]) >> k & 1)
			v = par[v][k];
	}
	if(u == v)return u;
	for(int k=maxv-1;k>=0;k--)
	if(par[u][k] != par[v][k]){
		u = par[u][k];
		v = par[v][k];
	}
	return par[u][0];
}
