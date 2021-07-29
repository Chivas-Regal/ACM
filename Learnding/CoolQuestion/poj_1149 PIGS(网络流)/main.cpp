//�������������
//����Ψһ���ѵ���ǹ�ͼ��һ���˿Ϳ��Կ������� 
//����֮���ֵ�����໥ת�ƣ����Խ������ص�ͼ��Ȼ��
//���㣬�����������Ĳ��͡�
//��󽨳ɵ�ͼ�ǣ���һ�����õ��˿�����һ������Ϊ
//��ʼ�����ıߣ�Ȼ����浽�õ���ǰ��һ�����ʵ�����
//�ο����ϣ�https://wenku.baidu.com/view/0ad00abec77da26925c5b01c.html
//��Ŀ���ӣ�http://poj.org/problem?id=1149
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<vector>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
struct node
{
	int to, flow, rev;
	node(int a, int b, int c):to(a),flow(b),rev(c){
	}
};
vector<node> g[2020];
int vis[2020], dis[2020];
void add(int from, int to, int flow);
int dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);

int main()
{
	int m, n, i, j, k, a[1020], bf[1020], ed;
	scanf("%d %d", &n, &m);
	ed = n + m + 1;
	memset(bf, 0, sizeof(bf)); 
	for(i=1;i<=n;i++)
		scanf("%d", &a[i]); 
	for(i=1;i<=m;i++)
	{
		scanf("%d", &j);
		while(j--)
		{
			scanf("%d", &k);
			//������ǵ�һ�����ʣ�����һ������Ϊ�������ı�
			//������һ������ΪINF�ıߡ� 
			if(bf[k] == 0)add(0, n+i, a[k]);
			else add(bf[k]+n, n+i, INF);
			bf[k] = i;
		}
		scanf("%d", &j);
		add(n+i, ed, j);
	}
	int ans = dinic(0, ed);
	printf("%d\n", ans);
	return 0;
}

void add(int from, int to, int flow)
{
	g[from].push_back(node(to, flow, g[to].size()));
	g[to].push_back(node(from, 0, g[from].size()-1));
}

int dinic(int s, int t)
{
	int res = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t]<0)return res;
		memset(vis, 0, sizeof(vis));
		int d;
		while((d=dfs(s, t, 1999999))>0)
			res += d;
	}
}

void bfs(int s, int t)
{
	memset(dis, -1, sizeof(dis));
	queue<int> que;
	que.push(s);
	dis[s] = 0;
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(int i=0;i<g[u].size();i++)
		{
			node &e = g[u][i];
			if(e.flow > 0 && dis[e.to]<0)
			{
				dis[e.to] = dis[u]+1;
				que.push(e.to);
			}
		}
	}
}

int dfs(int s, int t, int ans)
{
	if(s == t)return ans;
	for(int &i=vis[s];i<g[s].size();i++)
	{
		node &e = g[s][i];
		if(e.flow>0 && dis[e.to] == dis[s]+1)
		{
			int d = dfs(e.to, t, min(ans, e.flow));
			if(d>0){
				e.flow -= d;
				g[e.to][e.rev].flow += d;
				return d;
			}
		}
	}
	return 0;
}
