# 🔗
<a href="https://vjudge.net/contest/456121#problem/E"><img src="https://i.loli.net/2021/09/03/MYkj5xgtvmXrlsB.png"></a>

# 💡
由于异或的性质，反复异或等于0  
所以求a[l]^a[l+1]^...^a[r]时  
可以将a[i]标记为前缀和，然后求a[l-1]^a[r]即可  
那么问题转化为记录区间里面a[l-1]^a[r]=k的个数  
那么对于每个a[r]我们求一下a[r]^k的个数累加即可

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <queue>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <map>
#define ll long long

using namespace std;

const ll N = 1e5 + 10;

struct Q{
	ll l, r, id;
}q[N];// 查询
ll a[N], res[N], RES, pos[N]; // 数列，记录答案，当前答案，块编号
ll cnt[5000010]; // 统计出现过的数的个数
ll n, m, k, len;

int main () {
	ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif

	auto add = [&] ( ll id ) {
		RES += cnt[a[id] ^ k]; // 利用区间内出现数的个数求一下当前RES
		cnt[a[id]] ++;  // 前缀和出现个数++
	};
	auto sub = [&] ( ll id ) {
		cnt[a[id]] --;
		RES -= cnt[a[id] ^ k];
	}; 

	cin >> n >> m >> k; len = sqrt(n);

	for ( ll i = 1; i <= n; i ++ ) {
		cin >> a[i]; a[i] ^= a[i - 1];
		pos[i] = i / len;
	}

	for ( ll i = 0; i < m; i ++ ) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}

	sort ( q, q + m, []( Q a, Q b ) {
		if ( pos[a.l] != pos[b.l] ) return pos[a.l] < pos[b.l];
		return a.r < b.r;		
	});

	ll l = 1, r = 0; cnt[0] = 1;
	for ( ll i = 0; i < m; i ++ ) {
		while ( l > q[i].l ) add ( -- l - 1 );
		while ( r < q[i].r ) add ( ++ r );
		while ( l < q[i].l ) sub ( l ++ - 1 );
		while ( r > q[i].r ) sub ( r -- );
		res[q[i].id] = RES; 
	}
	for ( ll i = 0; i < m; i ++ ) {
		cout << res[i] << endl;
	}
	return 0;
}

```
