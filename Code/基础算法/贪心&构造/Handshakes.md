# 🔗
<a href="https://codeforces.com/problemset/problem/534/D"><img src="https://i.loli.net/2021/09/09/scJ3WeoiOuVFIMQ.png"></a>

# 💡
让我们在一个位置处利用可以利用的下标的值进行构造  
那么我们可以翻一下，用值存一下下标  
设置一个时间戳，每次+1，如果有要使用的数就利用一下这个数，否则退一下寻求合理的数也就是-3  
这样也可以尽快把大的数给用了  

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
