# 🔗
http://acm.hrbust.edu.cn/index.php?m=ProblemSet&a=showProblem&problem_id=2414

# 💡
设第a[i]种颜色不能用  
那么我们在选k个数中，要求得的是  
<img src="https://latex.codecogs.com/svg.image?1-P(a[1]\cup&space;a[2]\cup&space;a[3]\cup&space;...\cup&space;a[k]&space;)" title="1-P(a[1]\cup a[2]\cup a[3]\cup ...\cup a[k] )" />  
转化成容斥原理图得到的也就是  
<img src="https://latex.codecogs.com/svg.image?\begin{align}&space;&space;1&-(P(a[1])&plus;P(a[2])&plus;...&plus;P(a[k]))\\&space;&&plus;&space;(P(a[1]\cap&space;a[2])&plus;P(a[1]\cap&space;a[3])&plus;...&plus;P(a[k-1]\cap&space;a[k]))&space;\\&-(P(a[1]\cap&space;a[2]\cap&space;a[3])&plus;P(a[1]\cap&space;a[2]\cap&space;a[4])&plus;...&plus;P(a[k-2]\cap&space;a[k-1]\cap&space;a[k]))\\&...\end{align}" title="\begin{align} 1&-(P(a[1])+P(a[2])+...+P(a[k]))\\ &+ (P(a[1]\cap a[2])+P(a[1]\cap a[3])+...+P(a[k-1]\cap a[k])) \\&-(P(a[1]\cap a[2]\cap a[3])+P(a[1]\cap a[2]\cap a[4])+...+P(a[k-2]\cap a[k-1]\cap a[k]))\\&...\end{align}" />    
转化成公式就是  
<img src="https://latex.codecogs.com/svg.image?C_m^k(\sum_{i=1}^{k}(-1)^{k-i}C_k^ii(i-1)^{n-1})" title="C_m^k(\sum_{i=1}^{k}(-1)^{k-i}C_k^ii(i-1)^{n-1})" />  
那么就开卢卡斯定理求解即可  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#define ll long long
using namespace std;

const int mod = 1e9 + 7;

ll inv[1000010]; // 预处理很重要

inline ll ksm ( ll a, ll b, ll p ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a % p;
                a = a * a % p;
                b >>= 1;
        }
        return res;
}

inline void Init () {
        for ( ll i = 1; i < 1000010; i ++ ) inv[i] = ksm(i, mod - 2, mod);
}

inline ll C ( ll n, ll m, ll p ) {
        if ( m > n ) return 0;
        ll res = 1;
        for ( ll i = 1; i <= m; i ++ ) {
                ll a = (n + i - m) % p;
                ll b = i % p;
                res = res * (a * ksm(b, mod - 2, mod) % p) % p;
        }
        return res;
}

inline ll lucas ( ll n, ll m, ll p ) {
        if ( m == 0 ) return 1;
        return C( n % p, m % p, p ) * lucas ( n / p, m / p, p ) % p;
}

int main () {
        Init();
        int cass;
        for ( scanf("%d", &cass); cass; cass -- ) {
                ll n, m, k; scanf("%lld%lld%lld", &n, &m, &k);
                ll tmp = 1;
                ll res =  0;
                for ( int i = 1; i <= k; i ++ ) {
                        int flag = (k - i) % 2 == 0 ? 1 : -1; // 这一位该加该减
                        tmp = ((tmp * (k - i + 1)) % mod * inv[i]) % mod; // 不用每遍都lucas，推着用着即可
                        res = (res + flag * (i * ksm(i - 1, n - 1, mod) % mod) * tmp % mod + mod) % mod;
                }
                printf("%lld\n", res * lucas(m, k, mod) % mod);
        }
        return 0;
}
```
