# 🔗
<a href="https://codeforces.com/gym/103373/problem/G"><img src="https://s2.loli.net/2022/01/14/GJDlbeI1MXwcoku.png"></a>

# 💡
一个计数问题  
而且每个权值小的边都可以将自己的方案数推给相邻权值大的边  
就直接计数dp就完事了  
  
由于我们是小边推给大边  
这里要按边权从小打大开始遍历  
并且发现这里走过一条边有不同的方向，所以我们设置一个 `dp_up[i]` 和一个 `dp_down[i]` 来表示终止于这条边上到下的方案数和从下到上的方案数  
  
那么我们可以先从这条边深度大的点枚举它的相邻边，这样是累积 `dp_up`    
如果相邻边小，我们要看这个相邻边是从深度小的推向深度大的还是深度大到深度小的  
如果是小推大，那么就 `dp_up[i] += dp_down[该邻边编号]`  否则 `dp_up[i] += do_up[该邻边编号]`  
选择深度小的点枚举相邻边同理  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
ll n;
struct Edge {
        ll nxt, to, val;
        ll id; // 该边编号
} edge [400005];
ll head[200005], cnt;
inline void add_Edge ( ll from, ll to, ll val, ll id ) {
        edge [ ++ cnt ] = {head[from], to, val, id};
        head[from] = cnt;
}

struct Way {
        ll a, b, c;
} w[200005];

map<ll, vector<ll> > mp;
ll d[200005];

inline void dfs_Dep ( ll x, ll fa, ll dp ) {
        d[x] = dp;
        for ( ll i = head[x]; i; i = edge[i].nxt ) {
                if ( edge[i].to == fa ) continue;
                dfs_Dep(edge[i].to, x, dp + 1);
        }
}
ll dp_up[200005], dp_down[200005];

int main () {
        scanf("%lld", &n);
        for ( ll i = 0; i < n - 1; i ++ ) {
                scanf("%lld%lld%lld", &w[i].a, &w[i].b, &w[i].c);
                mp[w[i].c].push_back(i);
                add_Edge(w[i].a, w[i].b, w[i].c, i);
                add_Edge(w[i].b, w[i].a, w[i].c, i);
        }
        dfs_Dep(1, 1, 0);
        for ( auto m : mp ) {
                ll val = m.first;
                for ( ll ve = 0; ve < m.second.size(); ve ++ ) {
                        ll uppt = w[m.second[ve]].a;
                        ll dwpt = w[m.second[ve]].b;
                        ll lnvl = w[m.second[ve]].c;
                        if ( d[uppt] > d[dwpt] ) swap(uppt, dwpt);

                        dp_up[m.second[ve]] = dp_down[m.second[ve]] = 1;

                        // dp_dw
                        for ( ll i = head[uppt]; i; i = edge[i].nxt ) {
                                ll to = edge[i].to;
                                ll vl = edge[i].val;
                                ll id = edge[i].id;
                                if ( vl >= lnvl ) continue; // 严格小于
                                if ( d[to] > d[uppt] ) { // 这样看相邻边是向上推的
                                        dp_down[m.second[ve]] += dp_up[id];
                                } else { // 向下推的
                                        dp_down[m.second[ve]] += dp_down[id];
                                }
                        } 
                        // dp_up
                        for ( ll i = head[dwpt]; i; i = edge[i].nxt ) {
                                ll to = edge[i].to;
                                ll vl = edge[i].val;
                                ll id = edge[i].id;
                                if ( vl >= lnvl ) continue;
                                if ( d[to] > d[dwpt] ) {
                                        dp_up[m.second[ve]] += dp_up[id];
                                } else {
                                        dp_up[m.second[ve]] += dp_down[id];
                                }
                        }
                }
        }
        ll res = 0;
        for ( ll i = 0; i < n - 1; i ++ ) res += dp_up[i] + dp_down[i];
        cout << res << endl;
}
```
