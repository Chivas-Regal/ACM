# 🔗
<a href="https://codeforces.com/contest/1593/problem/C"><img src="https://i.loli.net/2021/10/14/tLkYVnWywBO8Zqp.png"></a>

# 💡
首先我们想让尽可能多的老鼠进洞，除了从最后面的往后走之外没有别的办法  
因为把几个老鼠挪进去的总耗时是一定的  
那么从最后开始挪肯定是性价比最高的  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 4e5 + 10;
ll n, k;
ll a[N];

inline void Solve() {
        cin >> n >> k;
        ll res = 0;
        for ( ll i = 0; i < k; i ++ ) cin >> a[i];
        sort ( a, a + n, greater<ll>());
        
        ll catid = 0;
        for ( ll i = 0; i < k; i ++ ) {
                if ( a[i] <= catid ) break;
                catid += n - a[i];
                res ++;
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
