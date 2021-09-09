# 🔗
<a href="https://codeforces.com/problemset/problem/538/C"><img src="https://i.loli.net/2021/09/09/AYHve3ZjlUomyCg.png"></a>

# 💡
两两之间有一个山峰形的折线图  
直接算有些麻烦，可以将两个点挪到同一高度（低的补上来，时间也要补） 
如果补到同一高度发现时间交错了，就不行  
然后在同一高度下利用两者中间的时间来计算他俩之间的峰顶高度  
要注意时间为1的位置和n的位置都是由两端的值向左和向右增出来的，也要维护一下  

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

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	int n, m; cin >> n >> m;
	pair<int, int> pr[m + 10];
	for ( int i = 1; i <= m; i ++ ) cin >> pr[i].first >> pr[i].second;
	pr[0].first = 1, pr[0].second = pr[1].second + pr[1].first - 1; // 时间为1的位置
	pr[m + 1].first = n, pr[m + 1].second = pr[m].second + n - pr[m].first; // 时间为n的位置

	
	int res = 0;
	for ( int i = 1; i <= m + 1; i ++ ) {
		if ( abs(pr[i].first - pr[i - 1].first) < abs(pr[i].second - pr[i - 1].second) ) {
			puts("IMPOSSIBLE");
			return 0;
		}
		int t1 = pr[i - 1].first, h1 = pr[i - 1].second;
		int t2 = pr[i].first, h2 = pr[i].second;
                // 两者要齐平一下，然后矮的那个时间也更改一下
		if ( h1 < h2 ) {
			t1 += h2 - h1;
			h1 = h2;
		} else if ( h2 < h1 ) {
			t2 -= h1 - h2;
			h2 = h1;
		}
		int dt = t2 - t1 - 1; // 时间差
		dt = max (dt, 0); 
		res = max ( res, dt / 2 + (dt & 1) + h1 ); // 计算峰值
	}
	cout << res << endl;
} 
```
