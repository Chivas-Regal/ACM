# 🔗
<a href="https://www.acwing.com/problem/content/266/"><img src="https://i.loli.net/2021/09/28/jqJ8zBepZdbuRyn.png"></a>

# 💡
此时路径还是分成三类：  
1.两点在一个子树内  
2.两点在不同子树内  
3.一点在子树重心上  

重要还是处理第二种  
我们可以设置一个哈希表或者说桶，去维护在距离重心为i的距离下，边数的最小值   
  
那么我们在每次遍历一棵子树时，去查找当前子树的每个距离重心不大于m的点  
对于每个点，如果距离=m说明是第三种，那么我们就可以直接拿res和这个点距离重心的边数进行比较  
如果距离<m，我们去看在"m-距离"的桶中的值，然后用这个值+我们查找的点距离重心的边数与res进行对比  

然后将这课子树的每个点记录进桶中，同时将我们塞入的每个点记录一下，再遍历下一个子树  
最后将塞入过的点对应的桶重置，进入下一层递归  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdio>

#define ll long long
#define x first
#define y second
#define pii pair<int, int>
#define INF 0x3f3f3f3f

using namespace std;

const int N = 2e5 + 10, M = 2 * N, S = 1e6 + 10;
struct Edge { int nxt, to, val; } edge [M]; int head[M], cnt;
int n, m;
bool st[N];
pii oneSon[N], allSon[N]; // first = 距离，second = 边数
int f[S]; // 维护在距离为i下，边数的最小值
int res = INF;

inline void Init () {
        memset ( head, -1, sizeof head );
        memset ( st, 0, sizeof st );
        memset ( f, INF, sizeof f );
        cnt = 0;
}
inline void Add_Edge ( int from, int to, int val ) {
        edge [ ++ cnt ] = { head[from], to, val };
        head[from] = cnt;
}
inline int get_Sz ( int x, int fath ) {
        if ( st[x] ) return 0;
        int res = 1;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                res += get_Sz ( to, x );
        }
        return res;
}
inline int get_Wc ( int x, int fath, int tot, int &wc ) {
        if ( st[x] ) return 0;
        int mxSon = 0, sum = 1;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                int t = get_Wc ( to, x, tot, wc );
                mxSon = max ( mxSon, t );
                sum += t;
        } 
        mxSon = max ( mxSon, tot - sum );
        if ( mxSon <= tot / 2 ) wc = x;
        return sum;
}
inline void get_Dis ( int x, int fath, int dist, int cnt, int &tot ) {
        if ( st[x] || dist > m ) return ;
        oneSon[ tot ++ ] = { dist, cnt };
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                get_Dis ( to, x, dist + edge[i].val, cnt + 1, tot );
        }
}
inline void Solve ( int x ) {
        if ( st[x] ) return ;
        get_Wc ( x, -1, get_Sz ( x, -1 ), x );
        st[x] = true;

        int cnt_allSon = 0;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to, cnt_oneSon = 0;
                get_Dis ( to, x, edge[i].val, 1, cnt_oneSon );
                for ( int j = 0; j < cnt_oneSon; j ++ ) {
                        auto t = oneSon[j];
                        if ( t.x == m ) res = min ( res, t.y ); // 可以直接根据这个节点建立[重心，节点]的路径判断一下个数最小值
                        else            res = min ( res, f[m - t.x] + t.y ); // 根据之前维护出来的哈希表内的判断一下个数最小值
                }
                for ( int j = 0; j < cnt_oneSon; j ++ ) {
                        auto t = oneSon[j];
                        f[t.x] = min ( f[t.x], t.y ); // 将当前子树的加入哈希表
                        allSon[ cnt_allSon ++ ] = t; 
                }
        }
        for ( int i = 0; i < cnt_allSon; i ++ ) { // 把这一个大连通块的重置为INF
                auto t = allSon[i];
                f[t.x] = INF;
        }
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                Solve(edge[i].to);
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif 
        Init ();
        scanf("%d%d", &n, &m);
        for ( int i = 0, a, b, c; i < n; i ++ ) {
                scanf("%d%d%d", &a, &b, &c);
                Add_Edge ( a, b, c );
                Add_Edge ( b, a, c );
        }
        Solve(0);
        if ( res == INF ) res = -1;
        printf("%d\n", res);
}
```
