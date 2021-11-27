# 🔗
<a href="https://codeforces.com/contest/1443/problem/C"><img src="https://i.loli.net/2021/08/29/QWYzrOhCki31lPe.png"></a>

# 💡
本题有一个题意里面待挖掘的性质：如果点了一家外卖，则比这家用时更短的外卖不会花费任何时间  
那么就比较明显了，我们可以枚举一下外卖用时的上界，超上界的全自己去买就行  
那么按外卖用时排个序  
然后维护一下当前外卖用时和自己去买用时的后缀和的最大值的最小值即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long

using namespace std;



const ll N = 2e5 + 10;

inline bool cmp ( pair<ll, ll> a, pair<ll, ll> b ) {
        return a.first < b.first;
}

inline void Solve () {
        ll n; scanf("%lld", &n);
        vector<pair<ll, ll> > a; a.push_back({0, 0});
        for ( ll i = 1, x; i <= n; i ++ ) scanf("%lld", &x), a.push_back({x, 0});
        for ( ll i = 1, x; i <= n; i ++ ) scanf("%lld", &x), a[i].second = x;
        
        sort ( a.begin(), a.end(), cmp );
        
        ll res = 1e18, self_time = 0; // 自己去买的用时和
        for ( int i = n; i >= 0; i -- ) {
                res = min ( res, max ( self_time, a[i].first ) );
                self_time += a[i].second;
        }
        printf("%lld\n", res);
}

int main () {
        ll cass; scanf("%lld", &cass); while ( cass -- ) {
                Solve();
        }
}

```
