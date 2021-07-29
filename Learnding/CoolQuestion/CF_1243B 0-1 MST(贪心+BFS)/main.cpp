/**********************************************
贪心+bfs
有一个完全图，有m条边的权值为1，其余边的权值为0，求MST
思路：瞎搞，设两个点集合S, T, S代表已经选中在最小生成树
中的点，T代表未在最小生成树中的点，初始所有点在T中。
随机选一个在T中的点，结果加1，然后将其放入队列，从队列中
取出点u，遍历u的所有边，如果终点在T中，则不处理，如果终点
不在T中，则将其放入队列(代表连接边权为0的边)，继续运行直至
队列为空。
这种思路实质上就是求输入的图的补图，然后对于求其补图有多少个
连通块。
题目链接：https://codeforces.com/contest/1243/problem/D
**************************************************/
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
const int maxn = 100100;
const int mod = 1e9+7;
vector<int> g[maxn];
//st1代表集合T
int in[maxn], vis[maxn], st1[maxn], st2[maxn];
int solve(int n);
 
int main()
{
	int n, m, i, j, k, ans;
	scanf("%d %d", &n, &m);
	for(i=0;i<m;i++)
	{
		scanf("%d %d", &j, &k);
		if(j == k)continue;
		g[j].push_back(k);
		g[k].push_back(j);
	}
	ans = solve(n);
	printf("%d\n", ans-1);
	return 0;
}
 
int solve(int n)
{
	queue<int> que;
	int ans = 0, i, j, num=0, top, top2;
	for(i=0;i<n;i++)
		st1[i] = i+1;
	top = n;
	while(num < n)
	{
		//任取一个不在S中的点
		for(i=1;i<=n;i++)
			if(!vis[i]){
				que.push(i);
				ans++;
				break;
			}
		while(!que.empty())
		{
			int u = que.front();que.pop();
			if(vis[u])continue;vis[u] = 1;num++;
			
			top2 = 0;
			for(j=0;j<g[u].size();j++)
				in[g[u][j]] = 1;
			//对于T中的点v，如果输入中没有(u,v)，则说明边权为0，则连接该
			//边，否则仍将该点留在T中
			for(j=0;j<top;j++)
				if(in[st1[j]] == 1)
					st2[top2++] = st1[j];
				else if(!vis[st1[j]]){
					que.push(st1[j]);
				}
			for(j=0;j<top2;j++)
				st1[j] = st2[j];
			top = top2;
			for(j=0;j<g[u].size();j++)
				in[g[u][j]] = 0;
		}
	}
	return ans;
}