# 🔗
<a href="https://www.luogu.com.cn/problem/P6086"><img src="https://img-blog.csdnimg.cn/f1bb3253695b48d0b864787235e289a0.png"></a>

# 💡
模板题  
具体讲解流程阅览<a href="https://chivas-regal.github.io/%E5%9B%BE%E8%AE%BA/2021/11/03/Prufer%E7%BC%96%E7%A0%81.html">这里</a>

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
namespace Prufer {
        const int N = 5e6 + 10;
        int d[N], f[N], p[N], n;
        
        inline void Prufer2Tree () {
                for ( int i = 1; i <= n - 2; i ++ )
                        cin >> p[i],
                        d[p[i]] ++;
                p[n - 1] = n;
                for ( int i = 1, j = 1; i <= n - 1; i ++, j ++ ) {
                        while ( d[j] ) j ++;
                        f[j] = p[i];
                        while ( i <= n - 2 && -- d[p[i]] == 0 && p[i] < j ) f[p[i]] = p[i + 1], i ++;
                }
                ll res = 0;
                for ( int i = 1; i <= n - 1; i ++ ) res ^= (ll)f[i] * i;
                cout << res << endl;
        }
        inline void Tree2Prufer () {
                for ( int i = 1; i < n; i ++ )
                        cin >> f[i],
                        d[f[i]] ++;
                for ( int i = 1, j = 1; i <= n - 2; j ++ ) {
                        while ( d[j] ) j ++;
                        p[ i ++ ] = f[j];
                        while ( i <= n - 2 && -- d[p[i - 1]] == 0 && p[i - 1] < j ) p[ i ++ ] = f[p[i - 1]];
                }
                ll res = 0;
                for ( int i = 1; i <= n - 2; i ++ ) res ^= (ll)p[i] * i;
                cout << res << endl;
        }
} using namespace Prufer;
int op;

int main () {
        cin >> n >> op;
        if ( op == 1 ) Tree2Prufer ();
        else           Prufer2Tree ();
}

```
