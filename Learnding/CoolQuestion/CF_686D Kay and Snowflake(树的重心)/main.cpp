/************************************************** 
��������
һ���и���������ÿ�����Ϊ�������������ģ��������һ������
��⣺�������Ķ���Ϊɾ���˽ڵ��ʣ�µ������ͨ����С
������������������ĵ��������⣬�������ĵ��������£�
1.�������е㵽ĳ����ľ�����У������ĵľ������С�����
	���������ģ����ǵľ����һ����
2.��������ͨ��һ�����������µ�����������ԭ�����������ĵ�������
3.һ������ӻ�ɾ��һ���ڵ㣬�����������ֻ�ƶ�һ���ߵ�λ��
4.һ����������������ģ�������
5. ��һ����������Ϊ���������Ľڵ������һ�����ڵ��ڽڵ�������һ��
6. ��һ���������������У��ҵ�һ����ʹ��ڵ���ǡ�ô��ڵ���
	ԭ���ڵ�������һ��(����"�ڵ������ڵ���ԭ���ڵ�����
	һ��"��������������ڵ�����С������)����ô��������
	��һ����һ�����ġ�
��Ҫ��������6����������dfs���ݹ����ÿ���ڵ�Ľ������
��Ŀ���ӣ�https://codeforces.com/contest/686/problem/D
**************************************************/ 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator> 
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300100;
const int mod = 1000000007;
//si[i]����iΪ���������Ľڵ����� 
int fa[maxn], si[maxn], ans[maxn];
vector<int> g[maxn];
void dfs(int u, int step);

int main()
{
	int n, q, i, j;
	scanf("%d %d", &n, &q);
	for(i=2;i<=n;i++)
	{
		scanf("%d", &fa[i]);
		g[fa[i]].push_back(i);
	}
	dfs(1, 0);
	while(q--)
	{
		scanf("%d", &j);
		printf("%d\n", ans[j]);
	}
	return 0;
}

void dfs(int u, int step)
{
	LL mi;
	int a1, a2;
	si[u] = 1;
	ans[u] = u;
	for(int i=0;i<g[u].size();i++)
	{
		int v = g[u][i];
		dfs(v, step+1);
		si[u] += si[v];
	}
	//�������ڵ������Ľڵ������ض����ڵ��ڵ�ǰ���ڵ�����һ�� 
	for(int i=0;i<g[u].size();i++)
	{
		if(si[g[u][i]]*2 > si[u])
			ans[u] = ans[g[u][i]];
	}
	//�������ڵ���С������ڵ������ڵ���ԭ���ڵ�һ��ĵ� 
	while((si[u]-si[ans[u]])*2>si[u])
		ans[u] = fa[ans[u]];
}
