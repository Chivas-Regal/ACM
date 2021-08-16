<a href="https://ac.nowcoder.com/acm/contest/11261/F"><img src="https://img-blog.csdnimg.cn/deee414475ff4a5e91ddd15dd99d9a8b.png"></a>

# 💡
本题重在模型的搭建  
首先对于一个括号字符串 "(()())"，我们可以很容易地知道一个括号的的"子同一级的括号"不可用一样的  
那么我们可以得到一个树模型，每个节点的编号是我们自定的  
而这个节点的子节点就是一个括号的子同一级括号  
  
问题转化为：对于每一个节点，它的子节点们不能使用相同的数  
所以，我们要尽可能地在更浅的地方将重复数量多的用完  
那么我们可以使用map对每个数存入数量后，把他们打到优先队列里面  
然后每次遍历到一个节点后，对这个节点的子节点进行选数  
我们可以从优先队列里面每次选出该节点的子节点个数个前面的数  
如果选不出来这么多，就"NO"了  
如果可以，就一个个映射上去就行了  
选完数再把每个数的数量-1，再倒回优先队列即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <unordered_map>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;


struct cmp{ // 重载一下pair的运算符
	bool operator()(pair<int, int>& p1, pair<int, int>& p2){
		return p1.second <= p2.second;
	}
};

const int N = 1e6 + 10;
struct Edge { int nxt, to; } edge[N]; // 前向星
int head[N], cnt; // 前向星
int n, a[N], fath[N]; // 输入个数，输入的数，每个节点的父亲节点
unordered_map<int, int> mp; // 存数的个数
priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pque; // .first = 数， .second = 数的个数
int res[N]; // 结果序列
string s; // 输入的括号


inline void Init () { cnt = 0; for ( int i = 0; i < N; i ++ ) head[i] = -1; }
	
inline void Add_Edge ( int from, int to ) { edge[++cnt] = {head[from], to}; head[from] = cnt; }
	
inline void BFS ( ) {
	queue<int> que; que.push(0); // 从一个虚拟源总根节点开始
	while ( que.size() ) {
		int x = que.front(); que.pop();
		vector<pair<int, int> > lose; // 存放优先队列前几个
		
		for ( int i = head[x]; ~i; i = edge[i].nxt ) { 
			int to = edge[i].to; que.push(to);
			if ( pque.size() ) // 如果还有数，就放进去
				lose.push_back(pque.top()), 
				res[to] = lose.back().first, 
				pque.pop(); 
			else	          // 如果没有不同的了，就"NO"
				puts("NO"), 
				exit(0);
		}
			
		for ( auto i : lose ) { // 再把提出来的这些导回去
			i.second --;
			if ( i.second ) pque.push(i);
		} 
	}
}


int main () {

#ifndef ONLINE_JUDGE
	freopen("in.in", "r", stdin);
#endif
	
	cin >> n >> s;
	for ( int i = 0; i < n; i ++ ) 
		cin >> a[i],
		mp[a[i]] ++; // 统计一下数的个数
	for ( auto i : mp )
		pque.push({i.first, i.second}); // 整体导入优先队列
	
	Init(); int cur_fath = 0 /*表当时重定义的倒数第二层节点*/, cur_son = 1 /*表当时重定义的最后一层节点*/;
	for ( auto i : s ) {
		if ( i == '(' ) 
			Add_Edge(cur_fath, cur_son),
			fath[cur_son] = cur_fath, // 把son和fath对应一下，以便遇见')'后cur_fath点回去一层
			cur_fath = cur_son ++;
		else cur_fath = fath[cur_fath]; // 回去一层
	}
	BFS ();
	
	puts("YES");
	for ( int i = 1; i <= n; i ++ )
		cout << res[i] << " ";
}


```
