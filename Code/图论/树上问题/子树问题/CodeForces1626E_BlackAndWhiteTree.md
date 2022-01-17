# 🔗
<a href="https://codeforces.com/contest/1626/problem/E"><img src="https://s2.loli.net/2022/01/18/ipuAclJtRTLyNEw.png"></a>

# 💡
如果一个点只有它的两侧各有一个点，那么它是可以动的，但仍会选另一个点导致弹回原位，我们把它视作动不了  
我们考虑什么样的边可以保证通过（并且不弹回来）  
对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;x\rightarrow&space;y" title="\inline x\rightarrow&space;y" /> 以  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 为根的子树有多于两个黑点，那么我们可以借用一个黑点走到  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 然后再借用另一个往里走，这个是不会弹回来的，所以这条边是可以走的  
如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 黑点，  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" /> 只需要一步就可以走到他想去的点，所以也可以视作能走  
  
如果对于每个方向都求一次  <img src="https://latex.codecogs.com/svg.image?\inline&space;son[i]" title="\inline son[i]" /> 那么时间肯定不允许  
但是由于子树的性质：   
如果整棵树以  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 为根  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 的子树  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 为  <img src="https://latex.codecogs.com/svg.image?\inline&space;son[y]" title="\inline son[y]" />   
 子树  <img src="https://latex.codecogs.com/svg.image?\inline&space;2" title="\inline 2" /> 为  <img src="https://latex.codecogs.com/svg.image?\inline&space;son[1]-son[y]+y" title="\inline son[1]-son[y]+y" />   
   
利用这个性质，我们遍历一次 DFS 即可  
然后我们根据上面对“边是否能走”的判断来建一个新图  
如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;x\rightarrow&space;y" title="\inline x\rightarrow&space;" /> 可以走，那么我们建一条  <img src="https://latex.codecogs.com/svg.image?\inline&space;y\rightarrow&space;x" title="\inline y\rightarrow&space;x" /> 的边，这样的话我们从所有黑点多源 BFS 即可走出所有能到达黑点的点  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int M = 6e5 + 10;
const int N = 3e5 + 10;
struct Edge {
        int nxt, to;
} edge[2][M];
int head[2][N], cnt[2];
inline void add_Edge ( int from, int to, int id ) {
        edge[id][++cnt[id]] = { head[id][from], to };
        head[id][from] = cnt[id];
}
int n, c[N];
int fa[N];
int num[N];

inline void DFS ( int x, int fath ) {
        fa[x] = fath;
        num[x] += c[x];
        for ( int i = head[0][x]; i; i = edge[0][i].nxt ) {
                int y = edge[0][i].to;
                if ( y == fath ) continue;
                DFS(y, x);
                num[x] += num[y];
        }
}

int main () {
        scanf("%d", &n);
        for ( int i = 1; i <= n; i ++ ) scanf("%d", &c[i]);
        for ( int i = 0; i < n - 1; i ++ ) {
                int a, b; scanf("%d%d", &a, &b);
                add_Edge(a, b, 0);
                add_Edge(b, a, 0);
        }        
        DFS(1, -1);

        for ( int x = 1; x <= n; x ++ ) {
                for ( int i = head[0][x]; i; i = edge[0][i].nxt ) {
                        int y = edge[0][i].to;
                        if ( c[x] ) {
                                add_Edge(x, y, 1);
                        } else {
                                if ( fa[y] == x && num[1] - num[y] > 1 ) add_Edge(x, y, 1);
                                else if ( fa[x] == y && num[x] > 1 )     add_Edge(x, y, 1);
                        }
                }
        }

        queue<int> que;
        for ( int i = 1; i <= n; i ++ ) if ( c[i] ) que.push(i);
        while ( que.size() ) {
                int x = que.front(); que.pop();
                for ( int i = head[1][x]; i; i = edge[1][i].nxt ) {
                        int y = edge[1][i].to;
                        if ( !c[y] ) 
                                c[y] = 1,
                                que.push(y);
                }
        }
        for ( int i = 1; i <= n; i ++ ) printf("%d ", c[i]);
}
```
