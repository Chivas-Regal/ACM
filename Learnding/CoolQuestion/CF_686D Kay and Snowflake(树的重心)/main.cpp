/************************************************** 
树的重心
一颗有根树，求以每个结点为根的子树的重心，输出其中一个重心
题解：树的重心定义为删除此节点后剩下的最大连通块最小
此题可以利用树的重心的性质来解，树的重心的性质如下：
1.树中所有点到某个点的距离和中，到重心的距离和最小，如果
	有两个重心，他们的距离和一样。
2.把两棵树通过一条链相连，新的树的重心在原来两颗树重心的连线上
3.一棵树添加或删除一个节点，树的重心最多只移动一条边的位置
4.一棵树最多有两个重心，且相邻
5. 以一棵树的重心为根的子树的节点个数，一定大于等于节点总数的一半
6. 在一棵树的所有子树中，找到一棵树使其节点数恰好大于等于
	原树节点总数的一半(满足"节点数大于等于原树节点总数
	一半"这个条件的子树节点数最小的子树)，那么该子树的
	根一定是一个重心。
主要利用性质6，对树进行dfs，递归求解每个节点的结果即可
题目链接：https://codeforces.com/contest/686/problem/D
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
//si[i]：以i为根的子树的节点数量 
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
	//重心所在的子树的节点数量必定大于等于当前树节点数的一半 
	for(int i=0;i<g[u].size();i++)
	{
		if(si[g[u][i]]*2 > si[u])
			ans[u] = ans[g[u][i]];
	}
	//找子树节点最小的满足节点数大于等于原树节点一半的点 
	while((si[u]-si[ans[u]])*2>si[u])
		ans[u] = fa[ans[u]];
}
