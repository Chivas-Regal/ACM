# 🔗
<a href="https://codeforces.com/gym/103145/problem/C"><img src="https://i.loli.net/2021/09/06/X7mSDUEoxi8vnVp.png"></a>

<details>
  <summary align="center">查看题解</summary>
           
# 💡
一个树形dp的比较经典的模型  
由于本题设计两个点存在问题：存在、存在且与另一个存在相连  
再带上一个不存在的问题，所以设计三个状态  
dp[x][0]：不存在  
dp[x][1]：存在但不连子节点  
dp[x][2]：存在且连了子节点  
  
分类讨论一下：  
0--不存在：除了不连子节点的点以外，其余状态点都可以连  
<img src="https://latex.codecogs.com/svg.image?dp[x][0]&space;=&space;\prod(dp[y][0]&plus;dp[y][2])&space;" title="dp[x][0] = \prod(dp[y][0]+dp[y][2]) " />  
1--存在但不连子节点：连上所有不存在的点  
<img src="https://latex.codecogs.com/svg.image?dp[x][1]&space;=&space;\prod&space;dp[y][0]" title="dp[x][1] = \prod dp[y][0]" />  
2--存在且连了子节点：除了子节点都不存在以外，别的方式都可以连  
<img src="https://latex.codecogs.com/svg.image?dp[x][2]&space;=&space;\prod(dp[y][0]&space;&plus;&space;dp[y][1]&space;&plus;&space;dp[y][2])&space;-&space;\prod&space;dp[y][0]" title="dp[x][2] = \prod(dp[y][0] + dp[y][1] + dp[y][2]) - \prod dp[y][0]" />
  
最后不能选存在且不连子节点的祖先，这样是一个被孤立的点，所以我们计算  
<img src="https://latex.codecogs.com/svg.image?dp[1][0]&space;&plus;dp[1][2]" title="dp[1][0] +dp[1][2]" />

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#define ll long long
using namespace std;

const int N = 1e5 + 10,
	  M = 2e5 + 10,
	  mod = 998244353;

struct Edge {
	int nxt, to;
}edge[M];

int head[M], cnt;
ll dp[N][3];
int vis[N];
int n;

inline void Init () {
	for ( int i = 0; i < n * 2 + 5; i ++ ) 
		head[i] = -1;
	for ( int i = 0; i < n + 5; i ++ ) 
		vis[i] = 0,  
		dp[i][0] = dp[i][1] = dp[i][2] = 1;
	cnt = 0;
}

inline void Add_Edge ( int from, int to ) {
	edge[++cnt] = { head[from], to };
	head[from] = cnt; 
}

inline void DFS ( int x ) {
	vis[x] = 1;
	for ( int i = head[x]; ~i; i = edge[i].nxt ) {
		int to = edge[i].to;
		if ( vis[to] ) continue;
		DFS ( to );

		dp[x][0] = dp[x][0] * ( dp[to][0] + dp[to][2] ) % mod;
		dp[x][1] = dp[x][1] * dp[to][0] % mod;	
		dp[x][2] = dp[x][2] * ( dp[to][0] + dp[to][1] + dp[to][2] ) % mod;
	}
	dp[x][2] = ((dp[x][2] + mod - dp[x][1]) % mod + mod) % mod;
}

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	int cass;
	for ( scanf("%d", &cass); cass; cass -- ) {
		scanf("%d", &n); Init(); 
		for ( int i = 1; i < n; i ++ ) {
			int a, b; scanf("%d%d", &a, &b); 
			Add_Edge ( a, b );
			Add_Edge ( b, a );
		}
		DFS (1);
		printf("%lld\n",( dp[1][0] + dp[1][2] ) % mod);
	}
	return 0;
}
```
