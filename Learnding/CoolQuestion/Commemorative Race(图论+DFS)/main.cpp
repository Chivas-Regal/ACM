/*********************************************************************
DFS+DP

有一个DAG图，初始可以选择起点终点和路径，要求使路径最长，如果有多条路径则随机，每一条都可考虑。
现在每一条边都可能不可用，如果在选择的路径上，边(u,v)不可用，那么会先走到u，然后确定一条最长路径
，要求在考虑任意不可用的边的情况下，使最长路径最小。

思路：因为一定会选择最长路径走，所以可以先DP求出每个点的最长路径。然后考虑断边的问题：
可以发现如果断边不在最长路径上，则无影响。所以只考虑最长路径上的断边，如果有x条最长路径，
如果x条路径无公共边，则无论选择断那条边，都不会影响结果，只有在所有最长路径都使用的那条
边才会影响最终结果。
所以需要先求出所有最长路径都使用的边，可以访问所有的最长路径上的点，统计每个长度的点
出现的次数，如果长度为i和长度为i+1的点都只出现了一次，则代表两个点之间的那条边是所有最长
路径所共有的。DFS最长路径，复杂度为O(m)，统计时同时统计如果不走最长边，走次长边最长路径
为多少。
最后暴力满足条件的所有边即可。

题目链接：https://vjudge.net/contest/356743#problem/B
PS：我跳不到原网站啊，我也不知道，我也不敢问。这场训练赛的密码是：zzuli_10（好像是这个）
**************************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, string> P;
const int maxn = 200100;
const int mod = 1000000007;
//g:原图，sg:反向图
vector<int> g[maxn], sg[maxn];
//in：出度，dp：最大深度，a：深度出现的次数，mx2：第i个点除了的次长长度
int ans, in[maxn], dp[maxn], a[maxn], vis[maxn], mx2[maxn];
void solve(int n);
void dfs(int u);

int main()
{
	ans = INF;
	int n, m, i, j, k, mx=0;
	scanf("%d %d", &n, &m);
	while(m--){
		scanf("%d %d", &i, &j);
		sg[j].push_back(i);
		g[i].push_back(j);
		in[i]++;
	}
	solve(n);
	for(i=1;i<=n;i++)
		mx = max(mx, dp[i]);
	for(i=1;i<=n;i++)
		if(dp[i] == mx)dfs(i);
	ans = mx;
	for(i=1;i<=n;i++)
		if(vis[i] && dp[i] && a[dp[i]-1] == 1 && a[dp[i]] == 1)
			ans = min(ans, mx+mx2[i]-dp[i]+1);
	printf("%d\n", ans);
	return 0;
}

void solve(int n)
{
	int i, j, k;
	queue<int> que;
	for(int i=1;i<=n;i++)
		if(in[i] == 0)
			que.push(i), dp[i] = 0;
	while(!que.empty())
	{
		i = que.front();que.pop();
		for(j=0;j<sg[i].size();j++)
		if(dp[i]+1 > dp[sg[i][j]]){
			dp[sg[i][j]] = dp[i]+1;
			que.push(sg[i][j]);
		}
			
	}
}

void dfs(int u)
{
	if(vis[u])return;
	a[dp[u]]++;
	vis[u] = 1;
	mx2[u] = -1;
	for(int i=0;i<g[u].size();i++)
		if(dp[g[u][i]]+1 == dp[u])
			dfs(g[u][i]);
		else mx2[u] = max(mx2[u], dp[g[u][i]]);
}