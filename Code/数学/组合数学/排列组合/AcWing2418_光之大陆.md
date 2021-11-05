# 🔗
<a href="https://www.acwing.com/problem/content/2420/"><img src="https://img-blog.csdnimg.cn/d53ef6a1ffcd49de9de5d27840b41ec1.png"></a>

# 💡
我们先将题意抽象出来  
相当于给定n个点，分成任意块，每块都是个环，让这些环连通  
  
环与环的之间连通可以prufer编码的性质 ^(n-2)直接得到  
问题就是分成块的问题  
对于i个点，我们要考虑每一个点的归属  
我们分成j块，我们考虑k个点的归属  
那么我们要递推i-1个点中选k-1个点： dp[i][j] = (dp[i][j] + dp[i - k][j - 1] * c[i - 1][k - 1]  
因为每一块可以旋转环，所以要乘阶乘  
  
最后统计一下分成1～n块的方案数  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 210;
ll g[N];
ll dp[N][N];
ll c[N][N];
ll n, mod;

inline void Pre () {
        for ( int i = 0; i < N; i ++ ) {
                for ( int j = 0; j <= i; j ++ ) {
                        if ( j == 0 ) c[i][j] = 1;
                        else          c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
                } 
        }
        g[1] = 1, g[3] = 3;                                                                                                                     
        for ( int i = 4; i < N; i ++ ) g[i] = g[i - 1] * i % mod;
}

int main () {
        cin >> n >> mod; Pre();
        dp[0][0] = 1;
        for ( int i = 1; i <= n; i ++ ) { // 总共i个点
                for ( int j = 1; j <= i; j ++ ) { // 分成j块
                        for ( int k = 1; k <= i - j + 1; k ++ ) { // 要枚举k个看看怎么分配
                                dp[i][j] = (dp[i][j] + dp[i - k][j - 1] * c[i - 1][k - 1] * g[k] % mod) % mod;
                        }
                }
        }
        ll res = g[n - 1], p = 1; // p: prufer定理后面要乘的数
        for ( int k = 2; k <= n; k ++ ) {
                res = ( res + dp[n][k] * p % mod ) % mod;
                p = p * n % mod;
        }
        cout << res << endl;
}
```
