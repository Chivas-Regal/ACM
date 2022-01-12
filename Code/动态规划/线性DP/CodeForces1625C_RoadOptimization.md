# 🔗
<a href="https://codeforces.com/contest/1625/problem/C"><img src="https://s2.loli.net/2022/01/13/7x1lXpbFmcBIzSh.png"></a>

# 💡
开始两发贪心上去，想着每次删去一个删掉后最省时的点，结果wa了，后来一想删掉当前阶段最省时的不一定能保证这个操作对于最后阶段最优  
观测一下数据量  <img src="https://latex.codecogs.com/svg.image?\inline&space;n\le500" title="\inline n\le500" /> ，三重循环能破，跑  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp" title="\inline dp" /> 吧  
限制为 终止哪个点，最多删  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" /> 个点  
于是我们设置  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i][j]" title="\inline dp[i][j]" /> 表示到第  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 个点删去了  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" /> 个点，可以跑出来的最短时间  
由于如果删掉一个点后，我们的速度是继承该点之前没有删掉的点  
所以我们三重循环，一重  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  枚举到哪个点了，一重枚举删了  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" />  个点，一重枚举上一个点是 <img src="https://latex.codecogs.com/svg.image?\inline&space;o" title="\inline k" />   
如果第  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 个点要删掉了， <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i][j + 1] = min(dp[i][j + 1], dp[o][j - (i - o - 1)] + time(o, i))" title="\inline dp[i][j + 1] = min(dp[i][j + 1], dp[o][j - (i - o - 1)] + time(o, i))" />   
如果不删的话  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i][j] = min(dp[i][j], dp[o][j - (i - o - 1)] + time(o, i))" title="\inline dp[i][j] = min(dp[i][j], dp[o][j - (i - o - 1)] + time(o, i))" /> ，即然是从  <img src="https://latex.codecogs.com/svg.image?\inline&space;o" title="\inline o" /> 跳过来的，那么中间的也必然被删掉了，所以  <img src="https://latex.codecogs.com/svg.image?\inline&space;o" title="\inline o" /> 的时候是删去了  <img src="https://latex.codecogs.com/svg.image?\inline&space;j-(i-o-1)" title="\inline j-(i-o-1)" /> 次  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
ll n, l, k;
ll d[510], a[510];
 
ll dp[510][510];
 
inline ll tm ( int x, int y ) { // x -> y
        return (d[y] - d[x]) * a[x];
}
 
int main () {
        ios::sync_with_stdio(false);
        cin >> n >> l >> k;
        for ( ll i = 0; i < n; i ++ ) cin >> d[i];
        for ( ll i = 0; i < n; i ++ ) cin >> a[i];
        d[n] = l, a[n] = 0;
 
        memset(dp, 0x3f3f3f3f, sizeof dp);
        dp[0][0] = 0;
        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 0; j < min((ll)i, k + 1); j ++ ) {
                        for ( int o = i - j - 1; o < i; o ++ ) {
                                dp[i][j + 1] = min(dp[i][j + 1], dp[o][j - (i - o - 1)] + tm(o, i));
                                dp[i][j] = min(dp[i][j], dp[o][j - (i - o - 1)] + tm(o, i));
                        }
                }
        }
        ll res = 0x3f3f3f3f;
        for ( int j = 0; j <= k; j ++ ) res = min(res, dp[n][j]);
        cout << res << endl;
}
```
