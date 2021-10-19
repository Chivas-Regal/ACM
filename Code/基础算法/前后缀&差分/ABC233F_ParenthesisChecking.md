# 🔗
<a href="https://atcoder.jp/contests/abc223/tasks/abc223_f"><img src="https://user-images.githubusercontent.com/78973908/137866247-01669ac7-7e42-4d9b-b8c2-699b3f2d97cc.png"></a>

# 💡
**括号匹配的本质是两两相消。**  
对于每一个位置的点重定义一下它的权值：`'(' = 1，')' = -1`  
在累加过程中，<img src="https://latex.codecogs.com/svg.image?1" title="1" />可以和<img src="https://latex.codecogs.com/svg.image?-1" title="-1" />相消为<img src="https://latex.codecogs.com/svg.image?0" title="0" />，所以**计算总贡献**  

那么可以记录一个**权值前缀和**  
那么对于每一个区间，如果其中的**最小值**小于 <img src="https://latex.codecogs.com/svg.image?l-1" title="l-1" /> 的前缀和的话，那么就一定是不匹配的（最小值的位置前右括号太多了  
当然如果本身 <img src="https://latex.codecogs.com/svg.image?l-1" title="l-1" /> 的前缀和不等于 <img src="https://latex.codecogs.com/svg.image?r" title="r" /> 的前缀和就也是不匹配的  
这里的最小值可以使用线段树进行维护，修改便直接在线段树上修改如果本身是'('，修改后区间-2，否则+2  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <deque>

using namespace std;

#define ll long long

const int N = 2e5 + 10;
char s[N];
int a[N], n, q;

namespace SegmentTree {
        struct Sgtr { int val, lazy; } sgtr[N << 2];
        inline void push_Up ( int rt ) {
                sgtr[rt].val = min ( sgtr[rt << 1].val, sgtr[rt << 1 | 1].val );
        }
        inline void push_Down ( int l, int r, int rt ) {
                if ( !sgtr[rt].lazy ) return;
                sgtr[rt << 1].val += sgtr[rt].lazy;
                sgtr[rt << 1 | 1].val += sgtr[rt].lazy;
                sgtr[rt << 1].lazy += sgtr[rt].lazy;
                sgtr[rt << 1 | 1].lazy += sgtr[rt].lazy;
                sgtr[rt].lazy = 0;
        }
        inline void Build ( int l, int r, int rt ) {
                if ( l == r ) { sgtr[rt].val = a[l]; return; }
                int mid = (l + r) >> 1;
                Build ( l, mid, rt << 1 );
                Build ( mid + 1, r, rt << 1 | 1 );
                push_Up ( rt ); 
        }
        inline void Update ( int a, int b, int c, int l, int r, int rt ) {
                if ( a <= l && r <= b ) { sgtr[rt].lazy += c, sgtr[rt].val += c; return; }
                if ( a > r || b < l ) return;
                int mid = (l + r) >> 1;
                push_Down ( l, r, rt );
                Update ( a, b, c, l, mid, rt << 1 );
                Update ( a, b, c, mid + 1, r, rt << 1 | 1 );
                push_Up ( rt );
        }
        inline int Query ( int a, int b, int l, int r, int rt ) {
                if ( a <= l && r <= b ) return sgtr[rt].val;
                if ( a > r || b < l )   return N;
                int mid = (l + r) >> 1;
                push_Down ( l, r, rt );
                return min ( Query ( a, b, l, mid, rt << 1 ), Query ( a, b, mid + 1, r, rt << 1 | 1) ); 
        }
} using namespace SegmentTree;

int main () {
        ios::sync_with_stdio(false);
        cin >> n >> q >> (s + 1);
        for ( int i = 1; i <= n; i ++ ) 
                if ( s[i] == '(' ) a[i] = a[i - 1] + 1;
                else               a[i] = a[i - 1] - 1;
        Build ( 1, n, 1 );
        while ( q -- ) {
                int op, l, r; cin >> op >> l >> r;
                if ( op == 1 ) {
                        if ( s[l] == s[r] ) continue;
                        if ( s[l] == '(' ) Update ( l, r - 1, -2, 1, n, 1 );
                        else               Update ( l, r - 1,  2, 1, n, 1 );
                        swap ( s[l], s[r] );
                } else {
                        int L = l == 1 ? 0 : Query ( l - 1, l - 1, 1, n, 1 ), R = Query ( r, r, 1, n, 1 );
                        if ( L != R ) { cout << "No" << endl; continue; }
                        if ( Query ( l, r, 1, n, 1 ) < L ) { cout << "No" << endl; continue; }
                        cout << "Yes" << endl;
                }
        }
}
```
