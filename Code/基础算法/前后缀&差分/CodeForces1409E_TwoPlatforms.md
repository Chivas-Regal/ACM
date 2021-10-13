# 🔗
<a href="https://codeforces.com/problemset/problem/1409/E"><img src="https://i.loli.net/2021/09/26/y8aDkSu6xjUotqs.png"></a>

# 💡
首先分析这是两块板子，必然是一前一后  
那么我们可以设置一个前缀最大覆盖，一个后缀最大覆盖  
每次对当前的球二分出最多能覆盖多少个点，并将当前的前缀或者后缀赋值为`max(之前的覆盖最大值，这一次点覆盖最大值)`  
然后枚举断点，扫一遍维护一下`max(res, pre[i] + nxt[i + 1])`  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
 
using namespace std;

const int N = 2e5 + 10;
ll n, k;
ll a[N];
ll pre[N], nxt[N]; // 前缀挡球最大个数，后缀挡球最大个数  
 
int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        ll cass; scanf("%lld", &cass); while ( cass -- ) {
                scanf("%lld%lld", &n, &k);
                a[0] = a[n + 1] = 1e18;
                pre[0] = nxt[n + 1] = 0;

                for ( int i = 1; i <= n; i ++ ) scanf("%lld", &a[i]);
                for ( int i = 1, x; i <= n; i ++ ) scanf("%d", &x); // 高度没啥用
                sort ( a + 1, a + n + 1 );

                for ( int i = 1; i <= n; i ++ ) 
                        pre[i] = max ( pre[i - 1], (ll)i - (lower_bound(a + 1, a + i + 1, a[i] - k) - a) + 1); // 向前二分
                for ( int i = n; i >= 1; i -- ) 
                        nxt[i] = max ( nxt[i + 1], ((ll)(upper_bound(a + i, a + n + 1, a[i] + k) - a) - 1) - i + 1); // 向后二分
                ll res = 0;
                for ( int i = 0; i <= n; i ++ ) res = max ( res, pre[i] + nxt[i + 1] );
                printf("%lld\n", res);
        }
}
```
