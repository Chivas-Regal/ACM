# 🔗
<a href="https://codeforces.com/problemset/problem/608/B"><img src="https://i.loli.net/2021/09/09/rladEgOGcVRpSxH.png"></a>

# 💡
求每一步匹配不上的数量  
也就是不相似度的累加和  
我们可以求一下相似度，然后  
用所有都相似的相似度减去我们求到的相似度累加和就是不相似度的累加和  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
using namespace std;
#define ll long long

const ll N = 1000010;
const double PI = acos(-1.0);
ll res[N];

ll n, m;
struct Complex {
        double x, y;
        Complex friend operator + ( Complex a, Complex b ) { return {a.x + b.x, a.y + b.y}; }
        Complex friend operator - ( Complex a, Complex b ) { return {a.x - b.x, a.y - b.y}; }
        Complex friend operator * ( Complex a, Complex b ) { return { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
} a[N], b[N];
ll rev[N];
ll bit, tot; 
string sa, sb;

inline void FFT ( Complex a[], ll inv ) {
        for ( ll i = 0; i < tot; i ++ ) if ( i < rev[i] ) swap(a[i], a[rev[i]]);
        for ( ll mid = 1; mid < tot; mid <<= 1 ) {
                Complex w1 = {cos(PI / mid), inv * sin(PI / mid)};
                for ( ll i = 0; i < tot; i += mid * 2 ) {
                        Complex wk = {1, 0};
                        for ( ll j = 0; j < mid; j ++, wk = wk * w1 ) {
                                Complex x = a[i + j], y = wk * a[i + j + mid];
                                a[i + j] = x + y, a[i + j + mid] = x - y;
                        }
                }
        }
}

inline void Solve ( char c ) {
        for ( ll i = 0; i < N; i ++ ) a[i] = b[i] = {0, 0};
        for ( ll i = 0; i < n; i ++ ) a[i].x = (sa[i] == c);
        for ( ll i = 0; i < m; i ++ ) b[i].x = (sb[m - i - 1] == c);
        FFT(a, 1); FFT(b, 1);
        for ( ll i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        FFT(a, -1);  
        for ( ll i = m - 1; i <= n + m - 2; i ++ ) {
                res[i] += (ll)(a[i].x / tot + 0.5);
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif

        cin >> sb >> sa;
        n = sa.size(), m = sb.size();
        while ( (1ll << bit) <= n + m - 2 ) bit ++; tot = 1ll << bit;
        for ( ll i = 0; i < tot; i ++ ) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        Solve('1'); Solve('0');
        ll RES = (n - m + 1) * m; // 都完美匹配上的情况
        for ( ll i = m - 1; i <= n - 1; i ++ ) RES -= res[i]; // 减去相似度
        cout << RES << endl;
}
```
