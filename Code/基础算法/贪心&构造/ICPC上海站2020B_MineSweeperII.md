# 🔗
<a href="https://codeforces.com/gym/102900/problem/B"><img src="https://s2.loli.net/2022/01/02/pn5JzxD1Lf3GEbd.png"></a>

# 💡
给定两个矩阵，由  <img src="https://latex.codecogs.com/svg.image?\inline&space;X" title="\inline X" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;." title="\inline ." /> 构成，每个矩阵的价值是所有  <img src="https://latex.codecogs.com/svg.image?\inline&space;." title="\inline ." /> 一圈的  <img src="https://latex.codecogs.com/svg.image?\inline&space;X" title="\inline X" /> 的数量的和，问可否在不多于  <img src="https://latex.codecogs.com/svg.image?\inline&space;\left\lfloor\frac{mn}{2}\right\rfloor" title="\inline \left\lfloor\frac{mn}{2}\right\rfloor" /> 次操作让  <img src="https://latex.codecogs.com/svg.image?\inline&space;B" title="\inline B" /> 矩阵和  <img src="https://latex.codecogs.com/svg.image?\inline&space;A" title="\inline A" /> 矩阵的价值一样  
  
可以看到，每个  <img src="https://latex.codecogs.com/svg.image?\inline&space;." title="\inline ." /> 做出的贡献都是依靠相对的  <img src="https://latex.codecogs.com/svg.image?\inline&space;X" title="\inline X" /> ，那么我们对一个矩阵进行翻转那么价值是一样的，而  <img src="https://latex.codecogs.com/svg.image?\inline&space;A" title="\inline A" /> 矩阵变成  <img src="https://latex.codecogs.com/svg.image?\inline&space;B" title="\inline B" /> 矩阵或者  <img src="https://latex.codecogs.com/svg.image?\inline&space;B" title="\inline B" /> 的反矩阵必定有一个次数是小于要求的，我们就看  <img src="https://latex.codecogs.com/svg.image?\inline&space;A,B" title="\inline A" /> 的差异数，我们就可以知道要变哪个矩阵  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1100;
string a[N];
string b[N];

inline void Solve () {
        int n, m; cin >> n >> m;
        for ( int i = 0; i < n; i ++ ) cin >> a[i];
        for ( int i = 0; i < n; i ++ ) cin >> b[i];
        int dirX = 0; // 差异数
        for ( int i = 0; i < n; i ++ ) {
                for ( int j = 0; j < m; j ++ ) {
                        dirX += a[i][j] != b[i][j];
                }
        }
        int candel = n * m / 2;
        if ( candel < dirX ) {
                for ( int i = 0; i < n; i ++ ) {
                        for ( int j = 0; j < m; j ++ ) a[i][j] == 'X' ? a[i][j] = '.' : a[i][j] = 'X';
                        cout << a[i] << endl;
                }
        }
        else {
                for ( int i = 0; i < n; i ++ ) cout << a[i] << endl;
        }
}       

int main () {
        ios::sync_with_stdio(false);
        int cass = 1; while ( cass -- ) {
                Solve ();
        }
}
```
