# 🔗
<a href="https://atcoder.jp/contests/abc221/tasks/abc221_e?lang=en"><img src="https://i.loli.net/2021/10/03/zgE36rAUpOTkXHQ.png"></a>

# 💡
问题转化一下就是  
从左向右，a[i]的贡献就是每个前面比它小的a[j]，在这个位置上的贡献为2^{i-j-1}  
由于区间长度总是参差不齐的  
那么对于每个a[j]，我们都可以维护一个前缀贡献为2^{-j-1}  
然后在i的位置的时候的贡献容斥为\frac{2^i}{\sum2^{j+1})即可，其中sum可以由树状数组的前缀得到  
所以每次累加查询a[i]位置以前的总贡献，`query(a[i]) * ksm(2, i)`  
然后在a[i]的位置上更新一下这个前缀贡献，`update( a[i], ksm(ksm(2, i + 1), mod - 2) )`  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 3e5 + 10;
const int mod = 998244353;
ll n, a[N];
vector<ll> nums;

inline ll ksm ( ll a, ll b ) {
	ll res = 1;
	while ( b ) {
		if ( b & 1 ) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

namespace TreeArray {
	ll tr[N];
	inline ll lowbit ( ll x ) {
		return x & -x;
	}
	inline void update ( ll id, ll val ) {
		while ( id < N ) tr[id] = (tr[id] + val) % mod, id += lowbit(id);
	}
	inline ll query ( ll id ) {
		ll res = 0;
		while ( id > 0 ) res = (res + tr[id]) % mod, id -= lowbit(id);
		return res;
	}
} using namespace TreeArray;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	cin >> n;
	ll res = 0;
	for ( int i = 1; i <= n; i ++ ) 
		cin >> a[i],
		nums.push_back(a[i]);
	sort ( nums.begin(), nums.end() );
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	for ( int i = 1; i <= n; i ++ ) a[i] = lower_bound(nums.begin(), nums.end(), a[i]) - nums.begin() + 1;
	for ( int i = 1; i <= n; i ++ ) {
		res = (res + query(a[i]) * ksm(2, i) % mod) % mod;
		update (a[i], ksm(ksm(2, i + 1), mod - 2));	
	}
	cout << res << endl;
	return 0;
}
```
