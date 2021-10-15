# 🔗
<a href="https://www.luogu.com.cn/problem/P4111"><img src="https://i.loli.net/2021/10/15/qBuLKOT7UWcERp6.png"></a>

# 💡
两两能到达的房间连边  
求生成树个数  
对每一个单位重新编号，然后进行连边  
可以采用每一个点如果能向右连就向右连，能向下连就向下连，可以防止重复  
使用矩阵树定理建行列式  
高斯消元求一下行列式sz-1阶行列式即可即可  
  
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 15, M = 105;
const int mod = 1e9;
char s[N][N];
int id[N][N], a[M][M];
int n, m;

inline void add ( int x, int y ) {
	-- a[x][y];
	-- a[y][x];
	++ a[x][x];
	++ a[y][y];
}
inline int Gauss ( int n ) {
	int res = 1;
	for ( int i = 1; i <= n; i ++ ) { // 在(i, i)上进行消元
		for ( int ii = i + 1; ii <= n; ii ++ ) { // 将(ii, i)变成0
			while ( a[ii][i] ) {
				int d = a[i][i] / a[ii][i];
				for ( int j = i; j <= n; j ++ )
					a[i][j] = (a[i][j] - (ll)d * a[ii][j] % mod + mod) % mod,
					swap ( a[i][j], a[ii][j] );
				res = -res;
			}
		}
		res = (ll)res * a[i][i] % mod;
		if ( res == 0 ) return 0;
	}
	return (res % mod + mod) % mod;
}


int main () {
	cin >> n >> m;
	for ( int i = 1; i <= n; i ++ ) cin >> (s[i] + 1);
	int idx = 0;
	for ( int i = 1; i <= n; i ++ ) for ( int j = 1; j <= m; j ++ ) if ( s[i][j] == '.' ) id[i][j] = ++ idx;
	for ( int i = 1; i <= n; i ++ ) for ( int j = 1; j <= m; j ++ ) if ( s[i][j] == '.' ) {
		if ( id[i - 1][j] ) add ( id[i][j], id[i - 1][j] );
		if ( id[i][j - 1] ) add ( id[i][j], id[i][j - 1] );
	}
	cout << Gauss ( idx - 1 ) << endl;
	return 0;
}
```
