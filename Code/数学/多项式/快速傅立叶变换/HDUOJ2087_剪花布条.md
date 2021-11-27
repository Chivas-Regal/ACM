# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=2087"><img src="https://i.loli.net/2021/08/22/i15QuOEZDmw2jGH.png"></a>

# 💡
本题可以使用fft去写  
对每个字符c建立一个多项式，系数表示当前位是不是c，如果是为1，不是为0  
b字符串反着建之后，每一次匹配可以与a的每一位形成一个固定的指数  
然后直接访问指数得到c字符的贡献值即可  
如果贡献值满m，那么就匹配成功，指针向后移动m位  
否则匹配不成功，指针移动一位  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;


const int N = 3010;
const double PI = acos(-1.0);

int n, m;
struct Complex {
        double x, y;
        Complex friend operator + ( Complex a, Complex b ) { return {a.x + b.x, a.y + b.y}; }
        Complex friend operator - ( Complex a, Complex b ) { return {a.x - b.x, a.y - b.y}; }
        Complex friend operator * ( Complex a, Complex b ) { return { a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
} a[N], b[N]; 
int rev[N]; 
int bit, tot; 

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

string sa, sb;
int res[N];

inline void Solve ( char c ) {
        for ( int i = 0; i < N; i ++ ) a[i] = b[i] = {0, 0};
        for ( int i = 0; i < n; i ++ ) a[i].x = sa[i] == c;
        for ( int i = 0; i < m; i ++ ) b[m - i - 1].x = sb[i] == c;
        FFT(a, 1); FFT(b, 1);
        for ( int i = 0; i <= m + n - 2; i ++ ) a[i] = a[i] * b[i];
        FFT(a, -1);
        for ( int i = m - 1; i <= n - 1; i ++ ) res[i] += (int)(a[i].x / tot + 0.5);
}

int main () {

#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif

        while ( cin >> sa && sa != "#" ) { cin >> sb;
                
                memset( res, 0, sizeof res ); // 重启一下res数组
                memset( rev, 0, sizeof rev ); 
                tot = 0, bit = 0;
                
                n = sa.size(), m = sb.size();
                // 搭建rev数组
                while ( (1ll << bit) <= n + m - 2 ) bit ++; tot = 1ll << bit;
                for ( int i = 0; i <= n + m - 2; i ++ ) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
                
                // 把出现的字符扔进去
                map<char, int> chr;
                for ( int i = 0; i < n; i ++ ) chr[sa[i]] ++;
                for ( int i = 0; i < m; i ++ ) chr[sb[i]] ++;
                for ( auto i : chr ) Solve(i.first); // 各跑一遍积累贡献值
                
                int RES = 0;
                int id = m - 1; while ( id <= n - 1 ) {
                        if ( res[id] == m ) id += m, RES ++;
                        else id ++;
                }
                cout << RES << endl;

        }
}
```
