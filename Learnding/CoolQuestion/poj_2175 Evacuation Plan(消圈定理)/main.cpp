//��Ȧ����
//����һ�ֽ��������Ϊ�Ƿ����һ�ָ�Ϊ����ķ���
//�������������ŷ����Ļ�������ֱ������������������ᳬʱ
//������Ҫ�������ķ����������Ż�����Ϊ�����ķ����Ƿ���
//����������ģ����Կ��Խ���������ͼ��Ϊ�������ķ���
//����һ���������Ĳ������磬Ȼ�������Ƿ��и�Ȧ�����
//������ڸ��ŵķ�����û����ǰ����
//PS�����Ϻ���Ҳûʲô�ö����ϣ��ͱ�����˵���������
//�Ѳ������罨������Ȼ��ӳ������T��ʼ�ܣ��Ҹ��� 
//��Ŀ���ӣ�http://poj.org/problem?id=2175 
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 220;
struct node{
	int x, y, num;
}b[maxn], a[maxn];
struct edge{
	int to, nex, flow, cap, cost;
}eg[maxn*maxn];
int cnt, hd[maxn], c[maxn][maxn], out[maxn];
int ed, preee[maxn], vis[maxn], dis[maxn], tim[maxn];
void init();
int solve(int n, int m);
void add(int f, int t, int cap, int flow, int cost);

int main()
{
	int n, m, i, j;
	init();
	scanf("%d %d", &n, &m);
	for(i=1;i<=n;i++)
		scanf("%d  %d %d", &a[i].x, &a[i].y, &a[i].num);
	for(i=1;i<=m;i++)
		scanf("%d %d %d", &b[i].x, &b[i].y, &b[i].num);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			scanf("%d", &c[i][j]);
			out[j] += c[i][j];
			//�󻨷� 
			int d = abs(a[i].x-b[j].x)+abs(a[i].y-b[j].y)+1;
			add(i, n+j, a[i].num, c[i][j], d);
		}
	//�����򳬼�������ı߽����� 
	for(i=1;i<=m;i++)
		add(i+n, 0, b[i].num, out[i], 0);
	//SPFA�Ҹ��� 
	int ans = solve(n, m);
	if(ans == -1)
		printf("OPTIMAL\n");
	else{
		printf("SUBOPTIMAL\n");
		memset(vis, 0, sizeof(vis));
		//�ҳ������ϵĵ� 
		while(!vis[ans]){
			vis[ans] = 1;
			ans = preee[ans];
		}
		int ls = ans;
		do{
			int xx = preee[ans];
			if(xx > n && ans<=n)c[ans][xx-n]--;
			if(xx<=n && ans>n)c[xx][ans-n]++;
			ans = xx;
		}while(ans != ls);
		for(i=1;i<=n;i++){
			printf("%d", c[i][1]);
			for(j=2;j<=m;j++)
				printf(" %d", c[i][j]);
			printf("\n");
		}
	}
	return 0;
}

void init()
{
	memset(out, 0, sizeof(out));
	memset(hd, -1, sizeof(hd));
	cnt = 1;
}
//������
//��Ϊ�ǲ���ͼ�ıߣ�����һ���������������Ϊflow
//�����������Ϊ-flow 
void add(int f, int t, int cap, int flow, int cost)
{
	eg[++cnt].to = t;
	eg[cnt].cost = cost;
	eg[cnt].cap = cap;
	eg[cnt].flow = flow;
	eg[cnt].nex = hd[f];
	hd[f] = cnt;
	eg[++cnt].to = f;
	eg[cnt].cost = -cost;
	eg[cnt].flow = -flow;
	eg[cnt].cap = 0;
	eg[cnt].nex = hd[t];
	hd[t] = cnt;
}
//SPFA�Ҹ��� 
int solve(int n, int m)
{
	int i, t = n+m+1;
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	memset(tim, 0, sizeof(tim));
	queue<int> que;
	que.push(0);
	dis[0] = 0;
	vis[0] = 1;
	while(!que.empty())
	{
		int u = que.front();que.pop();
		for(i=hd[u];i!=-1;i=eg[i].nex)
		{
			if(eg[i].cap>eg[i].flow && dis[eg[i].to] > dis[u]+eg[i].cost)
			{
				dis[eg[i].to] = dis[u] + eg[i].cost;
				preee[eg[i].to] = u;
				tim[eg[i].to]++;
				if(!vis[eg[i].to]){
					que.push(eg[i].to);
					vis[eg[i].to] = 1;		
				}
				if(tim[eg[i].to] > t)
					return eg[i].to;
			}
		}
		vis[u] = 0;
	}
	return -1;
}
