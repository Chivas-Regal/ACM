# 🔗
<a href="https://codeforces.com/problemset/problem/979/C"><img src="https://i.loli.net/2021/09/30/BFybalLjWnoRu4X.png"></a>

# 💡
直接处理可以到达的点对很麻烦，要考虑很多种情况  
那么可以容斥地减一下不能到达的点  
即通过y再到达x即之后的点  
  
既然是一棵树  
那么就直接用"x的子树大小"乘"y的子树中不包含x的子树的大小总和"就是我们要减的值  
即`res = n * (n - 1) - son[x] * elsSon`  
  
可以再写一个判断判断子树中有没有x的函数  
处理好son[]后，对y的子节点一个个判断并乘一下就行了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll N = 3e5 + 10, M = N * 2;
ll n, X, Y;
ll res;
struct Edge { ll nxt, to; } edge [M]; ll head[M], cnt;

inline void add_Edge ( ll from, ll to ) {
        edge[ ++ cnt ] = { head[from], to };
        head[from] = cnt;
}
ll son[N], sonels;
inline void get_Sz ( ll x, ll fath ) {
        for ( ll i = head[x]; ~i; i = edge[i].nxt ) {
                ll to = edge[i].to;
                if ( to == fath ) continue;
                get_Sz ( to, x );
                son[x] += son[to];
        }
}
inline bool check ( ll x, ll fath ) {
        ll res = 1;
        if ( x == X ) res = 0;
        for ( ll i = head[x]; ~i; i = edge[i].nxt ) {
                ll to = edge[i].to;
                if ( to == fath ) continue;
                res *= check(to, x);
        }
        return res;
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif 
        memset ( head, -1, sizeof head );
        for ( ll i = 0; i < N; i ++ ) son[i] = 1;
        scanf("%lld%lld%lld", &n, &X, &Y);
        res = n * (n - 1);
        for ( ll i = 1; i < n; i ++ ) {
                ll a, b; cin >> a >> b;
                add_Edge ( a, b );
                add_Edge ( b, a );
        }
        get_Sz ( Y, -1 );
        for ( ll i = head[Y]; ~i; i = edge[i].nxt ) {
                sonels += check(edge[i].to, Y) * son[edge[i].to];
        }
        sonels ++;
        res -= son[X] * sonels;
        printf("%lld\n", res);
}
```
