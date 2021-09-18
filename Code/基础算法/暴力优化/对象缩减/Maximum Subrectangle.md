# 🔗
<a href="https://codeforces.com/problemset/problem/1060/C"><img src="https://i.loli.net/2021/09/18/EOi7obhT8U9JwNj.png"></a>

# 💡
首先分析问题  
任意两个向量维构成的矩阵两两对应 
同时子区间也能完全对应成立  
所以题目就是让求a序列的某个区间和乘上b序列的某个区间和，在不超过x的情况下，两者长度相乘最大  
  
首先区间和可以很快化为前缀和问题O(1)地减出区间和  
然后可以发现，即然我们要求长度满足条件，所以我们要尽可能让ab数组的某个长度的区间和最小  
这样我们才能让满足条件的区间乘起来最大  
而ab的每个区间都能对应起来，所以一个区间长度的最小值就可以代表同长度的区间  
  
处理一下ab每个长度的区间和的最小值  
对象缩减为区间长度  
这道题就变成了一个枚举区间长度来判断是否满足条件的问题了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define ll long long

using namespace std;

const ll N = 2100;
ll n, m;
ll a[N], b[N]; // 化为前缀和数组
ll lena[N], lenb[N];// lena[i]表示a的子串里面长度为i的最小值，lenb同理
ll res;
ll x;

int main () {
#ifndef ONLINE_JUDGE
        freopen("../in.in", "r", stdin);
        freopen("../out.out", "w", stdout);
#endif
        memset(lena, 0x3f3f3f3f, sizeof lena);
        memset(lenb, 0x3f3f3f3f, sizeof lenb);
        cin >> n >> m;
        for ( ll i = 1; i <= n; i ++ )
                cin >> a[i],
                a[i] += a[i - 1];
        for ( ll i = 1; i <= m; i ++ )
                cin >> b[i],
                b[i] += b[i - 1];

        // 预处理这个最小值
        for ( ll len = 1; len <= n; len ++ )
                for ( ll i = len; i <= n; i ++ )
                        lena[len] = min ( lena[len], a[i] - a[i - len] );
        for ( ll len = 1; len <= m; len ++ )
                for ( ll i = len; i <= m; i ++ )
                        lenb[len] = min ( lenb[len], b[i] - b[i - len] );

        // 如果最小值对应相乘小于x，那么就可以取最大值
        cin >> x;
        for ( ll lna = 1; lna <= n; lna ++ )
                for ( ll lnb = 1; lnb <= m; lnb ++ )
                        if ( lena[lna] * lenb[lnb] <= x )
                                res = max ( res, lna * lnb );
        cout << res << endl;
}

```
