# 🔗
<a href="https://codeforces.com/contest/1593/problem/E"><img src="https://i.loli.net/2021/10/14/bWhzEKde5MxsJBo.png"></a>

# 💡
每次要删叶子节点  
可以思考一下叶子节点的性质：度=1  
  
DFS回溯是很难回溯的，因为走的是一条路，可能会走到别的树枝上  
那么可以思考BFS的队列  
队列一次维护的是相邻的层  
我们从初始的叶子节点出发  
每一次把这个节点砍掉会使它们相接的点的度数-1  
如果出现一个点度数变成1了，那么它就是新的叶子节点  
  
至于答案怎么维护  
每个节点肯定是要选最早入队的  
而每次入队都与让他们入队它们的相接节点有关  
所以可以直接用dp的思想进行转移  
每一个节点的dp表示它是第几次被删掉的  
这个dp是取让他们入队的节点的dp最小值+1  
  
最后记录一下dp>k也就是没有被删掉的节点个数  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 8e5 + 10;
struct Edge { int nxt, to; } edge[N];
int head[N], cnt;
int n, k;
int du[N];
int dpth[N];
 
inline void add_Edge ( int from, int to ) {
        edge[++cnt] = {head[from], to};
        head[from] = cnt;
}
 
inline void Solve() {
        queue<int> que;
        scanf("%d%d", &n, &k);
        if ( n == 1 ) { printf("0\n"); return;}
        for ( int i = 0; i < n * 2; i ++ ) head[i] = -1, dpth[i] = 0x3f3f3f3f, du[i] = 0; cnt = 0;
        for ( int i = 0, x, y; i < n - 1; i ++ ) {
                scanf("%d%d", &x, &y);
                add_Edge ( x, y );
                add_Edge ( y, x );
                du[x] ++;
                du[y] ++;
        }
        for ( int i = 1; i <= n; i ++ ) if ( du[i] == 1 ) que.push(i), dpth[i] = 1, du[i] = 0;
        while ( que.size() ) {
                int cur = que.front(); que.pop();
                for ( int i = head[cur]; ~i; i = edge[i].nxt ) {
                        int to = edge[i].to;
                        du[to] --;
                        if ( du[to] == 1 ) que.push(to), dpth[to] = min(dpth[to], dpth[cur] + 1);
                }
        }
        int res = 0;
        for ( int i = 1; i <= n; i ++ ) if ( dpth[i] > k ) res ++;
        printf("%d\n", res);
}
 
int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve();
        }
}
```
