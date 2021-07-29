//��С������
//��k�ֻ��n���̵꣬m���ֿ⣬�����̵���Ҫ�ĸ���
//������������ֿ�洢������������ֿ����䵥λ���ﵽ
//�̵�����Ҫ�ķ��ã�����С�ķ���
//����ÿ�ֻ��ﵥ����ͼ��Դ�����ӷ���Ϊ0������Ϊ�ֿ�
//�洢���ıߣ��ٽ�����Ϊ�ֿ⵽�̵���õıߣ�����ΪINF
//�ıߣ��ٽ�����Ϊ�̵�������������Ϊ0���̵굽���ı�
//Ȼ������С�����������ˣ�
//���ĳ�ֻ��ﲻ�������������������-1
//��Ŀ����:http://poj.org/problem?id=2516 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 120;
struct node
{
	int to, cap, cost, rev;
	node(int a, int b, int c, int d):to(a),cap(b),cost(c),rev(d){
	}
};
vector<node> g[maxn];
int ed, h[maxn], dis[maxn], prevv[maxn], preve[maxn];
int need[maxn][maxn], gs[maxn][maxn];
int min_cost_flow(int s, int t, int f);
void add(int from, int to, int cost, int flow);

int main()
{
	int n, sum, ed, m, k, i, j, p, ans;
	while(scanf("%d %d %d", &n, &m, &k),n&&m&&k)
	{
		ans = 0;
		for(i=1;i<=n;i++)
			for(j=1;j<=k;j++)
				scanf("%d", &need[i][j]);
		for(i=1;i<=m;i++)
			for(j=1;j<=k;j++)
				scanf("%d", &gs[i][j]);
		ed = n+m+1;
		//��k������ֱ�ͼ 
		for(i=1;i<=k;i++)
		{
			sum = 0;
			for(j=0;j<=ed;j++)g[j].clear();
			for(int z=1;z<=n;z++)
				for(j=1;j<=m;j++)
				{
					scanf("%d", &p);
					add(j, z+m, p, INF);
				}
			for(j=1;j<=n;j++)
			{
				sum += need[j][i];
				add(j+m, ed, 0, need[j][i]);
			}
			for(j=1;j<=m;j++)
				add(0, j, 0, gs[j][i]);
			sum = min_cost_flow(0, ed, sum);
			if(sum == -1 || ans == -1)
				ans = -1;
			else
				ans += sum;
		}
		printf("%d\n", ans);
	}
	return 0;
}

void add(int from, int to, int cost, int flow)
{
	g[from].push_back(node(to, flow, cost, g[to].size()));
	g[to].push_back(node(from, 0, -cost, g[from].size()-1));
}

int min_cost_flow(int s, int t, int f)
{
	int res = 0;
	//memset(h, 0, sizeof(h));
	while(f>0)
	{
		priority_queue<P, vector<P>, greater<P> > que;
		fill(dis, dis+t+1, INF);
		dis[s] = 0;
		que.push(P(0, s));
		while(!que.empty())
		{
			P p = que.top();que.pop();
			int v = p.second;
			if(dis[v]<p.first)continue;
			for(int i=0;i<g[v].size();i++)
			{
				node &e = g[v][i];
				if(e.cap>0 && dis[e.to]>dis[v]+e.cost)
				{
					dis[e.to] = dis[v]+e.cost;
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dis[e.to], e.to));
				}
			}
		 }
		if(dis[t] == INF)return -1;
		//for(int i=1;i<=n;i++)h[i] += dis[i];
		int d = f;
		for(int v=t;v!=s;v=prevv[v])
		{
			d = min(d, g[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * dis[t];
		for(int v=t;v!=s; v=prevv[v])
		{
			node &e = g[prevv[v]][preve[v]];
			e.cap -= d;
			g[v][e.rev].cap += d;
		}
	}
	return res;
}
