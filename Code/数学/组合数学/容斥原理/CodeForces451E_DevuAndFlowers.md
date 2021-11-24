# 🔗
<a href="https://www.luogu.com.cn/problem/CF451E"><img src="https://i.loli.net/2021/11/24/l2YRfXkU7Aq5bGQ.png"></a>

# 💡
这个数据量...  
感觉母函数过不了，看了眼  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" />  想一下容斥  
  
和多重背包超限一样  
我们考虑这里面的总方案和不合法方案  
如果箱子无限朵花，那么就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{s+n-1}{n-1}" title="\inline \binom{s+n-1}{n-1}" />  种取法  
>即问：  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^nx_i=s" title="\inline \sum\limits_{i=1}^nx_i=s" />   
>那就是使用  <img src="https://latex.codecogs.com/svg.image?\inline&space;n-1" title="\line n-1" />  个隔板将  <img src="https://latex.codecogs.com/svg.image?\inline&space;s" title="\inline s" />  个物品分割成  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" />  份  
>那就是有了  <img src="https://latex.codecogs.com/svg.image?\inline&space;s+n-1" title="\inline s+n-1" />  个位置可以用来放这  <img src="https://latex.codecogs.com/svg.image?\inline&space;n-1" title="\inline n-1" />  个隔板  
>方案数就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{s+n-1}{n-1}" title="\inline \binom{s+n-1}{n-1}" /> 

不合法方案就是“你第  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  个箱子只有  <img src="https://latex.codecogs.com/svg.image?\inline&space;x_i" title="\inline x_i" />  朵花，但是你取了  <img src="https://latex.codecogs.com/svg.image?\inline&space;x_i+1" title="\inline x_i+1" />  朵花  
  
那么我们如果直接强制在<img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />号箱子取  <img src="https://latex.codecogs.com/svg.image?\inline&space;x_i+1" title="\inline x_i+1" />  朵花，那么别的所有取法都不合法  
这就是容斥的问题了，因为枚举会出现重复  
所以就（奇数个箱子）-（偶数个箱子）  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 30;
const int mod = 1e9 + 7;

namespace PermutationAndCombination {
        inline ll ksm ( ll a, ll b ) {
                ll res = 1;
                while ( b ) {
                        if ( b & 1 ) res = res * a % mod;
                        a = a * a % mod;
                        b >>= 1;
                }
                return res;
        }
        inline ll inv ( ll x ) { return ksm(x, mod - 2); }

        ll iv[N];
        inline void Get () {
                for ( int i = 1; i < N; i ++ ) iv[i] = inv(i);
        }
        inline ll C ( ll n, ll m ) {
                if ( n < m )   return 0;
                if ( n < mod ) {
                        ll res = 1;
                        for ( ll i = 1; i <= m; i ++ ) {
                                ll a = (n + i - m) % mod;
                                ll b = i % mod;
                                res = res * a % mod * iv[b] % mod;
                        }
                        return res;
                }
                return C ( n / mod, m / mod ) * C ( n % mod, m % mod ) % mod;
        }
} using namespace PermutationAndCombination;

ll a[N], n, s, res;
int main () {
        ios::sync_with_stdio(false);
        Get(); cin >> n >> s;
        for ( int i = 0; i < n; i ++ ) cin >> a[i];
        for ( int i = 0; i < (1 << n); i ++ ) {
                ll np = 1, cur = s;
                for ( int j = 0; j < n; j ++ ) {
                        if ( i & (1 << j) ) {
                                np = -np;
                                cur -= a[j] + 1; 
                        }
                }
                if ( cur < 0 ) continue;
                ll upd = C(cur + n - 1, n - 1);
                res = (res + np * upd) % mod;
        }
        cout << (res + mod) % mod << endl;
}
```
