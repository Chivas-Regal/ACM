# 🔗
<a href="https://codeforces.com/gym/102900/problem/C"><img src="https://img-blog.csdnimg.cn/22c08ad3440c4ad7a629af2975f96976.png"></a>

# 💡
关注一下 <img src="https://latex.codecogs.com/svg.image?\inline&space;[i\&j=0]" title="\inline [i\&j=0]" />，这样的话每一位都不同才可以做出贡献，那么<img src="https://latex.codecogs.com/svg.image?\inline&space;log(i+j)" title="\inline [i\&j=0]" />就是<img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline [i\&j=0]" />和<img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline [i\&j=0]" />的最高位  
第一眼想到排列组合乱搞，但是架不住有 <img src="https://latex.codecogs.com/svg.image?\inline&space;XY" title="\inline [i\&j=0]" /> 的限制让选数不能随便选  
那么既然是上界，可以采用数位dp去跑  
  
限制为两个上界，正常一个位数
所以我们设置 <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i][j][k]" title="\inline [i\&j=0]" /> 表示枚举到第 <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="" /> 位，第一个数是否到达上界，第二个数是否到达上界  
  
我们在 <img src="https://latex.codecogs.com/svg.image?\inline&space;dfs" title="" />参数上也保持这样的状态，并因为有两个数，我们在枚举第<img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="" />位的时候应有两重 <img src="https://latex.codecogs.com/svg.image?\inline&space;01" title="" />，并根据是否为最高数来给定枚举的最大值，保证两个不同为<img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="" />即可

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int mod = 1e9 + 7;

int a[40], b[40]; // 二进制表示
ll dp[40][2][2];

inline ll DFS ( int id, bool is_high_x, bool is_high_y ) {
        if ( !(~id) ) return 1;
        if ( ~dp[id][is_high_x][is_high_y] ) return dp[id][is_high_x][is_high_y];

        int topx = is_high_x ? a[id] : 1; // 根据最高位设置枚举的最大值
        int topy = is_high_y ? b[id] : 1;

        ll res = 0;
        for ( int i = 0; i <= topx; i ++ ) {
                for ( int j = 0; j <= topy; j ++ ) {
                        if ( i && j ) continue;
                        res += DFS(id - 1, is_high_x && i == topx, is_high_y && j == topy); // 向小位走，传递“是否最高位”
                        res %= mod;
                }
        }
        return dp[id][is_high_x][is_high_y] = res;
}

inline void Solve () {
        ll x, y; cin >> x >> y;
        ll lenx = 0, leny = 0;
        memset(dp, -1, sizeof dp);
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        while ( x ) a[lenx ++] = x % 2, x /= 2;
        while ( y ) b[leny ++] = y % 2, y /= 2;

        ll res = 0;
        for ( int i = 0; i < max(lenx, leny); i ++ ) {
                int topx = i >= lenx - 1 ? a[i] : 1;
                int topy = i >= leny - 1 ? b[i] : 1;
                for ( int j = 0; j <= topx; j ++ ) {
                        for ( int k = j == 0; k <= topy; k ++ ) { // 最高位都是0的话没有枚举的必要
                                if ( j && k ) continue;
                                res += DFS(i - 1, i >= lenx - 1 && j == topx, i >= leny - 1 && k == topy) * (i + 1) % mod;
                                res %= mod;
                        }
                }
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
