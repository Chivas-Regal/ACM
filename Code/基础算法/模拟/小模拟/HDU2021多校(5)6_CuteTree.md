# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7017"><img src="https://i.loli.net/2021/10/14/MIyoid2FSAQEbRv.png"></a>

# 💡
分析一下数组的遍历没有什么用  
用处就是每次的`tot++`  
硬写也就log  
直接模拟就行了

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int n;
int tot;

inline void dfs ( int l, int r ) {
        tot ++;
        if ( l == r ) return;
        if ( r - l == 1 ) {
                dfs ( l, l );
                dfs ( r, r );
        } else {
                int len = r - l + 1;
                int b = l + ( len / 3 + (len % 3 != 0) ) - 1;
                int c = (b + r) / 2;
                dfs ( l, b );
                dfs ( b + 1, c );
                dfs ( c + 1, r );
        }
}

inline void Solve () {
        tot = 0; cin >> n;
        for ( int i = 0, x; i < n; i ++ ) cin >> x;
        dfs ( 1, n );
        cout << tot << "\n";
}

int main () {
        ios::sync_with_stdio(false);
        int cass;
        for ( cin >> cass; cass; cass -- ) {
                Solve();
        }
}
```
