# 🔗
<a href="https://codeforces.com/contest/1594/problem/D"><img src="https://i.loli.net/2021/10/09/OndVD6NqE1yFbIX.png"></a>

# 💡
首先要从人物关系中下手  
如果一个人说另一个人是船员，那么两个要么都是船员要么都不是  
如果一个人说另一个人是冒牌，那么两个人中必定只有一个是冒牌  
  
我们要求得最大的冒牌数量，可以使用带权并查集  
就是两个人一定同一阵营`merge( x, y ), merge ( x + n, y + n )`  
一定不是同一阵营 `merge ( x, y + n ), merge ( x + n, y )`  
  
在特判的时候，如果一个人自己和自己不是同一阵营，就输出-1  
否则在遇到每个阵营的祖先的时候，从它直接代表的两个阵营中选出一个最大的即 `max(siz[Find(x)], siz[Find(x + n)])`  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

#define ll long long
using namespace std;
const int mod = 1e9 + 7;

inline ll ksm ( ll a, ll b ) {
	ll res = 1;
	while ( b ) {
		if ( b & 1 ) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

inline void Solve() {
	ll a, b; cin >> a >> b;
	ll res = 0;
	while ( b > 0 ) {
		ll bas = 0, sum = 0;
		while ( sum + (1ll << bas) < b ) {
			sum += (1ll << bas);
			bas ++;
		}
		res = (res + ksm(a, bas)) % mod;
		b -= (1ll << bas);
	}
	cout << res << endl;

}

int main () {
	ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
	int cass; cin >> cass; while ( cass -- ) {
		Solve();
	}
        return 0;
}
```
