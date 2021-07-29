//��С��
//�ܵ��͵Ķ�ʽȡһ����
//����һ����Ʒ��A��B���ֲ�ͬ��Ȩֵ
//ͬʱ�ض���Ʒ�����һ��A��B�ڣ����ض���ֵ
//������Ȩֵ
//���ȿ������뵽��С�����������ͼ��Ȼ�����ÿ���ض�
//����ϣ���������x��x'��Ȼ������0��x������Ϊc1������x'
//����㣬Ȼ��������ڵ�Ԫ��ai����x��ai����ΪINF��ai��
//x'����ΪINF�ıߣ����������Ȼ�����ܵ�Ȩֵ�ͼ�ȥ��С��
//���ǽ��
//��Ŀ���ӣ�https://www.luogu.org/problem/P1361 
#include<clstdio>
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 5020;
const int mod = 1000000007;
struct node{
	int to, cap, flow, nex;
}eg[2020*2020];
int cnt, pmax, hd[maxn], dis[maxn], vis[maxn];
int a[maxn], b[maxn], c[maxn];
void init();
void add(int f, int t, int cap);
LL dinic(int s, int t);
void bfs(int s, int t);
int dfs(int s, int t, int ans);

int main()
{
	int n, m, i, j, ed, up1, up2, num;
	LL ans = 0;
	init();
	scanf("%d", &n);
	ed = n+1;
	num = ed+1;
	for(i=1;i<=n;i++){
		scanf("%d", &a[i]);
		ans += a[i];
		add(0, i, a[i]);
	}
	for(i=1;i<=n;i++){
		scanf("%d", &b[i]);
		ans += b[i];
		add(i, ed, b[i]);
	}
	scanf("%d", &m);
	while(m--)
	{
		int k, c1, c2;
		scanf("%d %d %d", &k, &c1, &c2);
		//���x��x' 
		up1 = num+1, up2 = num+2;
		num+=2;
		//����0->x,x'-ed��������ΪINF 
		add(0, up1, c1);
		add(up2, ed, c2);
		ans += c1+c2;
		for(i=1;i<=k;i++)
		{
			scanf("%d", &c[i]);
			add(up1, c[i], INF);
			add(c[i], up2, INF);
		}
	}
	pmax = num; 
	LL res = dinic(0, ed);
	printf("%lld\n", ans-res);
	return 0;
}

void init()
{
	memset(hd, -1, sizeof(hd));
	cnt = 1;
}

void add(int f, int t, int cap)
{
	eg[++cnt].to = t;
	eg[cnt].cap = cap;
	eg[cnt].flow = 0;
	eg[cnt].nex = hd[f];
	hd[f] = cnt;
	eg[++cnt].to = f;
	eg[cnt].cap = 0;
	eg[cnt].flow = 0;
	eg[cnt].nex = hd[t];
	hd[t] = cnt;
}

LL dinic(int s, int t)
{
	LL res = 0;
	while(1)
	{
		bfs(s, t);
		if(dis[t] < 0)return res;
		int d;
		for(int i=0;i<=pmax;i++)
			vis[i] = hd[i];
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
		int u = que.front();que.pop();
		for(int i=hd[u];i!=-1;i=eg[i].nex)
		{
			node e = eg[i];
			if(e.cap > e.flow && dis[e.to] == -1)
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
	for(int &i=vis[s];i!=-1;i=eg[i].nex)
	{
		if(eg[i].cap > eg[i].flow && dis[eg[i].to] == dis[s]+1)
		{
			int d = dfs(eg[i].to, t, min(ans, eg[i].cap-eg[i].flow));
			if(d>0)
			{
				eg[i].flow += d;
				eg[i^1].flow -= d;
				return d;
			}
		}
	}
	return 0;
}
