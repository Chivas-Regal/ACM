# 🔗
<a href="https://codeforces.com/problemset/problem/978/D"><img src="https://i.loli.net/2021/09/30/hIDbUfF4JaVnWc1.png"></a>

# 💡
处理每一个数的修改量是件很麻烦的事情  
  
每个数的最大修改量是1  
且考虑等差数列的性质：a[x] = a[1] + (x - 1) * d  
所以枚举第一项和第二项就行了，后面的也就自然都确定下来了  
  
我们在这个确定的数组中跑一遍，如果没有修改不了的那么就维护一下修改量的总和最小值    

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll N = 1e5 + 10;
ll a[N];

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif 
        ll n; cin >> n;
        for ( ll i = 1; i <= n; i ++ ) cin >> a[i];
        if ( n == 1 || n == 2 ) {
                cout << "0" << endl;
                return 0;
        } 
        ll res = 1e18;
        for ( ll x = a[1] - 1; x <= a[1] + 1; x ++ ) {
                for ( ll y = a[2] - 1; y <= a[2] + 1; y ++ ) {
                        bool flag = true;
                        ll dir = y - x;
                        ll cur = llabs(a[1] - x) + llabs(a[2] - y); 
                        for ( ll i = 3, id = y + dir; i <= n; i ++, id += dir ) {
                                if ( llabs(a[i] - id) > 1 ) flag = false;
                                cur += llabs(a[i] - id);
                        }
                        if ( flag ) res = min ( res, cur );
                }
        }
        if ( res == 1e18 ) cout << "-1" << endl;
        else cout << res << endl;
        return 0;
}
```
