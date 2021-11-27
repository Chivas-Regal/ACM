# 🔗
<a href="https://codeforces.com/problemset/problem/613/A"><img src="https://i.loli.net/2021/09/09/r3vLKBtR5mHdnEf.png"></a>

# 💡
一个计算几何问题  
首先我们考虑外围圆半径R，就是离圆心最远的直接就可以从点中找到  
但是考虑内圈圆半径r的时候，我们需要寻找圆心到边的最近距离即可（计算几何板子扔上去）  
最后答案就是 ( R * R - r * r ) * PI  

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
const ll mod = 998244353;
const double PI = acos(-1.0);
const double eps = 1e-9;

inline ll sgn ( double x ) {
        if ( x < -1e-9 ) return -1;
        else if ( x > 1e-9 ) return 1;
        return 0;
}

struct point {
        double x, y;
        point () {}
        point ( double a, double b ) : x(a), y(b) {}
        point operator + ( point b ) const {
                return point ( x + b.x, y + b.y );
        }
        point operator - ( point b ) const {
                return point ( x - b.x, y - b.y );
        }
        double operator * ( point b ) const {
                return x * b.x + y * b.y;
        }
        double operator ^ ( point b ) const {
                return x * b.y - y * b.x;
        }
};

inline point proj ( point a, point k1, point k2 ) {
        point res;
        double dx = k1.x - k2.x;
        double dy = k1.y - k2.y;
        double u = (a.x - k1.x) * (k1.x - k2.x) + (a.y - k1.y) * (k1.y - k2.y);
        u = u / ((dx * dx) + (dy * dy));
        res.x = k1.x + u * dx;
        res.y = k1.y + u * dy;
        return res;
}

inline bool OnSeg ( point p, point a, point b ) {
        return sgn ( ( a - p ) ^ ( b - p ) ) == 0 &&
        sgn ( (p.x - a.x) * (p.x - b.x) ) <= 0 &&
        sgn ( ( p.y - a.y ) * (p.y - b.y) );
}

inline double dist ( point a, point b ) {
        double dirx = a.x - b.x;
        double diry = a.y - b.y;
        return sqrt ( dirx * dirx + diry * diry );
}

inline point PointLine ( point p, point a, point b ) {
        point result;
        double t = ( ( p - a ) * ( b - a ) ) / ( ( b - a ) * ( b - a ));
        if ( t >= 0 && t <= 1 ) {
                result.x = a.x + (b.x - a.x) * t;
                result.y = a.y + (b.y - a.y) * t;
        } else {
                if ( dist ( p, a ) < dist ( p, b ) ) result = a;
                else result = b;
        }
        return result;
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        ll n;
        double X, Y; 
        cin >> n >> X >> Y;
        point PT = {X, Y};
        vector<point> pt;
        double r = 10000000000000000, R = 0;
        for ( ll i = 0; i < n; i ++ ) {
                double a, b; cin >> a >> b;
                pt.push_back({a, b});
                if ( dist(PT, pt.back()) - R > eps ) R = dist(PT, pt.back());
        }
        for ( int i = 0; i < n; i ++ ) {
                point near = PointLine ( PT, pt[i], pt[(i + 1) % n]);
                if ( r - dist(PT, near) > eps ) r = dist(PT, near);
        }

        printf("%.10f\n", (R * R - r * r) * PI);
}
```
