//trajan�㷨����
//��һ������ͼ����������Ҫ�ż����㣬���ܱ�֤
//���Ե������е㣬���ټӼ����߿���ʹ����Ϊǿ��ͨͼ
//��trajan���㣬Ȼ�����Ϊ0�ĵ㼴Ϊ����1�Ĵ�
//Ȼ�����Ϊ0�ĵ�����������Ϊ0�ĵ������
//�����ֵ��Ϊ������Ĵ�
//��Ŀ���ӣ�http://poj.org/problem?id=1236 
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
//gΪԭͼ��sgΪ������ͼ 
vector<int> g[maxn], sg[maxn];
int vis[maxn], low[maxn], dfn[maxn], in[maxn], out[maxn];
//colorΪ��������ɫ��ֵ��ͬ������һ���� 
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
	//��������ߣ�����ͬ��������ı���ӵ������ͼ�� 
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
