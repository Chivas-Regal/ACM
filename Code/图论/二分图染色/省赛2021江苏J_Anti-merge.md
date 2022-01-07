# 🔗
<a href="https://codeforces.com/gym/103495/problem/J"><img src="https://s2.loli.net/2022/01/08/Et2roMNiYj137Is.png"></a>

# 💡
相同的会删去，我们要加标签来防止有数被删去  
可以将相邻的一样的数看作连通块，我们要想让这个联通块两两隔开，其实就加一个编号就行了  
那么这道题答案的第一个数只有  <img src="https://latex.codecogs.com/svg.image?\inline&space;0" title="\inline 0" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 两种可能  
而对于连通块，我们从一个点  <img src="https://latex.codecogs.com/svg.image?\inline&space;a" title="\inline a" />  开始  <img src="https://latex.codecogs.com/svg.image?\inline&space;dfs" title="\inline dfs" /> 出这个连通块，看看是离  <img src="https://latex.codecogs.com/svg.image?\inline&space;a" title="\inline a" /> 距离为奇数加标签用的多还是偶数加标签用的多，我们选用最少的标签加法  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 510;
int g[N][N], vis[N][N];
int n, m;
int chos_which[N][N];

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct node { int a, b, c; };
int res1;
vector<node> res2;

int n1, n0;
inline void DFS ( int x, int y, int flag, int num, int op ) { // flag：0计数，12加标签
        if ( vis[x][y] ) return; vis[x][y] = 1;
        if ( flag ) n1 ++; // 距离为奇数要加标签的数量
        else n0 ++; // 距离为偶数要加标签的数量
        if ( op == 1 ) { // 距离为奇数且要加标签
                if ( flag ) res2.push_back({x, y, 1});
        } else if ( op == 2 ) { // 距离为偶数且要加加标签
                if ( !flag ) res2.push_back({x, y, 1});
        }

        for ( int i = 0; i < 4; i ++ ) {
                int nx = x + dx[i], ny = y + dy[i];
                if ( nx <= 0 || nx > n || ny <= 0 || ny > m ) continue;
                if ( g[nx][ny] != num ) continue;
                DFS(nx, ny, flag ^ 1, num, op);
        }
}

int main () {
        ios::sync_with_stdio(false);
        cin >> n >> m;
        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 1; j <= m; j ++ ) {
                        cin >> g[i][j];
                }
        }
        vector<pair<int, int> > nod_fath; // 一个连通块的根
        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 1; j <= m; j ++ ) {
                        if ( vis[i][j] ) continue;
                        n1 = n0 = 0;
                        DFS(i, j, 0, g[i][j], 0);
                        if ( n1 >= n0 ) chos_which[i][j] = 2;
                        else chos_which[i][j] = 1;
                        if ( n1 ) res1 = 1;
                        nod_fath.push_back({i, j});
                }
        }
        if ( !res1 ) cout << "0 0" << endl; // 不需要加标签
        else {
                memset(vis, 0, sizeof vis );
                for ( auto i : nod_fath ) {
                        DFS(i.first, i.second, 0, g[i.first][i.second], chos_which[i.first][i.second]);
                }
                cout << res1 << " " << res2.size() << endl;
                for ( int i = 0; i < res2.size(); i ++ ) {
                        cout << res2[i].a << " " << res2[i].b << " " << res2[i].c << endl;
                }

        }
}
```
