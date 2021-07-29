//trajan算法缩点
//有一个有向图，问最少需要放几个点，才能保证
//可以到达所有点，最少加几条边可以使他成为强连通图
//用trajan缩点，然后入度为0的点即为问题1的答案
//然后出度为0的点的数量和入度为0的点的数量
//的最大值即为问题二的答案
//题目链接：http://poj.org/problem?id=1236 
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
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 110;
//g为原图，sg为缩点后的图 
vector<int> g[maxn], sg[maxn];
int vis[maxn], low[maxn], dfn[maxn], in[maxn], out[maxn];
//color为缩点后的颜色，值相同代表在一个点 
int con, top, sum, color[maxn], stack[maxn];
void trajan(int u);

int main()
{
	int n, i, j, k;
	top = con = sum = 0;
	memset(vis, 0, sizeof(vis));
	memset(dfn, 0, sizeof(dfn));
	memset(color, 0, sizeof(color));
	scanf("%d", &n);
	for(i=1;i<=n;i++)
	{
		while(scanf("%d", &j), j)
			g[i].push_back(j);
	}
	for(i=1;i<=n;i++)
	if(!dfn[i])trajan(i); 
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	//缩点后连边，将不同的两个点的边添加到缩后的图里 
	for(i=1;i<=n;i++)
	{
		for(j=0;j<g[i].size();j++)
		if(color[i] != color[g[i][j]])
		{
			sg[color[i]].push_back(color[g[i][j]]);
			out[color[i]]++, in[color[g[i][j]]]++;
		}
	}
	int k1 = 0, k2 = 0;
	for(i=1;i<=sum;i++)
	{
		if(in[i] == 0)k1++;
		if(out[i] == 0)k2++;
	}
	if(sum == 1)
		printf("1\n0\n");
	else
		printf("%d\n%d\n", k1, max(k1, k2));
	return 0;
}

void trajan(int u)
{
	vis[u] = 1;
	dfn[u] = low[u] = ++con;
	stack[++top] = u;
	for(int i=0;i<g[u].size();i++)
	{
		int v = g[u][i];
		if(!dfn[v])
		{
			trajan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(dfn[v] && vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u])
	{
		
		color[u] = ++sum;
		vis[u] = 0;
		while(stack[top] != u)
		{
			vis[stack[top]] = 0;
			color[stack[top--]] = sum;
		}
		top--;
	}
}
