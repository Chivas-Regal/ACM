//���ŷ��
//�����ж�ͼ�Ƿ���ͨ��Ȼ����������ⶨ��,
//��������ͼ�м���ñߣ�����Ϊ1(ԭ��s,���t)�� 
//��ÿ������������ȣ�Ȼ���������Ϊ����������ŷ��ͼ
//��������in���ڳ���out�����һ��i��t������Ϊ(in-out)/2�ı�
//��������inС�ڳ���out�����һ��s��i������Ϊ(out-in)/2�ı�
//ͼ������������ŷ��ͼ
//ŷ��·��(ժ��kuangbin)��
//�Ȱ�ͼ�е��������㶨��Ȼ����ÿ�����Dֵ��
//������ֻ��������ĳ�ʼDֵΪ����������ĵ��ʼDֵ��Ϊż����
//���п��ܴ���ŷ��·�������򲻿��ܴ��ڣ���
//��һ���������������ʼDֵΪ�����ĵ㣬��Ϊ��i�͵�j��
//����D[i]>0��D[j]<0����i�����j���յ㣨������D[i]��D[j]ͬ���򲻴���ŷ��·������
//����<j, i>�����Ƿ����ŷ�������ɣ��������ŷ������ɾȥ��<j, i>���ɣ�������ֻ����һ���������
//�ο����ͣ� https://www.cnblogs.com/kuangbin/p/3537525.html
//��Ŀ���ӣ� http://poj.org/problem?id=1637
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
struct edg{
	int f, t;
}p[1020];
struct node
{
	int to, flow, rev;
	node(int a, int b, int c):to(a),flow(b),rev(c){
	}
};
vector<node> g[2020];
int vis[2020], dis[2020], a[220];
void add(int from, int to, int flow);
int dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);
int Find(int x);
bool ishui(int n, int m);

int main()
{
	int t, n, m, i, j, ans, num, in[220], out[220];
	scanf("%d", &t);
	while(t--)
	{
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		ans = 1, num = 0;
		scanf("%d %d", &n, &m);
		for(i=0;i<=n+1;i++)g[i].clear();
		for(i=0;i<m;i++)
		{
			int dir;
			scanf("%d %d %d", &p[i].f, &p[i].t, &dir);
			if(!dir)add(p[i].f, p[i].t, 1);
			in[p[i].t]++, out[p[i].f]++;
		}
		//�ж�ͼ�Ƿ���ͨ 
		if(!ishui(n, m))ans = 0;
		for(i=1;i<=n;i++)
		{
			if(abs(in[i]-out[i])&1)ans = 0;
			//���� 
			if(in[i]<out[i])add(0, i, (out[i]-in[i])/2);
			if(in[i]>out[i])add(i, n+1, (in[i]-out[i])/2);
			num += abs(in[i]-out[i])/2;
		}
		//�ж����� 
		if(dinic(0, n+1)!=num/2)
			ans = 0;
		if(ans)printf("possible\n");
		else printf("impossible\n");
	}
	return 0;
}

bool ishui(int n, int m)
{
	int i, j, num = 0;
	for(i=1;i<=n;i++)
		a[i] = i;
	for(i=0;i<m;i++)
	{
		int x = Find(p[i].f), y = Find(p[i].t);
		if(x!=y){
			a[x] = y;
			num++;
		}
		if(num == n-1)return true;
	}
	return false;
}

int Find(int x)
{
	return a[x]=(a[x]==x?x:Find(a[x]));
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
		while((d=dfs(s, t, INF))>0)
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
