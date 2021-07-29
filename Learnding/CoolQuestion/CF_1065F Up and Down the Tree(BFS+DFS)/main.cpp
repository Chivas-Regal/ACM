/******************************************************
BFS+DFS

有一棵树，1号节点为根节点，每次可以进行两种操作，
1、从当前节点进入其子树下的任一叶节点，
2、如果当前是叶节点，可以向上走不超过k步
初始在根节点，问最多能到达多少个不同的叶节点

思路：对于一个叶节点，假如处于当前节点，一定是尽可能的往上退的，因为
那样才能有机会访问更多的叶节点。设数组num，num[i]代表从当前节点走能
访问到的叶子节点并最高回到i号节点的叶子数量。所以可以考虑每个叶节点，
求出它按照规则走，能到达的最高的节点。(为什么不直接说向上走k步，因为存在
叶子节点较深，向上走几步，然后到一个深度较小的叶子节点，然后在向上退k步的
情况。)
所以对于num数组，可以考虑bfs，求每个节点对应的num。首先将叶节点放入队列中，
然后先访问深度较大的节点，同时每个节点，维护走到当前节点最多能在走几步的信息。

题目链接：https://codeforces.com/problemset/problem/1065/F
*********************************************************/
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
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000100;
const int mod = 772002;
struct node{
	int u, dep;
	node(){}
	node(int a, int b):u(a), dep(b){}
	bool operator <(node b)const
	{
		return dep < b.dep;
	}
};
//num:最多能回到i号节点的叶子节点的数量
//b:当前节点最多能向上走几步
int ans, num[maxn], fa[maxn], b[maxn], dep[maxn], vis[maxn];
vector<int> g[maxn];
void bfs(int n, int k);
void dfs(int u, int de, int num1);

int main()
{
	int n, k, i, j;
	scanf("%d %d", &n, &k);
	for(i=2;i<=n;i++){
		scanf("%d", &fa[i]);
		g[fa[i]].push_back(i);
	}
	//dfs求深度
	dfs(1, 1, 0);
	ans = 0;
	//bfs求每个点最多能到几个叶子节点并回到当前节点
	bfs(n, k);
	//dfs求最优解
	dfs(1, 1, num[1]);
	printf("%d\n", ans);
	return 0;
}

void dfs(int u, int de, int num1)
{
	ans = max(num1, ans);
	dep[u] = de;
	for(int i=0;i<g[u].size();i++)
		dfs(g[u][i], de+1, num1 + num[g[u][i]]);
}

void bfs(int n, int k)
{
	int i, j;
	memset(vis, 0, sizeof(vis));
	priority_queue<node> que;
	for(int i=1;i<=n;i++){
		if(!g[i].size()){
			que.push(node(i, dep[i]));
			b[i] = k;
			num[i] = 1;
		}
	}
	//深度优先bfs
	while(!que.empty())
	{
		node p = que.top();que.pop();
		if(b[p.u] == 0 || p.u == 1 || vis[p.u])continue;
		vis[p.u] = 1;
		b[fa[p.u]] = max(b[p.u]-1, b[fa[p.u]]);
		num[fa[p.u]] += num[p.u];
		que.push(node(fa[p.u], dep[fa[p.u]]));
		//为避免重复计数，将当前节点的数量清0
		num[p.u] = 0;
	}
}