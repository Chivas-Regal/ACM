# 🔗
<a href="http://poj.org/problem?id=1655"><img src="https://i.loli.net/2021/09/27/goTJAuW86V52F3U.png"></a>  

# 💡
本题是让输出树的值最小的重心和这个重心的重量   
算是模板题  
  
回溯求得  
我们要求的每个树的子树大小然后进行比较，得到一个初步的重量  
拿这个初步的重量和另一端的重量进行比较，也就是`n-sz[x]`  
得到后，根据重心的性质：如果重量小于等于n/2，那么可以成为树的重心  
在这个条件下进行比较当前点是否满足，满足的话比较一下数值大小   
  
最后输出重心和重量

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e4 + 10, M = 5e4;
int n;

namespace TreeMap {
        struct Edge { int nxt, to; } edge[M];
        int head[M], cnt;
        inline void Init () {
                for ( int i = 0; i < M; i ++ ) head[i] = -1;
                cnt = 0;
        }
        inline void add_Edge ( int from, int to ) {
                edge[ ++ cnt ] = { head[from], to };
                head[from] = cnt;
        }
}

namespace TreeWeightCenter {
        int sz[N], weight[N], center;
        inline void Init () {
                for ( int i = 0; i < N; i ++ ) 
                        sz[i] = 1, 
                        weight[i] = 0;
                center = 1e9;
        }
        inline void dfs ( int x, int fath ) {
                for ( int i = TreeMap::head[x]; ~i; i = TreeMap::edge[i].nxt ) {
                        int to = TreeMap::edge[i].to;
                        if ( to == fath ) continue;
                        dfs ( to, x );
                        sz[x] += sz[to]; // 子树大小
                        weight[x] = max ( weight[x], sz[to] ); // 重量选择最大子树大小
                }
                weight[x] = max ( weight[x], n - sz[x] ); // 还要和另一端的子树对比一下
                if ( weight[x] <= n / 2 ) center = min ( center, x ); // 可以作为重心
        }
}


int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        int cass; scanf("%d", &cass); while ( cass -- ) {
                TreeMap::Init(); TreeWeightCenter::Init();
                scanf("%d", &n);
                for ( int i = 1, a, b; i < n; i ++ )
                        scanf("%d%d", &a, &b),
                        TreeMap::add_Edge(a, b),
                        TreeMap::add_Edge(b, a);
                TreeWeightCenter::dfs ( 1, 1 );
                printf("%d %d\n", TreeWeightCenter::center, TreeWeightCenter::weight[TreeWeightCenter::center]);
        }
}
```
