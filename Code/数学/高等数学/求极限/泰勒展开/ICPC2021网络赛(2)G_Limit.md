# 🔗
<a href="https://pintia.cn/problem-sets/1441745686294945792/problems/1441745856154955782"><img src="https://i.loli.net/2021/09/26/RVhr9M2Of1sINXc.png"></a>

# 💡
首先根据泰勒展开可得  
<img src="https://latex.codecogs.com/svg.image?ln(1&plus;x)&space;=&space;x-\frac{x^2}2&plus;\frac{x^3}3-\frac{x^4}4&plus;...." title="ln(1+x) = x-\frac{x^2}2+\frac{x^3}3-\frac{x^4}4+...." />  
我们想找指数最小的第一个系数不为0的项  
如果它的指数<img src="https://latex.codecogs.com/svg.image?=t" title="=t" />，可以求系数  
如果<img src="https://latex.codecogs.com/svg.image?<t" title="<t" />，就输出<img src="https://latex.codecogs.com/svg.image?inf" title="inf" />  
如果<img src="https://latex.codecogs.com/svg.image?>t" title=">t" />，就输出<img src="https://latex.codecogs.com/svg.image?0" title="0" />  
  
那么对于第<img src="https://latex.codecogs.com/svg.image?j" title="j" />项也就是<img src="https://latex.codecogs.com/svg.image?x^j" title="x^j" />的时候，每一对<img src="https://latex.codecogs.com/svg.image?a[i],&space;b[i])" title="a[i], b[i])" />可以选出<img src="https://latex.codecogs.com/svg.image?(-1)^{j-1}\frac{a_ib_i^j}j" title="(-1)^{j-1}\frac{a_ib_i^j}j" />作为系数  
所以分子可以枚举<img src="https://latex.codecogs.com/svg.image?\sum\limits_{j\ge1}x^{j}(-1)^{j-1}\sum\limits_{1\le&space;i\le&space;n}\frac{a_ib_i^j}j" title="\sum\limits_{j\ge1}x^{j}(-1)^{j-1}\sum\limits_{1\le i\le n}\frac{a_ib_i^j}j" />    
在指数<img src="https://latex.codecogs.com/svg.image?\le&space;t" title="\le t" />时，如果遇到系数不为<img src="https://latex.codecogs.com/svg.image?0" title="0" />，首先判断<img src="https://latex.codecogs.com/svg.image?j" title="j" />是否为<img src="https://latex.codecogs.com/svg.image?t" title="t" />  
如果<img src="https://latex.codecogs.com/svg.image?j=t" title="j=t" />，满足条件，跳出循环可以开始求系数（分数，up和down）    
如果<img src="https://latex.codecogs.com/svg.image?j<t" title="j<t" />就说明存在指数比t小且系数不为0的，那么就是<img src="https://latex.codecogs.com/svg.image?inf" title="inf" />  
  
如果系数一直为<img src="https://latex.codecogs.com/svg.image?0" title="0" />且<img src="https://latex.codecogs.com/svg.image?j>t" title="j>t" />，那么最大的项也要比<img src="https://latex.codecogs.com/svg.image?x^t" title="x^t" />小，所以输出<img src="https://latex.codecogs.com/svg.image?0" title="0" />  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
 
using namespace std;
 
inline ll ksm ( ll a, ll b ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a;
                a = a * a;
                b >>= 1;
        }
        return res;
}
inline ll gcd ( ll a, ll b ) {
        return b ? gcd ( b, a % b ) : a;
}

int main () {
        ll n, t; cin >> n >> t;
        ll a[n], b[n];
        for ( ll i = 0; i < n; i ++ ) cin >> a[i] >> b[i];

        ll up = 0, down = 0;
        for ( ll j = 1; ; j ++ ) {
                if ( j > t ) { cout << "0"; return 0; } // 最大的项比x^t小
                up = 0, down = j;
                for ( ll i = 0; i < n; i ++ ) up += a[i] * ksm(b[i], j);
                if ( j % 2 == 0 ) up *= -1;
                if ( up ) { // 系数不为0
                        if ( j < t ) { cout << "infinity"; return 0; } // 最大的项比x^t大且存在  
                        break; // 否则开始求系数
                }
        }
        ll d = gcd ( llabs(up), llabs(down) );
        up /= d; down /= d; // 约分
        if ( up % down == 0 ) cout << up / down; // 直接除来求
        else {
                if ( up * down < 0 ) cout << "-"; // 异号，负号提出
                cout << up << "/" << down;
        }
}
```
