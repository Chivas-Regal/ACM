# 🔗
<a href="https://www.luogu.com.cn/problem/P4137"><img src="https://i.loli.net/2021/09/24/8jlF1bTrPG6XHes.png"></a>

# 💡
我们可以对每个数存一个最右端位置  
然后维护一下这个前缀版本区间内的最小下标  
在查询[l,r]的时候，只需要查询在root[r]的版本下，下标没有出现在l后的最小的数  
那么每次就是对左右子树分别查看，这个最小下标是否可以出现在子树内，来决定递归哪一个  
肯定优先递归左子树，所以只有左子树的val>=pos的时候，才做右子树  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

const int N = 3e5 + 10;
struct node {
        int l, r;
        int val; // 维护当前区间内每个数最右侧下标的最小值
} sgtr[N * 40];
int root[N], tot;
int n, a[N], m, x, y;

inline void insert ( int l, int r, int pre, int &now, int p, int c ) { // p是数值，c是新下标
        sgtr[++tot] = sgtr[pre];
        now = tot;
        if ( l == r ) { // 更新
                sgtr[now].val = c;
                return;
        }
        int mid = (l + r) >> 1;
        if ( p <= mid ) // 新数值改变左子树
                insert ( l, mid, sgtr[pre].l, sgtr[now].l, p, c ); 
        else 
                insert ( mid + 1, r, sgtr[pre].r, sgtr[now].r, p, c );
        sgtr[now].val = min ( sgtr[sgtr[now].l].val, sgtr[sgtr[now].r].val ); // 更新一下最小值（pushup）
}

inline int query ( int l, int r, int rt, int pos ) { // 查询 MEX
        if ( l == r ) return l;
        int mid = (l + r) >> 1;
        if ( sgtr[sgtr[rt].l].val >= pos ) // 若左子树右侧下标最小值都出现在[L,R]区间内，就查询右子树 
                return query ( mid + 1, r, sgtr[rt].r, pos );
        else                               // 否则查询左子树
                return query ( l, mid, sgtr[rt].l, pos );
}


int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        scanf("%d%d", &n, &m);
        for ( int i = 1; i <= n; i ++ ) 
                scanf("%d", &a[i]);

        for ( int i = 1; i <= n; i ++ ) {
                insert ( 0, 1e9, root[i - 1], root[i], a[i], i ); // ai插入主席树并将ai位置更新为i
        } 
        while ( m -- ) {
                int l, r; scanf("%d%d", &l, &r);
                printf("%d\n", query ( 0, 1e9, root[r], l ) );
        }
}

```
