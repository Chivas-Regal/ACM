# 🔗
<a href="https://www.acwing.com/problem/content/2817/"><img src="https://i.loli.net/2021/10/05/AXjtPNe9C2L7siQ.png"></a>

# 💡
本题中要处理一下相同的data，即三维均相等的元素    
则每一个data的权值都是这个数出现的个数  
  
首先对.a排序，然后我们用归并一步步合并两个区间  
在合并区间的时候，两个指针中左区间的指针每走一次都代表出现一个比当前右指针位置严格小的，就向后移动1同时在树状数组内更新这个点的权值  
右指针走之前累加一下它之前的树状数组前缀  
  
最后在计算答案时，就是将相同的数的个数加到最后一个具有代表性的点`q[i].res + q[i].cnt - 1`，因为他们的权值也会是相同的，所以要加上`q[i].cnt`    

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e5 + 10, M = 2e5 + 10;
struct Data {
        int a, b, c;
        int cnt, res;
        inline friend bool operator < (Data a, Data b) {
                if ( a.a != b.a ) return a.a < b.a;
                if ( a.b != b.b ) return a.b < b.b;
                return a.c < b.c;
        }
        inline friend bool operator == ( Data a, Data b) {
                return a.a == b.a && a.b == b.b && a.c == b.c;
        }
}q[N], w[N];
int res[N], n, m;

namespace TreeArray {
        int tr[M];
        inline int lowbit ( int x ) { return x & -x; }
        inline void update ( int x, int val ) { while ( x < M ) tr[x] += val, x += lowbit(x); }
        inline int query ( int x ) { int res = 0; while ( x > 0 ) res += tr[x], x -= lowbit(x); return res; }
} using namespace TreeArray;

inline void merge_Sort ( int l, int r ) {
        if ( l >= r ) return;
        int mid = (l + r) >> 1;
        merge_Sort ( l, mid ); merge_Sort ( mid + 1, r );

        int i = l, j = mid + 1, k = 0;
        while ( i <= mid && j <= r )
                if ( q[i].b <= q[j].b ) update ( q[i].c, q[i].cnt ), w[k ++] = q[i ++];
                else                    q[j].res += query ( q[j].c ), w[k ++] = q[j ++];
        while ( i <= mid ) update ( q[i].c, q[i].cnt ), w[k ++] = q[i ++];
        while ( j <= r )   q[j].res += query ( q[j].c ), w[k ++] = q[j ++];
        for ( int i = l; i <= mid; i ++ ) update ( q[i].c, -q[i].cnt );
        for ( int i = l, j = 0; j < k; j ++, i ++ ) q[i] = w[j];
}

int main () {
        ios::sync_with_stdio(false);
        cin >> n >> m;
        for ( int i = 0; i < n; i ++ )
                cin >> q[i].a >> q[i].b >> q[i].c,
                q[i].cnt = 1;
        sort ( q, q + n );
        int k = 1;
        for ( int i = 1; i < n; i ++ ) 
                if ( q[i] == q[k - 1] ) q[k - 1].cnt ++;
                else                    q[k ++] = q[i];
        merge_Sort ( 0, k - 1 );
        for ( int i = 0; i < k; i ++ )
                res[q[i].res + q[i].cnt - 1] += q[i].cnt;
        for ( int i = 0; i < n; i ++ )
                cout << res[i] << endl;
}
```
