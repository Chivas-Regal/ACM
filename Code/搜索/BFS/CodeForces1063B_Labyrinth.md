# 🔗
<a href="https://codeforces.com/problemset/problem/1063/B"><img src="https://i.loli.net/2021/09/15/yvlqKuNwCxRb3LP.png"></a>

# 💡
即然要记录能到达的点数  
其实每个点访问一次就行了  
那么主要设计好标记不重复走每一格，时间复杂度允许我们开BFS搜索遍历的  
  
关键问题在于：如何让没怎么消耗左右走机会的访问节点优先走  
没怎么消耗左右节点也就意味着尽可能上下走的节点  
那就只需要**对上下走优先遍历**即可  
  
DFS肯定爆栈，我们可以对BFS中遍历队列设为**双端队列**  
我们每次优先将上下走的节点压入队首，左右走压入队尾  
每次遍历时取队头即可满足优先上下走的条件了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ll long long

using namespace std;
const int mod = 1e9 + 7;
const int N = 2100;

int n, m;
int r, c;
int _l, _r;
char s[N][N];
struct node {
        int x, y, nl, nr;
};
int vis[N * N * 2];
int res;

inline void BFS () {
        deque<node> dq;
        dq.push_back({r, c, _l, _r});
        while ( dq.size() ) {
                node cur = dq.front(); dq.pop_front();
                if ( cur.x < 1 || cur.x > n || cur.y < 1 || cur.y > m ) continue;
                if ( vis[(cur.x - 1) * m + cur.y] ) continue; vis[(cur.x - 1) * m + cur.y] = 1;
                if ( s[cur.x][cur.y] == '*' ) continue;

                res ++;
                dq.push_front({cur.x + 1, cur.y, cur.nl, cur.nr}); // 优先上下走
                dq.push_front({cur.x - 1, cur.y, cur.nl, cur.nr});
                if ( cur.nl ) dq.push_back({cur.x, cur.y - 1, cur.nl - 1, cur.nr}); // 其次左右走
                if ( cur.nr ) dq.push_back({cur.x, cur.y + 1, cur.nl, cur.nr - 1});
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        scanf("%d%d%d%d%d%d", &n, &m, &r, &c, &_l, &_r);
        for ( int i = 1; i <= n; i ++ ) scanf("%s", s[i] + 1);
        BFS();
        printf("%d\n", res);
}

```
