/*********************************************************
DFS + 思路
有一棵以1节点为根节点的有根树，树上的点分为重要点和非重要点，现在有一个集合，集合
中的点，要不是重要点，要不是两个重要点的LCA。给出树上的非重要的，求辅助集合的大小。

思路：因为每个询问给出的是m个非重要点，那么n-m个重要点肯定在集合中，关键在于是
两个重要点LCA的非重要点。如果一个非重要点，则需要保证所有的儿子中，至少有两个他的儿子
及其所在树存在重要点。
在处理每个询问时，如果一个节点为非重要点，那么如果他的度数大于等于2，显然他是集合中的元素，
如果他的度数为0，则说明他的所有儿子节点及其后代节点都是非重要点，那么对于他的父节点来说，
这个儿子节点的存在无贡献，可以将其父节点的度数减一。因为会对前面有影响，所以需要先处理较深的
节点。
综上，对于每棵树，需要求出每个节点的深度，其父节点，和度数(儿子的数量)。对于每次询问，暂且记
ans = n-m。将所有非重要点按深度降序排列，并依次访问，如果当前节点的度数大于等于2，则ans++，
如果度数等于0，则其父节点度数减1。最后输出即可。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=5927
********************************************************/
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
typedef pair<int, int> P;
const int maxn = 100100;
int a[maxn], dep[maxn], fa[maxn], son[maxn];
vector<int> g[maxn];
void dfs(int u, int dept);
bool cmp(int a, int b);

int main()
{
	int t, q, n, m, ans, i, j, k;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		scanf("%d %d", &n, &q);
		for(i=0;i<=n;i++)g[i].clear();
		for(i=1;i<n;i++){
			scanf("%d %d", &j, &k);
			g[k].push_back(j);
			g[j].push_back(k);
		}
		fa[1] = 0;
		dfs(1, 1);
		printf("Case #%d:\n", z);
		while(q--)
		{
			scanf("%d", &m);
			ans = n-m;
			for(i=0;i<m;i++)
				scanf("%d", &a[i]);
			sort(a, a+m, cmp);
			for(i=0;i<m;i++)
				if(son[a[i]] == 0)
					son[fa[a[i]]]--;
				else if(son[a[i]]>1)
					ans++;
			for(i=m-1;i>=0;i--)
				if(son[a[i]] == 0)
					son[fa[a[i]]]++;
			printf("%d\n", ans);
		}
	}
	return 0;
}

void dfs(int u, int dept)
{
	dep[u] = dept;
	son[u] = 0;
	for(int i=0;i<g[u].size();i++){
		if(g[u][i] != fa[u]){
			fa[g[u][i]] = u;
			son[u]++;
			dfs(g[u][i], dept+1);
		}
	}
}

bool cmp(int a, int b)
{
	return dep[a] > dep[b];
}

