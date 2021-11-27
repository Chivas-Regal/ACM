# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=1398"><img src="https://i.loli.net/2021/08/18/nEyv2pHq3jJmoZe.png"></a>

# 💡
与<a href="https://github.com/Chivas-Regal/ACM/blob/main/Code/%E6%95%B0%E5%AD%A6/%E5%A4%9A%E9%A1%B9%E5%BC%8F/%E5%BF%AB%E9%80%9F%E5%82%85%E7%AB%8B%E5%8F%B6%E5%8F%98%E6%8D%A2/Ignatius%20and%20the%20Princess%20III.md">FFT加速母函数</a>一样，这里构造的多项式的系数为1的条件是i%(k*k)==0  
同样的，在枚举下一个括号的最后一个1时，使用m=num/(k*k)*(k*k)

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int N = 10210;
const double PI = acos(-1.0);

int n, m, num;
struct Complex { // 复数结构体
        double x, y;
        Complex () {}
        Complex ( double _x, double _y ) : x(_x), y(_y) {}
        Complex friend operator+(Complex a, Complex b) { return {a.x + b.x, a.y + b.y}; }
        Complex friend operator-(Complex a, Complex b) { return {a.x - b.x, a.y - b.y}; }
        Complex friend operator*(Complex a, Complex b) { return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }
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

int main(){
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
#endif
        num = 300;
        for ( int i = 0; i <= num; i ++ ) a[i].x = 1;
        n = num;
        for ( int k = 2; k <= 17; k ++ ){
                m = num / (k * k) * (k * k);
                
                while ( (1 << bit) < n + m + 1 ) bit ++;
                tot = 1 << bit;
                
                // b的重启读入
                for ( int i = 0; i <= m; i ++ ) b[i].x = (i % (k * k) == 0), b[i].y = 0; // k的倍数为1，否则为0。 虚部固定为0
                for ( int i = m + 1; i < tot; i ++ ) b[i].x = 0, b[i].y = 0; // 后面的实部和虚部也要为0

                // rev数组的更新
                for ( int i = 0; i < tot; i ++ ) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)); // 二进制反转
                
                FFT(a, 1); FFT(b, 1);
                for ( int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
                FFT(a, -1);
                
                // a的重启读入
                for ( int i = 0; i <= n + m; i ++ ) a[i] = {(double)(int)(a[i].x / tot + 0.5), 0}; // 读入后虚部重启为0
                for ( int i = n + m + 1; i <= N; i ++ ) a[i] = {0, 0}; // 实部虚部重启为0
                
                n += m; // 第一个多项式扩到n + m
        }
        
        while ( scanf("%d", &num) == 1 && num ){
                printf("%d\n", (int)(a[num].x + 0.5));
        }
}





/*

int elem[18] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289};

*/
```
