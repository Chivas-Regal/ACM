# 🔗
<a href="https://www.luogu.com.cn/problem/P1919"><img src="https://i.loli.net/2021/08/18/C23OHeJhcURbf6d.png"></a>

# 💡
我们可以把A转变为一个多项式  
<img src="https://latex.codecogs.com/svg.image?A=A(x)=a_0x^0&plus;a_1x^1&plus;...&plus;a_nx^n" title="A=A(x)=a_0x^0+a_1x^1+...+a_nx^n" />  
B同理  
此时我们想求出两者的积，也就是把A(x)*B(x)  
然后得到的C(x)，对系数转换10进制即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int N = 3000010;
const double PI = acos(-1.0);

int n, m;
struct Complex { // 复数结构体
        double x, y;
        Complex friend operator + ( Complex a, Complex b ) { return {a.x + b.x, a.y + b.y}; }
        Complex friend operator - ( Complex a, Complex b ) { return {a.x - b.x, a.y - b.y}; }
        Complex friend operator * ( Complex a, Complex b ) { return { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
} a[N], b[N];
int rev[N];
int bit, tot;
int res[N];

inline void FFT ( Complex a[], int inv ) {
        for ( int i = 0; i < tot; i ++ ) if ( i < rev[i] ) swap(a[i], a[rev[i]]);
        for ( int mid = 1; mid < tot; mid <<= 1 ) { 
                Complex w1 = {cos(PI / mid), inv * sin(PI / mid)};
                for ( int i = 0; i < tot; i += mid * 2 ) {
                        Complex wk = {1, 0}; 
                        for ( int j = 0; j < mid; j ++, wk = wk * w1 ) {
                                Complex x = a[i + j], y = wk * a[i + j + mid];
                                a[i + j] = x + y, a[i + j + mid] = x - y;
                        }
                }
        }
}

int main() {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
#endif
        string sa, sb;
        cin >> sa >> sb; n = sa.size() - 1, m = sb.size() - 1;
        for ( int i = 0; i <= n; i ++ ) a[i].x = sa[n - i] - '0'; // 每一位拆出来给实部
        for ( int i = 0; i <= m; i ++ ) b[i].x = sb[m - i] - '0';
        while ( (1 << bit) < n + m + 1 ) bit ++;
        tot = 1 << bit;
        for ( int i = 0; i < tot; i ++ ) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        FFT( a, 1 ); FFT( b, 1 );
        for ( int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        FFT( a, -1 );
        
        int nxt = 0;
        for ( int i = 0; i <= n + m + 1; i ++ ) {
                res[i] = (nxt + (int)(a[i].x / tot + 0.5)) % 10;
                nxt = (nxt + (int)(a[i].x / tot + 0.5)) / 10;
        }
        int i = n + m + 1;
        while ( res[i] == 0 ) i --;
        for ( ; i >= 0; i -- ) cout << res[i]; // 整合给res输出
        return 0;
}
        
/*
FFT:            1524157891004055895123067864200200646789061868481059858831257643955833850367278502666927131954920793240938240966819899216931602390126499790993189428688835402911622011521694514727469596012471524
BigInteger:
        1524157891004055895125653722788645091233506312925504303275702088400278294811722947111371576399365237685382685411264343661376046834570944235437633873133279847355807870107294514727469596012471524
*/
```
