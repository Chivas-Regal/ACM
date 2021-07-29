//��С������+��� 
//�ؼ����ڽ����������⣺ÿ��Ԫ��ֻ���ڴӳ�ʼλ��
//����ʱ�ż�����ã�����ʹ�ú󿪿���0���ø���������ʹ�� 
//�賬��Դ��S�볬�����T����ÿ�����Ϊ�����㣬һ������
//����������һ������������������ͼ���£� 
//����S�㵽���������ĵ㣬����Ϊ������ҪԪ������������Ϊ1
//����S�㵽���������ĵ㣬����Ϊ������ҪԪ������������Ϊ0
//���ӽ��������ĵ㵽T�㣬����Ϊ������ҪԪ������������Ϊ0
//���Ԫ����iʹ���������j����ǰ����j��������i������
//�㵽j�Ľ��յ㣬����ΪINF������Ϊ0
//���Ϲ�ͼ�ɱ�֤�����Ϊ������ҪԪ��֮�ͣ�����С����
//������Դ����������������������������(�൱��i�����
//��Ԫ�ش��ݸ�j)��������ܻ򲻹������ڴ�S������Ҫ��Ԫ��
//��ʱ��С���ü�Ϊ������Ҫ��Ԫ��
//PS��������ʱ��֪��Ϊʲô��������û����������ʾ�ɣ�
//ûע�⵽kֻ��������һ�����ܵ���ĵ㣬Ȼ��͡������� 
//��Ŀ���ӣ�http://202.196.1.136/problem.php?id=2527 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1010;
const int mod = 1e9;
struct node
{
	int to, cap, cost, rev;
	node(int a, int b, int c, int d):to(a),cap(b),cost(c),rev(d){
	}
};
int n, dis[maxn], prevv[maxn], preve[maxn];
int x[maxn], y[maxn], bg[maxn], ed[maxn], na[maxn], a[maxn][8];
vector<node> g[8][3*maxn];
void add(int i, int from, int to, int cost, int flow);
int min_cost_flow(int ks, int s, int t, int f);

int main()
{
	int T, n, m, k, i, j;
	scanf("%d %d %d", &n, &m, &k);
	T = 2*n+1;
	scanf("%d %d", &x[0], &y[0]);
	memset(na, 0, sizeof(na));
	ed[0] = 0;
	for(i=1;i<n;i++){
		scanf("%d %d %d %d", &x[i], &y[i], &bg[i], &ed[i]);
		ed[i] += bg[i];
		for(j=0;j<m;j++)
			scanf("%d", &a[i][j]);
	}
	int sum = 0;
	for(i=1;i<n;i++){
		int d = abs(x[i]-x[0])+abs(y[i]-y[0]);
		if(d > bg[i]){
			sum++;
			na[i] = 1;
		}
	}
	if(sum > k)
		printf("THE END IS COMING!!!!!\n");
	else{
		for(i=1;i<n;i++)
			for(j=1;j<n;j++){
				if(i==j || na[i] || na[j])continue;
				int d = abs(x[i]-x[j])+abs(y[i]-y[j]);
				if(d+ed[i]<=bg[j]){
					for(k=0;k<m;k++)
					add(k, 2*i+1, 2*j, 0, INF);
				}
			}
		for(i=1;i<n;i++){
			for(j=0;j<m;j++)
			if(!na[i]){
				add(j, 2*i, T, 0, a[i][j]);
				add(j, 0, 2*i+1, 0, a[i][j]);
				add(j, 0, 2*i, 1, a[i][j]);
			}
		}
		int ans = 0;
		for(i=0;i<m;i++)
			ans += min_cost_flow(i, 0, T, 1000000);
		printf("%d\n", ans);
	}
	return 0;
}


void add(int i, int from, int to, int cost, int flow)
{
	g[i][from].push_back(node(to, flow, cost, g[i][to].size()));
	g[i][to].push_back(node(from, 0, -cost, g[i][from].size()-1));
}

int min_cost_flow(int ks, int s, int t, int f)
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
			int ss = g[ks][v].size();
			for(int i=0;i<ss;i++)
			{
				node &e = g[ks][v][i];
				if(e.cap>0 && dis[e.to]>dis[v]+e.cost)
				{
					dis[e.to] = dis[v]+e.cost;
					prevv[e.to] = v;
					preve[e.to] = i;
					que.push(P(dis[e.to], e.to));
				}
			}
		 }
		if(dis[t] == INF)return res;
		//for(int i=1;i<=n;i++)h[i] += dis[i];
		int d = f;
		for(int v=t;v!=s;v=prevv[v])
		{
			d = min(d, g[ks][prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * dis[t];
		for(int v=t;v!=s; v=prevv[v])
		{
			node &e = g[ks][prevv[v]][preve[v]];
			e.cap -= d;
			g[ks][v][e.rev].cap += d;
		}
	}
	return res;
}

