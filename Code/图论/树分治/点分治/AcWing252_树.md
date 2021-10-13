# 🔗
<a href="https://www.acwing.com/problem/content/description/254/"><img src="https://i.loli.net/2021/09/27/e9TvVhaQmuU4icR.png"></a>

# 💡
路径分类：  
1.两点都在一个子树内，那么递归处理子树即可  
2.两点在不同子树内(路经重心)，求所有子树内每一个点到重心的距离，两两匹配，如果和<=k，路径满足要求  
但会有不应在本情况的对出现，即选中两个点在一个子树内，可以容斥地删掉不合法路径：减去两点都在一个子树地匹配情况  
3.某个点是重心(边界情况)，从重心开始向子树遍历，求每个点到重心的距离是不是k  
  
如何求过重心的方案？  
也就是给一堆数，任取两点总和<=k的方案数  
排好序后对每个数向后二分最大是多少，也可以双指针取长度  
  
容斥：  
从当前点出发寻找重心，删去  
求每个子树满足条件的值分别减去，将满足点加入大集合  
最后加一下大集合的配对数量，递归子树继续解决

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e4 + 10, M = N * 2;
int n, m;
struct Edge { int nxt, to, val; } edge[M]; int head[M], cnt;
bool st[N];
int allSon[N], oneSon[N]; // 所有子树的点数、一个子树的点数

inline void Init () {
        memset ( head, -1, sizeof head );
        memset ( st, 0, sizeof st );
        cnt = 0;
}
inline void add_Edge ( int from, int to, int val ) {
        edge[ ++ cnt ] = { head[from], to, val };
        head[from] = cnt;
}
inline int get_Sz ( int x, int fath ) { // 求子树大小
        if ( st[x] ) return 0;
        int res = 1;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                res += get_Sz ( to, x );
        }
        return res;
}
inline int get_Wc ( int x, int fath, int tot, int &wc ) { // 求重心，返回子树大小
        if ( st[x] ) return 0;
        int sum = 1, mxSon = 0; //子树大小、最大剩余块
        for ( int i = head[x]; ~i; i = edge[i].nxt ) { 
                int to = edge[i].to;
                if ( to == fath ) continue;
                int t = get_Wc ( to, x, tot, wc ); 
                sum += t; 
                mxSon = max ( mxSon, t );
        }
        mxSon = max ( mxSon, tot - sum ); // 与另一侧的块进行比较
        if ( mxSon <= tot / 2 ) wc = x; // 如果最大剩余连通块小于总块的1/2，重心为它
        return sum;
}
inline void get_Dis ( int x, int fath, int dist, int &tot ) { // 获取一棵子树的所有点到重心的距离
        if ( st[x] ) return;
        oneSon[tot ++] = dist;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int to = edge[i].to;
                if ( to == fath ) continue;
                get_Dis ( to, x, dist + edge[i].val, tot );
        }
}
inline int get_Num ( int a[], int k ) { // 双指针去查找满足加起来<=k的点数
        sort ( a, a + k ); int res = 0;
        for ( int i = k - 1, j = -1; i >= 0; i -- ) {
                while ( j + 1 < i && a[j + 1] + a[i] <= m ) j ++;
                j = min ( j, i - 1 );
                res += j + 1;
        }
        return res;
}
inline int Solve ( int x ) {
        if ( st[x] ) return 0;
        get_Wc ( x, -1, get_Sz ( x, -1 ), x ); // 找重心
        st[x] = 1; // 删重心

        int res = 0, cnt_allSon = 0;
        for ( int i = head[x]; ~i; i = edge[i].nxt ) {
                int cnt_oneSon = 0, to = edge[i].to;
                get_Dis ( to, -1, edge[i].val, cnt_oneSon ); // 记录一个子树的点
                res -= get_Num ( oneSon, cnt_oneSon ); // 减去一个子树内满足条件的点对数
                for ( int j = 0; j < cnt_oneSon; j ++ ) 
                        res += oneSon[j] <= m, // 与重心相连的路径
                        allSon[cnt_allSon ++] = oneSon[j]; // 这个子树点塞入总点中
        }
        res += get_Num ( allSon, cnt_allSon ); // 加上所有点满足条件的对

        for ( int i = head[x]; ~i; i = edge[i].nxt ) res += Solve ( edge[i].to ); // 进行下一层
        return res;

}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        while ( scanf("%d%d", &n, &m) == 2, n || m ) {
                Init();
                for ( int i = 1, a, b, c; i < n; i ++ ) 
                        scanf("%d%d%d", &a, &b, &c),
                        add_Edge ( a, b, c ),
                        add_Edge ( b, a, c );
                printf("%d\n", Solve(0));
        }
}
```
