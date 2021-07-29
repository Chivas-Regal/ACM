//trajan�㷨
//����
//�ο����ͣ�https://blog.csdn.net/shiqi_614/article/details/7833628
//��Ŀ���ӣ� http://lightoj.com/volume_showproblem.php?problem=1063
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 10100;
vector<int> g[maxn];
//dfn���ڵ��״γ��ֵ�ʱ��
//low���ڵ��ܷ��ʵ���������ֵ�ʱ��� 
int con, vis[maxn], par[maxn], low[maxn], dfn[maxn], a[maxn];
void trajan(int u);

int main()
{
	int t, n, m, i, j, k, sum;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		con = sum = 0;
		scanf("%d %d", &n, &m);
		for(i=0;i<=n;i++)g[i].clear();
		for(i=1;i<=n;i++)a[i] = i;
		while(m--)
		{
			scanf("%d %d", &i, &j);
			g[i].push_back(j);
			g[j].push_back(i);
		}
		memset(a, 0, sizeof(a));
		memset(vis, 0, sizeof(vis));
		par[1] = -1;
		trajan(1);
		for(i=1;i<=n;i++)
		if(a[i])sum++;
		printf("Case %d: %d\n", z, sum);
	}
	return 0;
}

void trajan(int u)
{
	int sum = 0;//sumΪ���������� 
	vis[u] = 1;
	dfn[u] = low[u] = ++con;
	for(int i=0;i<g[u].size();i++)
	{
		if(!vis[g[u][i]])
		{
			sum++;
			par[g[u][i]] = u;
			trajan(g[u][i]);
			low[u] = min(low[u], low[g[u][i]]);
			//������ʼ���ʵ��Ǹ��ڵ㲢����������������Ϊ��� 
			if(par[u] == -1 && sum>1)
				a[u] = 1;
			//���������ʼ�㣬��u���ӽڵ���û���ܷ���u���丸�ڵ�ıߣ���Ϊ��� 
			else if(par[u]!=-1 && low[g[u][i]]>=dfn[u])
				a[u] = 1;
			//dfn[u]<low[v]����������(u,v)Ϊ�� 
		}
		else 
			low[u] = min(low[u], dfn[g[u][i]]);
	}
}
