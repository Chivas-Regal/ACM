# 🔗
https://ac.nowcoder.com/acm/contest/13647/A

# 💡
线段树储存前后缀最小值  
从而在区间内未出现的最小数O(1)查询


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#define rep1(i, a, n) for (ll i = a; i <= n; i++)
#define rep2(i, a, n) for (ll i = a; i >= n; i--)
#define mm(a, b) memset(a, b, sizeof(a))
#define each_cass(cass) for (cin >> cass; cass; cass--)
typedef long long ll;
void mc(ll *aa, ll *a, ll len) { rep1(i, 1, len) * (aa + i) = *(a + i); }
const int INF = 0x7FFFFFFF;
const ll LNF = 1e18;
const double G = 10;
const double eps = 1e-6;
const double PI = acos(-1.0);
const int mod = 1e9 + 7;
using namespace std;
const int maxn = 1e5 + 10;
int minn[maxn << 2];
int a[maxn];

void PushUp(int rt) { minn[rt] = min(minn[rt << 1], minn[rt << 1 | 1]); }
void Build(int l, int r, int rt)
{
    if (l == r)
    {
        minn[rt] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(l, mid, rt<<1);
    Build(mid + 1, r, rt<<1|1);
    PushUp(rt);
}
int Query(int a, int b, int l, int r, int rt)
{
    if (a > r || b < l)
        return INF;
    if (a <= l && b >= r)
        return minn[rt];
    int mid = (l + r) >> 1;
    return min(Query(a, b, l, mid, rt << 1), Query(a, b, mid + 1, r, rt << 1 | 1));
}
int main()
{
    int n, q;
    cin >> n >> q;
    a[0]=a[n+1]=n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Build(0, n+1, 1);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << min(Query(0, l-1, 0, n+1, 1), Query(r+1, n+1, 0, n+1, 1)) << endl;
    }
}
```
