# 🔗
<a href="https://www.luogu.com.cn/problem/P1972"><img src="https://i.loli.net/2021/09/23/CZdUyPovu9sxtTi.png"></a>

# 💡
一道主席树查找区间不同数的个数的模板题  
对于每个数，就算出现很多次，我们在求的时候实际关注的还是最右侧的位置  
那么在本题里面可以用主席树构建前缀数列中每一个数出现的最右侧的位置  
这样我们就可以在很少的修改下，将一个数列的每个前缀数列中的每个数出现的最右侧位置记录下来了  
那么还是两步  
  
**1.插入**  
在a[i]插入时以上一个版本删掉之前a[i]出现过的位置，在当前版本加入i这个位置    
**2.查询**  
输入l, r  
对于版本r，查询数列中l位置之后的数的出现个数  
若`l <= mid`，那么我们该向左固定区间，同时得知右一半的区间均满足，则 `res += query () + sgtr[sgtr[rt].r].sum`  
若`l > mid`，那么我们该向右固定区间，就还是正常的查询 `res += query()`

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;

const int N = 1e6 + 10;
int a[N], n, m;
struct node {
        int l, r, sum;
} sgtr[N * 40];
int root[N], tot;
int lastPos[1000010];

inline void insert ( int l, int r, int pre, int &now, int p, int op ) {
        sgtr[++tot] = sgtr[pre];
        now = tot;
        sgtr[now].sum += op;

        if ( l == r ) return;

        int mid = (l + r) >> 1;
        if ( p <= mid ) insert ( l, mid, sgtr[pre].l, sgtr[now].l, p, op );
        else insert ( mid + 1, r, sgtr[pre].r, sgtr[now].r, p, op );
}

inline int query ( int l, int r, int rt, int pos ) {
        if ( l == r ) return sgtr[rt].sum;
        int res = 0, mid = (r + l) >> 1;
        if ( pos <= mid ) res += query ( l, mid, sgtr[rt].l, pos ) + sgtr[sgtr[rt].r].sum;
        else res += query ( mid + 1, r, sgtr[rt].r, pos );
        return res;
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        scanf("%d", &n);
        for ( int i = 1; i <= n; i ++ ) 
                scanf("%d", &a[i]);

        for ( int i = 1; i <= n; i ++ ) {
                if ( lastPos[a[i]] ) {
                        insert ( 1, n, root[i - 1], root[i], lastPos[a[i]], -1 );
                        insert ( 1, n, root[i], root[i], i, 1 );
                } else {
                        insert ( 1, n, root[i - 1], root[i], i, 1 );
                }
                lastPos[a[i]] = i;
        }

        scanf("%d", &m);
        while ( m -- ) {
                int l, r; scanf("%d%d", &l, &r);
                printf("%d\n", query(1, n, root[r], l) );
        }
}

```
