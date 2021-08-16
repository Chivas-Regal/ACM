# 🔗
<a href="https://codeforces.com/problemset/problem/1512/G"><img src="https://img-blog.csdnimg.cn/5b206cdb8bd74dafa8c530e12e895270.png"></a>

# 💡
每个数的因数都要算一遍，那么我们就需要用到埃氏筛的重复筛的性质  
给了两秒，可以支持O(nlogn)    
那么我们直接开埃氏筛存数即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

using namespace std;

const int N = 1e7 + 10;
int mark[N], res[N], n;

inline void Get () {
	for ( int i = 1; i < N; i ++ )
		for ( int j = i; j < N; j += i )
			mark[j] += i; // 每个数的因子和都要记录一下
	for ( int i = 1; i < N; i ++ ) 
		if ( mark[i] < N && !res[mark[i]] )
                        res[mark[i]] = i; // 第一个出现的存进去
}

int main () {
	Get(); int cass, x;
	for ( cin >> cass; cass; cass -- )
		cin >> x, cout << (res[x] == 0? -1 : res[x])<< endl;
}
```
