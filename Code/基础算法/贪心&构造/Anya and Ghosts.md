# 🔗
<a href="https://codeforces.com/problemset/problem/508/C"><img src="https://i.loli.net/2021/09/08/uBEPGIaWbC4zlhK.png"></a>

# 💡
整个条的数据量不算大，我们可以使用数组当时间轴表示在i时刻是否点了蜡烛  
我们在每个鬼出现的时间前t个节点看看存在几根没灭的蜡烛  
如果少了话就贪心地在后面尽可能补蜡烛  
这样维护每一只鬼出现的时刻都有r根蜡烛  
最后统计一下我们点了几根蜡烛即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <deque>
#include <algorithm>
#include <cstring>
#define ll long long

using namespace std;

const int N = 310;
int a[N], n, t, r;
map<int, int> vis;

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	cin >> n >> t >> r;
	if ( t < r ) { // t时间内点不了r根蜡烛
		cout << "-1" << endl;
		return 0;
	}
	int res = 0;
	for ( int i = 0; i < n; i ++ ) {
		cin >> a[i];
		int ned = r;
		for ( int j = a[i] - t; j <= a[i] - 1 && ned > 0; j ++ ) ned -= vis[j] == 1;
		for ( int j = a[i] - 1; ned; j -- ) { // 补蜡烛
			ned -= vis[j] == 0;
			vis[j] = 1;
		}
	}
	for ( auto i : vis ) res += (i.second == 1);
	cout << res << endl;
	return 0;
}

```
