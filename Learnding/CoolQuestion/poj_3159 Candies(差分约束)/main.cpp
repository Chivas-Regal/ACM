//spfa+差分约束 
//对于xi-xj<=w,可以建一条从j到i的边，然后跑最短路
//题目链接：http://poj.org/problem?id=3159 
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 30010;
int n, m, tot, g[maxn], to[6*maxn], nex[6*maxn], pi[6*maxn];
//vis：当前元素是否在队列(栈中)
//cnt：当前元素入栈次数,一个元素入队超过n次即存在负环 
int vis[maxn], cnt[maxn], st[maxn];
LL dis[maxn];
void add(int f, int t, int p);
bool spfa(int u);

int main()
{
	int i, j, k;
	scanf("%d %d", &n, &m);
	while(m--){
		scanf("%d %d %d", &i, &j, &k);
		add(i, j, k);
	}
	spfa(1);
	printf("%lld\n", dis[n]);
	return 0;
}

void add(int f, int t, int p){
	to[++tot] = t;
	pi[tot] = p;
	nex[tot] = g[f];
	g[f] = tot;
}

bool spfa(int u){
	for(int i=1;i<=n;i++)
		dis[i] = 10000000000000;
	int l = 0;
	st[++l] = u;
	cnt[u]++, vis[u] = 1, dis[u] = 0;
	while(l)
	{
		u = st[l--];
		vis[u] = 0;
		for(int i=g[u];i;i=nex[i])
			if(dis[to[i]]>dis[u]+pi[i]){
				dis[to[i]] = dis[u]+pi[i];
				if(!vis[to[i]]){
					vis[to[i]] = 1, cnt[to[i]]++;
					if(cnt[to[i]]>n)return false;
					st[++l] = to[i];
				}
			}
	 }
	return true; 
}
