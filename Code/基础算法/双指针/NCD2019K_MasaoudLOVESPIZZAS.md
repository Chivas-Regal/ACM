# 🔗
<a href="https://codeforces.com/gym/102163/problem/K"><img src="https://s2.loli.net/2022/01/06/zRhQVGom2Hn39bp.png"></a>

# 💡
求有多少个子段和不超过  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" />  
不一样的子段的差异就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;[l,r]" title="\inline [l,r]" /> 的差异，所以我们可以找对于每个  <img src="https://latex.codecogs.com/svg.image?\inline&space;l" title="\inline l" /> 有多少个  <img src="https://latex.codecogs.com/svg.image?\inline&space;r" title="\inline r" /> 满足，也就是对于每个  <img src="https://latex.codecogs.com/svg.image?\inline&space;l" title="\inline l" /> 的满足条件的最大字段长   
然后累加  
这个先**预处理一下前缀和**然后通过双指针就可以实现  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
ll a[100005];
ll b[100005];
ll n, k;

inline void Solve () {
        cin >> n >> k;
        for ( int i = 1; i <= n; i ++ ) 
                cin >> a[i],
                b[i] = b[i - 1] + a[i];

        ll cur = 0;
        ll res = 0;
        
        for ( int l = 1, r = 1; l <= n; l ++ ) {
                r = max(l - 1, r);
                while ( r <= n && b[r] - b[l - 1] < k ) r ++;
                res += r - l;
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
