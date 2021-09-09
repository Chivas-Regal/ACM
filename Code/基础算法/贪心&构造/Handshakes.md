# 🔗
<a href="https://codeforces.com/problemset/problem/534/D"><img src="https://i.loli.net/2021/09/09/scJ3WeoiOuVFIMQ.png"></a>

# 💡
首先简化一下题意：有一个计数变量cur，每次若cur大于3，可以选择减任意个3，从给定数组中挑出一个cur并输出下标，然后cur+1，执行n次  
那么我们可以存一下每个值对应的下标集合  
计数变量cur从1往上走，先不减，把大的数用了    
如果这一步没有能放的数的话就不断-3直到有为止  
如果到负数还没有的话就输出不可能

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cmath>
#include <map>
#include <deque>
#include <algorithm>
#include <cstring>
#include <vector>

#define ll long long

using namespace std;

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	int n; cin >> n;
	vector<int> vec[n + 10];
	int a[n + 10];
	for ( int i = 1; i <= n; i ++ ) {
		cin >> a[i];
		vec[a[i]].push_back(i);
	}
	int cur = 0; // 时间戳
	int res[n + 10];
	for ( int i = 1; i <= n; i ++ ) {
		while ( !vec[cur].size() ) { // 如果没有，不断减3
			cur -= 3;
			if ( cur < 0 ) {
				cout << "Impossible" << endl;
				return 0;
			}
		}
		res[i] = vec[cur].back();
		vec[cur].pop_back();
		cur ++;
	}
	cout << "Possible" << endl;
	for ( int i = 1; i <= n; i ++ ) {
		cout << res[i] << " ";
	}
} 
```
