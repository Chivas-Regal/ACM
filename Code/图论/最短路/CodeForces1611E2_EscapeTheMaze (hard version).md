# 🔗
<a href="https://codeforces.com/contest/1611/problem/E2"><img src="https://i.loli.net/2021/11/26/RTpWMdm5ZLg3jcG.png"></a>

# 💡
和 <a href="https://github.com/Chivas-Regal/ACM/blob/main/Code/%E5%9B%BE%E8%AE%BA/%E6%9C%80%E7%9F%AD%E8%B7%AF/CodeForces1611E1_EscapeTheMaze%20(easy%20version).md">这个题</a>没什么大区别，就是任务稍微改了一下而已  
  
如果Vlad可以逃脱，那么谁都抓不住他，输出-1  
否则能抓住他的就是在最后一个dfs中看一下Vlad走的时候会被断多少次  
因为每个人最多会断它一次，因为从上往下走的时候不会有多次相邻一个点

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int n, k;
const int N = 2e5 + 10;
const int M = 4e5 + 10;
int a[N];
bool flag;
int can_catch; // 可以抓住的
 
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
                cnt = can_catch = 0;
                flag = false;
        }
 
        inline void pre_Dfs ( int x, int fath ) {
                if ( x != 1 ) dep[x] = dep[fath] + 1;
                for ( int i = head[x]; i; i = edge[i].nxt ) {
                        int to = edge[i].to;
                        if ( to == fath ) continue;
                        pre_Dfs ( to, x );
                }
        }
 
        inline void pre_Bfs () {
                queue<int> que;
                for ( int i = 0; i < k; i ++ ) 
                        que.push(a[i]),
                        tim[a[i]] = 0;
 
                while ( que.size() ) {
                        int x = que.front(); que.pop();
                        for ( int i = head[x]; i; i = edge[i].nxt ) {
                                int to = edge[i].to;
                                if ( dep[to] > dep[x] ) continue;
                                if ( tim[to] > tim[x] + 1 )
                                        tim[to] = tim[x] + 1,
                                        que.push(to);
                        }
                }
        }
 
        inline void Solve_Dfs ( int x, int fath ) {
                if ( flag ) return;
                if ( dep[x] >= tim[x] ) {can_catch ++; return;}
 
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
        if ( flag ) puts("-1");
        else        printf("%d\n", can_catch);
}
 
int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
