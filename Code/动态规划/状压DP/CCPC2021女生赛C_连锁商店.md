# 🔗
<a href="https://codeforces.com/gym/103389/problem/C"><img src="https://s2.loli.net/2022/01/13/7urOm9w23AtzMVC.png"></a>

# 💡
类似于一个旅行商问题  
n不大，我们可以想着用状压来表示状态  
但它是  <img src="https://latex.codecogs.com/svg.image?\inline&space;36" title="\inline 36" /> ，如果用  <img src="https://latex.codecogs.com/svg.image?\inline&space;36" title="\inline 36" /> 位二进制肯定会超内存，想想优化  
如果一个公司只有一个点，那么是没有必要用这个状态的  
因为不能反方向走的话，根本不用决定这个点是否出现过在这个状态内  
所以可以把这类只有一个点的公司拿出来单独选择  
而把至少有两个点的公司压入二进制状态，我们第二维就可以作为上一步是哪个点  
那么这个问题就状压DP  <img src="https://latex.codecogs.com/svg.image?\inline&space;sxy" title="\inline sxy" /> 就可以解决了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 40;
const int M = 1600;
int n, m;
int c[N], w[N];
struct Edge {
        int nxt, to;
} edge[M];
int head[N], cnt;
int vis[N][N];
inline void add_Edge ( int from, int to ) {
        edge[++ cnt] = { head[from], to };
        head[from] = cnt;
}

int dp[300000][40];

// 用来挑出来独立公司的一些工具
vector<int> vec;
int numc[N];
bool one[N]; 
vector<int> cam;

int id[N]; // 公司的新编号

int main () {
        scanf("%d%d", &n, &m);
        for ( int i = 1; i <= n; i ++ ) scanf("%d", &c[i]), c[i] --, numc[c[i]] ++, vec.push_back(i);
        for ( int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
        for ( int i = 1; i <= m; i ++ ) {
                int a, b; scanf("%d%d", &a, &b);
                add_Edge(a, b);
                vis[a][b] = 1;
        }
        for ( int i = 2; i <= n; i ++ ) if ( !vis[1][i] ) add_Edge (1, i);
        sort ( vec.begin(), vec.end(), [&](int x, int y) {
                return numc[c[x]] > numc[c[y]];
        });
        while ( vec.size() && numc[c[vec.back()]] == 1 ) one[vec.back()] = true, vec.pop_back();
        for ( int i = 0; i < vec.size(); i ++ ) cam.push_back(c[vec[i]]);
        sort ( cam.begin(), cam.end() );
        cam.erase(unique(cam.begin(), cam.end()), cam.end());
        for ( int i = 0; i < cam.size(); i ++ ) id[cam[i]] = i;

        // 普通的状压
        if ( one[1] ) dp[0][1] = w[c[1]];
        else dp[1 << (id[c[1]])][1] = w[c[1]];

        for ( int s = 0; s < (1ll << cam.size()); s ++ ) {
                for ( int x = 1; x <= n; x ++ ) {
                        for ( int i = head[x]; i; i = edge[i].nxt ) {
                                int to = edge[i].to;
                                if ( one[to] ) dp[s][to] = max(dp[s][to], dp[s][x] + w[c[to]]);
                                else if ( !(s & (1 << (id[c[to]]) ) ) ) dp[s | (1 << id[c[to]])][to] = max(dp[s | (1 << id[c[to]])][to], dp[s][x] + w[c[to]]); 
                                else dp[s][to] = max(dp[s][to], dp[s][x]);
                        }
                }
        }
        for ( int i = 1; i <= n; i ++ ) {
                int cur = 0;
                for ( int s = 0; s < (1ll << cam.size()); s ++ ) {
                        if ( one[i] ) cur = max(cur, dp[s][i] );
                        else if ( s & (1 << id[c[i]])) cur = max(cur, dp[s][i] );
                }
                printf("%d\n", cur);
        }
}
```
