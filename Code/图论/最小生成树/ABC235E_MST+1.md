# 🔗
<a href="https://atcoder.jp/contests/abc235/tasks/abc235_e?lang=en"><img src="https://s2.loli.net/2022/01/18/RSvwFnZajtz93QP.png"></a>

# 💡
回想一下 kruskal 树的构建过程  
从权值小到大枚举边，如果不构成回路就插入  
那么我们可以对固定的边和询问的边分别排个序  
  
从权值小到大枚举询问边  
递进地让每个小于当前询问边的所有点都按 kruskal 的构建方式进行构建  
对于当前询问的边，如果插进去不具有回路，那么证明这个边是可以存在于最小生成树的，反之不行。  
  
这样我们就可以离线地求出所有询问边的答案了，然后把它按顺序输出即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e5 + 10;
int n, m, q;
struct Query {
        int a, b, l;
        bool res;
        int id;
        inline friend bool operator < ( Query a, Query b ) {
                return a.l < b.l;
        }
} qry[N], edg[N];
 
int nod[N];
inline int Find ( int x ) {
        return x == nod[x] ? x : nod[x] = Find(nod[x]);
}
inline void Merge ( int x, int y ) {
        int fx = Find(x), fy = Find(y);
        if ( fx != fy ) nod[fx] = fy;
}
inline bool is_Similar ( int x, int y ) {
        int fx = Find(x), fy = Find(y);
        return fx == fy;
}
int res[N];
 
int main () {
        for ( int i = 0; i < N; i ++ ) nod[i] = i;
        scanf("%d%d%d", &n, &m, &q);
        for ( int i = 0; i < m; i ++ ) {
                scanf("%d%d%d", &edg[i].a, &edg[i].b, &edg[i].l);
        }
        for ( int i = 0; i < q; i ++ ) {
                scanf("%d%d%d", &qry[i].a, &qry[i].b, &qry[i].l);
                qry[i].id = i;
        }
        sort ( edg, edg + m );
        sort ( qry, qry + q );
 
        int ide = 0;
        for ( int i = 0; i < q; i ++ ) {
                while ( ide < m && edg[ide] < qry[i] ) {
                        if ( !is_Similar(edg[ide].a, edg[ide].b) ) {
                                Merge(edg[ide].a, edg[ide].b);
                        }
                        ide ++;
                }
                if ( is_Similar(qry[i].a, qry[i].b) ) res[qry[i].id] = false;
                else res[qry[i].id] = true;
        }
        for ( int i = 0; i < q; i ++ ) {
                if ( res[i] ) puts("Yes");
                else puts("No"); 
        }
}
```
