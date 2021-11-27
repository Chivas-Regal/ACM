# 🔗
<a href="https://codeforces.com/contest/1569/problem/C"><img src="https://i.loli.net/2021/09/09/feoEr5vRHgldT9p.png"></a>

# 💡
观察题目转换一下题目问题  
即最大值的后面至少有一个可以让最大值最后一步和倒数第二步不在一起的数  
那么如果最大值有两个，怎么搞都可以  
如果最大值和次大值的差值大于1则怎么搞都不行  
然后就是最大值和次大值差值为1的情况  
  
获取一下所有的排列方式即<img src="https://latex.codecogs.com/svg.image?n!" title="n!" />  
然后最大值在最后是不可以的，所以要减去<img src="https://latex.codecogs.com/svg.image?(n-1)!" title="(n-1)!" />  
然后计算所有次大值都在最大值前面的情况  
  
我们设置<img src="https://latex.codecogs.com/svg.image?a_0" title="a_0" />是最大值，<img src="https://latex.codecogs.com/svg.image?a_1" title="a_1" />是次大值，<img src="https://latex.codecogs.com/svg.image?num_i" title="num_i" />是<img src="https://latex.codecogs.com/svg.image?i" title="i" />出现的个数  
最大值前面至少要留下<img src="https://latex.codecogs.com/svg.image?num_{a_1" title="num_{a_1" />，最多就是<img src="https://latex.codecogs.com/svg.image?n-2" title="n-2" />个  
那么我们以<img src="https://latex.codecogs.com/svg.image?i" title="i" />遍历  
将<img src="https://latex.codecogs.com/svg.image?num_{a_1" title="num_{a_1" />个数不记顺序地放入<img src="https://latex.codecogs.com/svg.image?i" title="i" />个空中  
即<img src="https://latex.codecogs.com/svg.image?C_i^{num_{a_1}}" title="C_i^{num_{a_1}}" />  
然后对这<img src="https://latex.codecogs.com/svg.image?num_{a_1" title="num_{a_1" />个数考虑顺序，对其余的<img src="https://latex.codecogs.com/svg.image?n-num_{a_1}-1" title="n-num_{a_1}-1" />个数考虑顺序  
即都是阶乘  
那么就有公式：  
<img src="https://latex.codecogs.com/svg.image?n!-(n-1)!-\sum\limits_{i=num_{a_1}}^{n-2}\{C_i^{num_{a_1}}\times&space;num_{a_1}!\times&space;(n-1-num_{a_1})!\}" title="n!-(n-1)!-\sum\limits_{i=num_{a_1}}^{n-2}\{C_i^{num_{a_1}}\times num_{a_1}!\times (n-1-num_{a_1})!\}" />  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <cstring>
#include <list>
using namespace std;
#define ll long long
const int N = 200005;
const ll mod = 998244353;

ll a[N];
ll f[N];
ll n;
map<ll, ll> num;
inline void get_F () {
        f[0] = 1;
        for ( int i = 1; i < N; i ++ ) {
                f[i] = f[i - 1] * i % mod;
        }
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
inline ll C ( ll a, ll b ) { 
        return f[a] * ksm(f[b], mod - 2) % mod * ksm(f[a - b], mod - 2) % mod;
}
inline void solve () {
        num.clear();
        cin >> n;
        for ( int i = 0; i < n; i ++ ) 
                cin >> a[i],
                num[a[i]] ++;
        sort ( a, a + n, [] ( ll a, ll b ) { return a > b; } );
        
        if ( a[0] - a[1] > 1 ) { // 最后一个要自己一个连续减好多次
                cout << 0 << endl;
        } else if ( num[a[0]] > 1 ) { // 自己和自己顶，可以随便搞
                cout << f[n] << endl;
        } else {
                ll res = f[n]; // 初始化为所有的情况
                ll del = f[n - 1]; // 要删去的不符合的情况
                for ( int i = num[a[1]]; i <= n - 2; i ++ ) {
                        del = ( del + C(i, num[a[1]]) * f[num[a[1]]] % mod * f[n - 1 - num[a[1]]] % mod ) % mod;
                }
                cout << ( ( res - del ) % mod + mod) % mod << endl;
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        get_F();
        ll cass; cin >> cass; while ( cass -- ) {
                solve();
        }
}
```
