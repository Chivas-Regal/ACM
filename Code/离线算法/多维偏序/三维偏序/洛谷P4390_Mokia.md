# 🔗
<a href="https://www.luogu.com.cn/problem/P4390"><img src="https://s2.loli.net/2022/01/08/2rqsQxUKJlPb3oM.png"></a>

# 💡
带了修改时间的[《老C的任务》](https://github.com/Chivas-Regal/ACM/blob/main/Code/%E7%A6%BB%E7%BA%BF%E7%AE%97%E6%B3%95/%E5%A4%9A%E7%BB%B4%E5%81%8F%E5%BA%8F/%E4%BA%8C%E7%BB%B4%E5%81%8F%E5%BA%8F/AcWing2849_%E8%80%81C%E7%9A%84%E4%BB%BB%E5%8A%A1.md)  
那么就俨然成为了一道三维偏序问题（第三维：修改时间  
  
做法一样，我们设置一个时间递进器  
对于加人，我们就在这个该时刻的这个  <img src="https://latex.codecogs.com/svg.image?\inline&space;(x,y)" title="\inline (x,y)" /> 添加一个信息  
对于查询，由于是二维，我们依旧用二维前缀和的方式，将二维区间和的四个信息分别设置  <img src="https://latex.codecogs.com/svg.image?\inline&space;\pm1" title="\inline " /> 然后我们在记录  <img src="https://latex.codecogs.com/svg.image?\inline&space;res[q[i].which\_qry]" title="\inline res[q[i].which\_qry]" /> 时就可以累加  <img src="https://latex.codecogs.com/svg.image?\inline&space;q[i].sgn\times&space;q[i].res" title="\inline q[i].sgn\times&space;q[i].res" /> ，由于查询要查四个数据，我们可以放在连续时刻的四个信息里面  
而我们这三维关系就是对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" /> ， <img src="https://latex.codecogs.com/svg.image?\inline&space;q[i].x\le&space;q[j].x\wedge&space;q[i].y\le&space;q[j].y\wedge&space;q[i].t<q[j].t" title="\inline q[i].x\le&space;q[j].x\wedge&space;q[i].y\le&space;q[j].y\wedge&space;q[i].t\lt&space;q[j].t" />   
第二维  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 用归并  
第三维  <img src="https://latex.codecogs.com/svg.image?\inline&space;t" title="\inline t" /> 在归并中用树状数组即可  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e6 + 10;

namespace TreeArray {
        int tr[N];
        inline int lowbit ( int x ) { return x & -x; }
        inline void update ( int x, int v ) {
                while ( x < N ) tr[x] += v, x += lowbit(x);
        }
        inline int query ( int x ) {
                int res = 0;
                while ( x > 0 ) res += tr[x], x -= lowbit(x);
                return res;
        }
} using namespace TreeArray;

struct node {
        int x, y, v, t;
        int is_qry, which_qry, sgn;
        ll res;
        inline friend bool operator < ( node a, node b ) {
                if ( a.x != b.x ) return a.x < b.x;
                if ( a.y != b.y ) return a.y < b.y;
                return a.t < b.t;
        }
} q[N], w[N];
int tim = 1, qryid;
ll res[N];

inline void merge_Sort (int l, int r) {
        if ( l >= r ) return;
        int mid = (l + r) >> 1;
        merge_Sort(l, mid); merge_Sort(mid + 1, r);

        int i, j, k;

        i = l, j = mid + 1, k = 0;
        while ( i <= mid && j <= r ) {
                if ( q[i].y <= q[j].y ) update(q[i].t, q[i].v), w[k ++] = q[i ++];
                else q[j].res += query(q[j].t), w[k ++] = q[j ++];
        }
        while ( i <= mid ) update(q[i].t, q[i].v), w[k ++] = q[i ++];
        while ( j <= r ) q[j].res += query(q[j].t), w[k ++] = q[j ++];
        for ( i = l; i <= mid; i ++ ) update(q[i].t, -q[i].v);
        for ( i = l, j = 0; j < k; i ++, j ++ ) q[i] = w[j];
}

inline void Solve () {
        int op; while ( cin >> op, op != 3 ) {
                if ( op == 1 ) {
                        int x, y, a; cin >> x >> y >> a; x ++, y ++;
                        q[tim] = {x, y, a, tim, 0}; tim ++;
                } else if ( op == 2 ) {
                        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; x1 ++, y1 ++, x2 ++, y2 ++;
                        q[tim] = {x2,     y2,     0, tim, 1, qryid, 1,  0}; tim ++;
                        q[tim] = {x1 - 1, y2,     0, tim, 1, qryid, -1, 0}; tim ++;
                        q[tim] = {x2,     y1 - 1, 0, tim, 1, qryid, -1, 0}; tim ++;
                        q[tim] = {x1 - 1, y1 - 1, 0, tim, 1, qryid, 1,  0}; tim ++;
                        qryid ++;
                }
        } 
        sort ( q + 1, q + tim ); 
        merge_Sort (1, tim - 1);
        for ( int i = 1; i < tim; i ++ ) {
                if ( q[i].is_qry ) {
                        res[q[i].which_qry] += q[i].res * q[i].sgn;
                }
        }
        for ( int i = 0; i < qryid; i ++ ) {
                cout << res[i] << endl;
        }
}
```
