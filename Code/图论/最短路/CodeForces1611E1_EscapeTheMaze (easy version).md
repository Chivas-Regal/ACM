# 🔗
<a href="https://codeforces.com/contest/1611/problem/E1"><img src="https://i.loli.net/2021/11/26/Q61oAS5wfDUqRdI.png"></a>

# 💡
玩家想抓到Vlad，Vlad想逃脱  
每一个玩家往上跑，Vlad往下跑  
如果一个点Vlad先到了玩家才到，那么玩家是赶不上Vlad的  

所以应该预处理出来玩家到达每一个节点的最短时间  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{tim\}" title="\inline \{tim\}" />   
然后让Vlad往下跑，如果一个点玩家会先到，那么Vlad就不能走这个点  
看看有没有一种方法让Vlad到达叶子节点  

  
那么问题的关键就在处理  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{tim\}" title="\inline \{tim\}" />  数组上了  
这个可以想到最短路的更新方式，以所有玩家为起始点入队进行  <img src="https://latex.codecogs.com/svg.image?\inline&space;BFS" title="\inline BFS" />   
如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;to" title="\inline to" />  点的  <img src="https://latex.codecogs.com/svg.image?\inline&space;tim[to]" title="\inline tim[to]" />  被  <img src="https://latex.codecogs.com/svg.image?\inline&space;tim[x]+1" title="\inline tim[x]+1" />  更新了，那么就入队，一个一个向上更新  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int n, k;
const int N = 2e5 + 10;
const int M = 4e5 + 10;
int a[N];
bool flag;

namespace Tree {
        int head[M], cnt;
        struct Edge {
                int nxt, to;
        } edge[M];

        inline void add_Edge ( int from, int to ) {
                edge[ ++ cnt ] = { head[from], to };
                head[from] = cnt;
        }

        int dep[N];
        int tim[N];
        inline void Init () {
                for ( int i = 0; i <= n; i ++ )
                        head[i] = 
                        dep[i]  = 0,
                        tim[i] = 0x3f3f3f3f;
                cnt = 0;
                flag = false;
        }

        inline void pre_Dfs ( int x, int fath ) { // 处理 {dep}
                if ( x != 1 ) dep[x] = dep[fath] + 1;
                for ( int i = head[x]; i; i = edge[i].nxt ) {
                        int to = edge[i].to;
                        if ( to == fath ) continue;
                        pre_Dfs ( to, x );
                }
        }

        inline void pre_Bfs () { // 最短路处理 {tim}
                queue<int> que;
                for ( int i = 0; i < k; i ++ ) 
                        que.push(a[i]),
                        tim[a[i]] = 0;

                while ( que.size() ) {
                        int x = que.front(); que.pop();
                        for ( int i = head[x]; i; i = edge[i].nxt ) {
                                int to = edge[i].to;
                                if ( dep[to] > dep[x] ) continue; // 要往上跑
                                if ( tim[to] > tim[x] + 1 ) // 更新就入队
                                        tim[to] = tim[x] + 1,
                                        que.push(to);
                        }
                }
        }

        inline void Solve_Dfs ( int x, int fath ) { // 求答案看看往哪搜
                if ( dep[x] >= tim[x] || flag ) return; // 先到了

                bool has_son = false;
                for ( int i = head[x]; i; i = edge[i].nxt ) {
                        int to = edge[i].to;
                        if ( to == fath ) continue;
                        Solve_Dfs ( to, x );
                        has_son = true;
                }
                if ( !has_son ) flag = true;
        }

} using namespace Tree;



inline void Solve () {
        scanf("%d%d", &n, &k); Init();
        for ( int i = 0; i < k; i ++ ) scanf("%d", &a[i]);
        for ( int i = 0, x, y; i < n - 1; i ++ )
                scanf("%d%d", &x, &y),
                add_Edge ( x, y ),
                add_Edge ( y, x );
        pre_Dfs ( 1, 1 );
        pre_Bfs ();
        Solve_Dfs ( 1, 1 );
        if ( flag ) puts("YES");
        else        puts("NO");
}

int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
