# 🔗
<a href="https://codeforces.com/gym/102163/problem/C"><img src="https://s2.loli.net/2022/01/06/izcD6HPLqywuN42.png"></a>

# 💡
求最长上升子序列的长度以及它的个数  
可以看做是[这道题](https://www.luogu.com.cn/problem/P1108)的简化版，因为这里是按下标看的  
并不需要涉及一样的数列去重  
  
在这个地方就省去很多处理的步骤  
还是一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp1[i]" title="\inline dp1[i]" /> 表示  结尾是  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  的最长上升子序列长度，一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp2[i]" title="\inline dp2[i]" /> 表示结尾是  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  的最长上升子序列的数量  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;1000" title="\inline 100" /> 的数据量，那么我们求它的时候就是正常的前面的进行   
   
 在求  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp2[i]" title="\inline dp2[i]" /> 时，我们一样枚举  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 前面的  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" /> ，如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;a[j]<a[i]" title="\inline a[j]<a[i]" /> 并且  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp1[i]=dp1[j]+1" title="\inline dp1[i]=dp1[j]+1" /> ，就说明这个  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp1[i]" title="\inline dp[i]" /> 有一部分方案是由  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp1[j]" title="\inline dp1[j]" /> 转移过来的  
 那么我们汇聚一下方案数也就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp2[i]+=dp2[j]" title="\inline dp2[i]+=dp2[j]" /> 就可以了（记得在  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp1[i]=1" title="\inline dp1[i]=1" /> 的情况下说明  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 没有别的推过来，它自己是唯一一种方案，要设置为  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
ll dp1[1005], dp2[1005];
ll a[1005];

inline void Solve () {
        memset(dp1, 0, sizeof dp1);
        memset(dp2, 0, sizeof dp2);
        ll n; cin >> n;
        ll res1 = 1, res2 = 1;

        for ( ll i = 1; i <= n; i ++ ) cin >> a[i];
        for ( ll i = 1; i <= n; i ++ ) {
                dp1[i] = 1;
                for ( ll j = 1; j < i; j ++ ) {
                        if ( a[j] < a[i] ) dp1[i] = max(dp1[j] + 1, dp1[i]);
                }        
        }
        for ( ll i = 1; i <= n; i ++ ) {
                if ( dp1[i] == 1 ) {
                        dp2[i] = 1;
                        continue;
                }
                for ( ll j = 0; j < i; j ++ ) {
                        if ( a[j] < a[i] && dp1[j] + 1 == dp1[i] ) {
                                dp2[i] += dp2[j];
                                dp2[i] %= mod;
                        }
                }
        }

        ll res = 0;
        ll longest = 0;
        for ( ll i = 1; i <= n; i ++ ) {
                longest = max(longest, dp1[i]);
        }
        for ( ll i = 1; i <= n; i ++ ) {
                if ( dp1[i] == longest ) res += dp2[i], res %= mod;
        }
        cout << longest << " " << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
