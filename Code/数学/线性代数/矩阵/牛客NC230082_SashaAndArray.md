# 🔗
<a href="https://ac.nowcoder.com/acm/contest/24157/C"><img src="https://i.loli.net/2021/11/25/yJkxhsDW2CSl9cY.png"></a>

# 💡
一个涉及到区间修改和区间求和的问题  
且  <img src="https://latex.codecogs.com/svg.image?\inline&space;a_i" title="\inline a_i" />  到最后会很大，所以想矩阵  <img src="https://latex.codecogs.com/svg.image?\inline&space;ksm" title="\inline ksm" />  ，我们设置  <img src="https://latex.codecogs.com/svg.image?\inline&space;base" title="\inline base" />  矩阵就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;fibonacci" title="\inline fibonacci" />  的基础矩阵  
那么在矩阵里面区间修改加也就是变成了区间修改乘（区间和矩阵乘上  <img src="https://latex.codecogs.com/svg.image?\inline&space;base" title="\inline base" />  矩阵的  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline c" />  次方  
区间乘可以由乘法分配律满足，所以线段树懒标记就可以实现    
而统计的时候就是区间查询加，这个就直接用线段树的区间求和数组计算加后的矩阵  
由于满足乘法分配律，我们直接用初始的竖矩阵去乘这个区间和矩阵就行了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
struct Mat {
        ll m[2][2];
        inline Mat() {}
        inline Mat ( int e ) {
                for ( int i = 0; i < 2; i ++ ) 
                        for ( int j = 0; j < 2; j ++ )
                                m[i][j] = e * (i == j);
        }
        inline Mat operator + ( Mat a ) {
                Mat res(0);
                for ( int i = 0; i < 2; i ++ )
                        for ( int j = 0; j < 2; j ++ )
                                res.m[i][j] = (a.m[i][j] + m[i][j]) % mod;
                return res;
        }
        inline friend Mat operator * ( Mat a, Mat b ) {
                Mat res(0);
                for ( int i = 0; i < 2; i ++ )
                        for ( int j = 0; j < 2; j ++ )
                                for ( int k = 0; k < 2; k ++ )
                                        res.m[i][j] = (res.m[i][j] + a.m[i][k] * b.m[k][j] % mod) % mod;
                return res;
        }
        inline bool operator == ( Mat b ) {
                for ( int i = 0; i < 2; i ++ )
                        for ( int j = 0; j < 2; j ++ )
                                if ( m[i][j] != b.m[i][j] ) return false;
                return true;
        }
} base, one(1), zero(0), res(0);
inline Mat ksm ( Mat a, ll b ) { Mat res(1); while ( b ) { if ( b & 1 ) res = res * a; a = a * a; b >>= 1; } return res; }

const int N = 1e5 + 10;
int n, m, a[N];

struct SegmenTree {
        Mat val, lazy;
} sgtr[N << 2];
inline void PushUp ( int rt ) { sgtr[rt].val = sgtr[rt << 1].val + sgtr[rt << 1 | 1].val; }
inline void PushDown ( int rt, int l, int r ) {
        auto &cur = sgtr[rt], &lson = sgtr[rt << 1], &rson = sgtr[rt << 1 | 1];
        if ( cur.lazy == one ) return;

        int mid = (l + r) >> 1;
        lson.val = lson.val * cur.lazy; lson.lazy = lson.lazy * cur.lazy;
        rson.val = rson.val * cur.lazy; rson.lazy = rson.lazy * cur.lazy;
        cur.lazy = one;
}
inline void Build ( int l, int r, int rt ) {
        sgtr[rt].lazy = one;
        if ( l == r ) {
                if ( a[l] == 1 )      sgtr[rt].val.m[0][0] = 1;
                else if ( a[l] == 2 ) sgtr[rt].val.m[0][0] = sgtr[rt].val.m[0][1] = 1;
                else                  sgtr[rt].val = res * ksm(base, a[l] - 2);
                return;
        }

        int mid = (l + r) >> 1;
        Build ( l, mid, rt << 1 );
        Build ( mid + 1, r, rt << 1 | 1);
        PushUp ( rt ); 
}
inline void Update ( int a, int b, Mat c, int l, int r, int rt ) {
        if ( a <= l && r <= b ) {
                sgtr[rt].val = sgtr[rt].val * c;
                sgtr[rt].lazy = sgtr[rt].lazy * c;
                return;
        }
        if ( a > r || b < l ) return;
        int mid = (l + r) >> 1;
        PushDown ( rt, l, r );
        Update ( a, b, c, l, mid, rt << 1 );
        Update ( a, b, c, mid + 1, r, rt << 1 | 1 );
        PushUp ( rt );
}
inline ll Query ( int a, int b, int l, int r, int rt ) {
        if ( a <= l && r <= b ) return sgtr[rt].val.m[0][0];
        if ( a > r || b < l )   return 0;
        PushDown ( rt, l, r );
        int mid = (l + r) >> 1;
        return (Query ( a, b, l, mid, rt << 1 ) + Query ( a, b, mid + 1, r, rt << 1 | 1 )) % mod;
}

int main () {
        base.m[0][0] = base.m[0][1] = base.m[1][0] = 1; base.m[1][1] = 0;
        res.m[0][0] = res.m[0][1] = 1;

        cin >> n >> m;
        for ( int i = 1; i <= n; i ++ ) cin >> a[i];
        Build ( 1, n, 1 );

        while ( m -- ) {
                int op; cin >> op;
                if ( op == 1 ) {
                        int l, r, x; cin >> l >> r >> x;
                        Update ( l, r, ksm(base, x), 1, n, 1 );
                } else {
                        int l, r; cin >> l >> r;
                        cout << Query ( l, r, 1, n, 1 ) << endl;
                }
        }
}
```
