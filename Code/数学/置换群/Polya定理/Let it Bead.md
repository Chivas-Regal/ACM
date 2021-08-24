# 🔗
<a href="http://poj.org/problem?id=2409"><img src="https://i.loli.net/2021/08/24/vUWQXsbVMPpfk8o.png"></a>

# 💡
首先考虑有多少种置换  
1.旋转置换  
转<img src="https://latex.codecogs.com/svg.image?k" title="k" />次，<img src="https://latex.codecogs.com/svg.image?k=0,1,...,n-1" title="k=0,1,...,n-1" />  
<img src="https://latex.codecogs.com/svg.image?d&space;=&space;gcd(n,&space;k)" title="d = gcd(n, k)" />  
出现循环的点为  
<img src="https://latex.codecogs.com/svg.image?x&plus;kt\equiv&space;x(mod\;n)" title="x+kt\equiv x(mod\;n)" />  
<img src="https://latex.codecogs.com/svg.image?kt\equiv&space;0(mod\;n)\Rightarrow&space;kt&plus;nr=0" title="kt\equiv 0(mod\;n)\Rightarrow kt+nr=0" />  
解方程 <img src="https://latex.codecogs.com/svg.image?t=\frac&space;nd" title="t=\frac nd" />  
即最少转<img src="https://latex.codecogs.com/svg.image?\frac&space;nd" title="\frac nd" />步会出现循环  
长为n，有n/d哥循环点，所以总循环数=<img src="https://latex.codecogs.com/svg.image?\frac{n}{\frac{n}{d}}" title="\frac{n}{\frac{n}{d}}" />  
得到式子：总不动点数=<img src="https://latex.codecogs.com/svg.image?\sum\limits_{k=0}^{n-1}m^{gcd(n,k)}" title="\sum\limits_{k=0}^{n-1}m^{gcd(n,k)}" />  
  
2.翻转置换  
1>n为奇数><img src="https://latex.codecogs.com/svg.image?n*m^{\frac{n&plus;1}2}" title="n*m^{\frac{n+1}2}" />  
2>n为偶数>穿过某个点><img src="https://latex.codecogs.com/svg.image?\frac&space;n2*m^{\frac&space;n2&space;&plus;&space;1}" title="\frac n2*m^{\frac n2 + 1}" />  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不穿某个点><img src="https://latex.codecogs.com/svg.image?\frac&space;n2*m^{\frac&space;n2}" title="\frac n2*m^{\frac n2}" />  
  
最后所有的不动点数相加除 2*n 即可

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#define ll long long

using namespace std;

inline int gcd ( int a, int b ) {
        return b ? gcd(b, a % b) : a;
}
inline ll ksm ( int a, int b ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a;
                a = a * a;
                b >>= 1;
        }
        return res;
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        int m, n;
        while ( cin >> m >> n , m || n ) {
                ll res = 0;
                //旋转置换
                for ( int i = 0; i < n; i ++ ) res += ksm(m, gcd(n, i));
                //翻转置换
                if ( n % 2 ) res += n * ksm(m, (n + 1) / 2);
                else res += n / 2 * (ksm(m, n / 2 + 1) + ksm(m, n / 2));
                cout << res / (n * 2) << endl;
        }
}
```
