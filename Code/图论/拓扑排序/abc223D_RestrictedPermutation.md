# 🔗
<a href="https://atcoder.jp/contests/abc223/tasks/abc223_d"><img src="https://i.loli.net/2021/10/17/Lo2YI3EAjRsVSt5.png"></a>

# 💡
首先不合法的情况肯定就是有环的  
这道题的关系网内，每一个点都会通过一个优先顺序转移得到另一个点  
那么我们可以利用这个顺序建立拓扑结构  
在拓扑结构内使用优先队列来保证构造的是最小的字典序  
然后如果最后出来的不是n个数说明有环，就-1  
否则输出这n个数  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 3e5 + 10;
int in[N];

struct CMP{
        int x;
        inline friend bool operator < ( CMP a, CMP b ) {
                return a.x > b.x;
        }
};

int head[N], cnt;
struct Edge {
        int nxt, to;
}edge[N];
inline void add_Edge ( int from, int to ) {
        edge[ ++ cnt ] = { head[from], to };
        head[from] = cnt;
}

int main () {
        ios::sync_with_stdio(false);
        memset ( head, -1, sizeof head );
        priority_queue<CMP> que;
        int n, m; cin >> n >> m;
        for ( int i = 0, x, y; i < m; i ++ ) {
                cin >> x >> y;
                add_Edge ( x, y );
                in[y] ++;
        }
        for ( int i = 1; i <= n; i ++ ) {
                if ( in[i] == 0 ) que.push({i});
        }
        vector<int> res;
        while ( que.size() ) {
                res.push_back(que.top().x);
                int x = que.top().x; que.pop();
                for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                        in[edge[i].to] --;
                        if ( !in[edge[i].to] ) que.push({edge[i].to});
                }
        }
        if ( res.size() != n ) { cout << "-1" << endl; return 0;}
        for ( int i = 0; i < res.size(); i ++ ) cout << res[i] << " ";
}
```
