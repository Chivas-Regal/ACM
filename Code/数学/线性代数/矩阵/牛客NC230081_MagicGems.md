# 🔗
<a href="https://ac.nowcoder.com/acm/contest/24157/B"><img src="https://i.loli.net/2021/11/25/PGmu3thx1kQjEZg.png"></a>

# 💡
一个计数问题  
一个宝石可以被分解，那么容量也降低  
那么要拿第  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  个的时候可以由  <img src="https://latex.codecogs.com/svg.image?\inline&space;i-1" title="\inline i-1" /> 推过来，也可以选择分解这个，由  <img src="https://latex.codecogs.com/svg.image?\inline&space;i-m" title="\inline i-m" />  推过来
那么我们可以设计出递推式  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;f_i=f_{i-1}+f_{i-m}" title="\inline f_i=f_{i-1}+f_{i-m}" />  
   
由于  <img src="https://latex.codecogs.com/svg.image?\inline&space;n" title="\inline n" /> 很大，那么直接矩阵<img src="https://latex.codecogs.com/svg.image?\inline&space;ksm" title="\inline ksm" />优化

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int mod = 1e9 + 7;
const int N = 110;

struct Matrix {
        ll m[N][N];
        inline Matrix ( int e ) { 
                for ( int i = 0; i < N; i ++ ) 
                        for ( int j = 0; j < N; j ++ ) 
                                m[i][j] = e * (i == j); 
        }
        inline Matrix Mul ( Matrix a, Matrix b ) {
                Matrix res(0);
                for ( int i = 0; i < N; i ++ ) {
                        for ( int j = 0; j < N; j ++ ) {
                                for ( int k = 0; k < N; k ++ ) {
                                        res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j] % mod) % mod;
                                }
                        }
                }
                return res;
        }
        inline Matrix ksm ( Matrix a, ll b ) {
                Matrix res(1);
                while ( b ) {
                        if ( b & 1 ) res = Mul(res, a);
                        a = Mul(a, a);
                        b >>= 1;
                }
                return res;
        }
};

int main () {
        ll n, m; cin >> n >> m;
        if ( n < m ) { cout << 1 << endl; return 0; }
        Matrix res(0); 
        res.m[0][0] = res.m[0][m - 1] = 1;
        for ( int i = 1; i < m; i ++ ) res.m[i][i - 1] = 1;
        res = res.ksm(res, n - m + 1);

        ll RES = 0;
        for ( int i = 0; i < m; i ++ ) RES = (RES + res.m[0][i]) % mod;
        cout << RES << endl;

}
```
