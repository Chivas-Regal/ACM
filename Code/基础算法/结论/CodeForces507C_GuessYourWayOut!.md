# 🔗
<a href="https://codeforces.com/problemset/problem/507/C"><img src="https://i.loli.net/2021/09/08/wWV3gmbDsBKa61d.png"></a>

# 💡
这道题刚开始可能没有什么思路，在纸上画一下一个比较大的树的遍历顺序并把值写上去  
发现在把叶子分为两部分时，左区间的右端点与右区间的左端点的差值为<img src="https://latex.codecogs.com/svg.image?2^h-1" title="2^h-1" />，再进一步划分就是<img src="https://latex.codecogs.com/svg.image?2^{h-1}-1" title="2^{h-1}-1" />   
每一个区间的左右端点差值也有类似的性质  
一个节点的左儿子的树在中间两个数是递增的，右儿子中间两个数是递减的  
把所有的可以用的性质挖出来之后  
我们发现可以二分查找地推出来我们找的序号的值  
设变量l,r是左右总区间端点序号，l1,r1是左区间的两个端点序号，l2,r2是右区间的两个端点序号  
val_l1,val_r1是左区间的两个端点值，val_l2,val_r2是右区间的两个端点值  
并建立一个VAL_L用来继承上一步求得的val_l1或者val_l2（具体是哪个要根据我们选择的是左区间还是右区间  
推到最后l=r时停止  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#define ll long long

using namespace std;

ll h, n; 

int main () {
#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif

	cin >> h >> n;
	ll l = 1, r = (1ll << h);

	ll l1, r1, l2, r2;
	ll val_l1 = (1ll << h), val_r1, val_l2, val_r2 = (1ll << (h + 1)) - 1;
	ll dep = (1ll << h); // 两端点差值
	ll val_l = (1ll << h);

	bool flag = true; // 选左儿子false, 选右儿子true

	while ( l != r ) {
		// 8个变量的值根据结论进行推
		l1 = l,          r1 = l1 + dep / 2 - 1, 
		l2 = r1 + 1,     r2 = r;
		val_l1 = val_l;           
		val_r1 = val_l1 - dep / 2 + 1;
		if ( flag ) 
			val_l2 = val_r1 + dep - 1; 
		else 
			val_l2 = val_r1 - dep + 1;	
		val_r2 = val_l2 + dep / 2 - 1;

		if ( l1 <= n && n <= r1 ) // 进入左区间
			l = l1, r = r1,
			val_l = val_l1,// 继承左区间的左端点
			flag = false;
		else                      // 进入右区间
			l = l2, r = r2,
			val_l = val_l2,// 继承右区间的左端点
			flag = true;
		dep /= 2;
	}
	cout << val_l - 1 << endl;
}
```
