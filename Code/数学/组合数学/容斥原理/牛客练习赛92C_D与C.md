# 🔗
<a href="https://ac.nowcoder.com/acm/contest/11182/C"><img src="https://i.loli.net/2021/11/27/Ne98jLhYZSQsnxz.png"></a>

# 💡
真就看见计数想容斥呗  
首先可以得到总边数  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_edge" title="\inline has\_edge" />  为  <img src="https://latex.codecogs.com/svg.image?\inline&space;\frac{n\times&space;(n-1)}2" title="\inline \frac{n\times&space;(n-1)}2" />  
对于这些边数让两人一起放一共有  <img src="https://latex.codecogs.com/svg.image?\inline&space;\binom{has\_edge}{a}\times\binom{has\_edge}{b}" title="\inline \binom{}{}" /> 种情况，设为  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_situation" title="\inline has\_situation" />   

如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;a+b\ge&space;has\_edge" title="\inline a+b\ge&space;has\_edge" /> 那么不管咋放都成立，直接输出  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_situation" title="\inline has\_situation" /> 就行  
否则看看两人没有公共边的情况  
就是在  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_edge" title="\inline has\_edge" /> 中选  <img src="https://latex.codecogs.com/svg.image?\inline&space;a" title="\inline a" /> 个，再从  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_edge-a" title="\inline has\_edge-a" /> 个中选  <img src="https://latex.codecogs.com/svg.image?\inline&space;b" title="\inline b" /> 个  
这样的答案就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;has\_situation-\binom{has\_edge}{a}\times\binom{has\_edge-a}{b}" title="\inline has\_situation-\binom{has\_edge}{a}\times\binom{has\_edge-a}{b}" />   

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

#define ll long long

using namespace std;

const int mod = 1e9 + 7;
const int N = 1e6 + 10;

ll f[N];
inline void Get () {
        f[0] = 1;
        for ( ll i = 1; i < N; i ++ ) f[i] = f[i - 1] * i % mod;
}
inline ll ksm ( ll a, ll b ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }
        return res;
}
inline ll inv ( ll x ) { return ksm (x, mod - 2); }
inline ll C ( ll n, ll m ) {
        return f[n] * inv(f[m]) % mod * inv(f[n - m]) % mod;
}

int main () {
        Get();
        ll n, a, b; cin >> n >> a >> b;
        ll has_edge = n * (n - 1) / 2;
        ll has_situation = C(has_edge, a) * C(has_edge, b) % mod;
        if ( a + b >= has_edge ) cout << has_situation << endl;
        else {
                ll sub = C(has_edge, a) * C(has_edge - a, b) % mod;
                cout << (has_edge - sub + mod) % mod << endl;
        }
}
```
