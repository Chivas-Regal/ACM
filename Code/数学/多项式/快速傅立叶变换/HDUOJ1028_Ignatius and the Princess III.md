# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=1028"><img src="https://user-images.githubusercontent.com/78973908/129878123-d4c3d1ed-f1ad-47b1-a647-ea4bec8c8d37.png"></a>

# 💡
本题就是一个母函数的模板题  
这里使用FFT优化  
  
1.构造本问题的生成函数  
<img src="https://latex.codecogs.com/svg.image?(1&plus;x&plus;x^2&plus;...&plus;x^n)*(1&plus;x^2&plus;x^4&plus;...&plus;x^{\left\lfloor\frac&space;n2\right&space;\rfloor&space;*&space;2})*(1&plus;x^3&plus;x^6&plus;...&plus;x^{\left\lfloor\frac&space;n3\right&space;\rfloor&space;*&space;3})&space;*..." title="(1+x+x^2+...+x^n)*(1+x^2+x^4+...+x^{\left\lfloor\frac n2\right \rfloor * 2})*(1+x^3+x^6+...+x^{\left\lfloor\frac n3\right \rfloor * 3}) *..." />  
  
2.转移为多项式问题  
<img src="https://latex.codecogs.com/svg.image?(1&plus;1x&plus;1x^2&plus;...&plus;1x^n)*(1&plus;0x^1&plus;1x^2&plus;0x^3&plus;1x^4&plus;...&plus;1x^{\left&space;\lfloor&space;\frac&space;n2\right&space;\rfloor*2})*...." title="(1+1x+1x^2+...+1x^n)*(1+0x^1+1x^2+0x^3+1x^4+...+1x^{\left \lfloor \frac n2\right \rfloor*2})*...." />  
  
每次合并创建的多项式给a  
对b不断地重启与清零，a在求得后对虚部与某些实部清零    
  
<span style="color: orange;">PS:小数据不推荐使用FFT，常数较大有些吃亏</span>

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const int N = 30010;
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

inline void FFT(Complex a[], int inv) {
        for ( int i = 0; i < tot; i ++ ) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for ( int mid = 1; mid < tot; mid <<= 1) {
                Complex w1 = {cos(PI / mid), inv * sin(PI / mid)};
                for ( int i = 0; i < tot; i += mid * 2 ) {
                        Complex wk = {1, 0};
                        for (int j = 0; j < mid; j++, wk = wk * w1) {
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
        num = 120;
        for ( int i = 0; i <= num; i ++ ) a[i].x = 1;
        n = num;
        for ( int k = 2; k <= num; k ++ ){
                m = num / k * k;
                
                while ( (1 << bit) < n + m + 1 ) bit ++;
                tot = 1 << bit;
                
                // b的重启读入
                for ( int i = 0; i <= m; i ++ ) b[i].x = (i % k == 0), b[i].y = 0; // k的倍数为1，否则为0。 虚部固定为0
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
        
        while ( scanf("%d", &num) == 1 ){
                printf("%d\n", (int)(a[num].x + 0.5));
        }
}
```
