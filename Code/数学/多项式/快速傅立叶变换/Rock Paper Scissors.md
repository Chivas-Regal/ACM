# 🔗
<a href="https://codeforces.com/gym/101667/attachments"><img src="https://i.loli.net/2021/08/21/Y7k9Mf3lQIoJaEe.png"></a>

# 💡
本题是用于解决字符串匹配相似度的  
本题最朴素的写法就是暴力匹配，然后时间是O(nm)，稳T  
最显眼的还是只有三个字符，字符串在一位一位匹配的时候，很像多项式卷积的过程，用到一位对应一位求解  
那么其实可以反转一下b串，让这个对应刚好使得指数为定值  
那么我们也可以利用多项式卷积，把一个字符串以某个字符匹配时的相似度做一个多项式  
即我们在以字符c匹配时令一个位置的系数为[s[i]=c]  
那么可以构造出这样一个多项式  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}&a_0x^0&plus;a_1x^1&plus;a_2x^2&plus;a_3x^3\\&b_0x^2&plus;x_1x^1&plus;x_2x^0&space;\end{aligned}&space;" title="\begin{aligned}&a_0x^0+a_1x^1+a_2x^2+a_3x^3\\&b_0x^2+x_1x^1+x_2x^0 \end{aligned} " />  
这样在第一次匹配时，即寻找指数为2的卷积结果。第二次匹配时寻找指数为3的卷积结果...  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 300010;
const double PI = acos(-1.0);
int res[N];

int n, m;
struct Complex { // 复数结构体
        double x, y;
        Complex friend operator + ( Complex a, Complex b ) { return {a.x + b.x, a.y + b.y}; }
        Complex friend operator - ( Complex a, Complex b ) { return {a.x - b.x, a.y - b.y}; }
        Complex friend operator * ( Complex a, Complex b ) { return { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
} a[N], b[N];
int rev[N];
int bit, tot; 
string sa, sb;

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

inline void Solve ( char c ) {
        for ( int i = 0; i < N; i ++ ) a[i] = b[i] = {0, 0};
        for ( int i = 0; i < n; i ++ ) a[i].x = (sa[i] == c);
        for ( int i = 0; i < m; i ++ ) b[i].x = (sb[m - i - 1] == c);
        FFT(a, 1); FFT(b, 1);
        for ( int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
        FFT(a, -1);  
        for ( int i = m - 1; i <= n + m - 2; i ++ ) {
                res[i] += (int)(a[i].x / tot + 0.5);
        }
}

int main () {
        cin >> n >> m >> sa >> sb;
        for ( int i = 0; i < m; i ++ ) {
                if ( sb[i] == 'S' ) sb[i] = 'P';
                else if ( sb[i] == 'P' ) sb[i] = 'R';
                else sb[i] = 'S';
        }
        while ( (1ll << bit) <= n + m - 2 ) bit ++; tot = 1ll << bit;
        for ( int i = 0; i < tot; i ++ ) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

        Solve('R'); Solve('S'); Solve('P');
        int RES = 0;
        for ( int i = m - 1; i <= n + m - 2; i ++ ) RES = max ( RES, res[i] );
        cout << RES << endl;
}
```
