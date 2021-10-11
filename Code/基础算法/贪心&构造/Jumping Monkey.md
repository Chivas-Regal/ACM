# 🔗
<a href="https://acm.hdu.edu.cn/showproblem.php?pid=7136"><img src="https://i.loli.net/2021/10/11/3XzVMLBKTsqUZah.png"></a>

# 💡
由于每一个很大的点都可以挡住一定范围的点对互相连通  
所以每一个点所能到达的范围，其实是一个被拆开之后的连通块   
那么拆的方式也就是从最大的点向最小的点递进  
每一次可以拆掉每个连通块内最大的点，同一次被拆掉的点都是同级的  
如：第一次是整棵树最大的点x，第二次是拆掉x后剩下的连通块的最大的点...  
他们的级数就是他们能跳到的点数  
  
这样去拆很难把时间复杂度降低下来  
我们可以试着反向模拟  
从最小的点开始枚举  
每一次它将连接"与它相连且已经枚举过了的连通块"，并将它作为这个连通块的根节点（也就是连接它和这个连通块的根节点）    
这样构建出的一棵树，其中每个点的深度就是他们能跳到的点树  
  
在构造树的过程中我们可以使用并查集  
可以发现在最后一次遍历新树之前，所有连通块除了根节点之外毫无作用  
我们就可以用并查集记录这个连通块的根节点，然后每次连接枚举的点x和与x相连的且已经枚举过的儿子节点to的根节点nod[to]  
  
最后跑一次记录一下深度即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e5 + 10;
struct Edge {
        int nxt, to;
} edge[2][N];
int head[2][N], cnt[2]; // edge[0][]老树， edge[1][]新树
inline void add_Edge ( int op, int from, int to ) { // 连边
        edge[op][++ cnt[op]] = { head[op][from], to };
        head[op][from] = cnt[op];
}

namespace union_Find { // 并查集
        int nod[N];
        inline void Init ( int n ) { for ( int i = 1; i <= n; i ++ ) nod[i] = i; }
        inline int Find ( int x ) { return x == nod[x] ? x : nod[x] = Find(nod[x]); }
        inline void Merge ( int x, int y ) { int fx = Find(x), fy = Find(y); nod[fx] = fy; }
}

#define pii pair<int, int>
#define x first
#define y second
pii a[N]; // x: val, y: id， 输入的a
int n, depth[N]; // 输入的n，深度 

inline void dfs ( int x, int fath ) { // 求深度的dfs
        depth[x] = depth[fath] + 1;
        for ( int i = head[1][x]; ~i; i = edge[1][i].nxt ) {
                int to = edge[1][i].to;
                if ( to == fath ) continue;
                dfs ( to, x );
        }
}

inline void Solve () {
        memset ( head[0], -1, sizeof head[0] );
        memset ( head[1], -1, sizeof head[1] );
        cnt[0] = cnt[1] = 0;
        scanf("%d", &n);
        for ( int i = 0, x, y; i < n - 1; i ++ ) 
                scanf("%d%d", &x, &y),
                add_Edge ( 0, x, y ),
                add_Edge ( 0, y, x );
        for ( int i = 1; i <= n; i ++ )
                scanf("%d", &a[i].x),
                a[i].y = i;
        sort ( a + 1, a + n + 1, [&](pair<int, int> a, pair<int, int> b){ // 按val升序排序
                return a.first < b.first;
        });

        union_Find::Init( n );
        map<int, bool> vis;
        for ( int i = 1; i <= n; i ++ ) { // 枚举
                vis[a[i].y] = true; // 枚举过了
                for ( int j = head[0][a[i].y]; ~j; j = edge[0][j].nxt ) { // 跑一遍这个编号的儿子
                        if ( !vis[edge[0][j].to] ) continue;              // 如果还没有枚举过，就不连接
                        int fj = union_Find::Find(edge[0][j].to);         // 它儿子所在连通块的根节点
                        if ( union_Find::nod[fj] != a[i].y )              // 如果它儿子没有和它连接过 
                                add_Edge ( 1, a[i].y, fj ),
                                add_Edge ( 1, fj, a[i].y ),
                                union_Find::nod[fj] = a[i].y;              // 同时儿子的连通快根节点认父为连通块根节点
                }
        }
        depth[a[n].y] = 0; dfs ( a[n].y, a[n].y );  // 建立深度
        for ( int i = 1; i <= n; i ++ ) printf("%d\n", depth[i]);
}

int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve();
        }
}
```
