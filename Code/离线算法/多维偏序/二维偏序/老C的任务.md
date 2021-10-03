# 🔗
<a href="https://www.acwing.com/problem/content/2849/"><img src="https://i.loli.net/2021/10/03/wqlsa1oPUgYFIJC.png"></a>

# 💡
这道题和[Stars](https://github.com/Chivas-Regal/ACM/blob/main/Code/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84/Stars.md)那道题很像  
其实都是在(<=x, <=y)上做文章  
但是这道题有一个特殊的地方就是要求区间  
那么可以想到前缀和->二维前缀和  
  
只需要将要查的矩形的四个点也传入要排序的数组中  
标记一下再排序（还是双关键字），如果当前遍历到的点是查询点的话就不update，而是query，查询后塞到查询的结构体中。否则update  
然后对一个查询结构体内的传进的四次query进行排序，最大的就是右下角的点，中等的是左下右上，最小的是左上  
然后用二维前缀和计算的方式进行计算即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll N = 1e5 + 10, M = 1e6 + 10;
struct Qry { // 询问
        ll x1, y1, x2, y2;
        ll k;
        ll res[4];
}q[N];
struct Node { // 点
        ll x, y, v; // 坐标，点权
        ll id; // 编号
}nd[M];
ll tr[M]; // 树状数组
bool isqry[M]; // 记录这个点是不是询问点，如果是询问点就要拔出
ll whichqry[M]; // 属于哪一个询问
ll n, m;
ll k; // 点个数
vector<ll> nums; // 对y离散化

inline ll get_Id ( ll x ) { return lower_bound(nums.begin(), nums.end(), x) - nums.begin() + 1; }
inline ll lowbit ( ll x ) { return x & -x; }
inline void update ( ll id, ll val ) {
        while ( id < M ) tr[id] += val, id += lowbit(id);
}
inline ll query ( ll id ) {
        ll res = 0;
        while ( id ) res += tr[id], id -= lowbit(id);
        return res;
}

int main () {
        scanf("%lld%lld", &n, &m);
        for ( ll i = 0, x, y, z; i < n; i ++ ) {
                scanf("%lld%lld%lld", &x, &y, &z);
                nd[k] = {x, y, z, M - 1}; k ++;
                nums.push_back(y);
        }
        for ( ll i = 0, x1, y1, x2, y2; i < m; i ++ ) {
                scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
                q[i] = {x1, y1, x2, y2};
                isqry[k] = true; whichqry[k] = i; nd[k] = {x1 - 1, y1 - 1, 1, k}; k ++;
                isqry[k] = true; whichqry[k] = i; nd[k] = {x2,     y2,     1, k}; k ++;
                isqry[k] = true; whichqry[k] = i; nd[k] = {x1 - 1, y2,     1, k}; k ++;
                isqry[k] = true; whichqry[k] = i; nd[k] = {x2,     y1 - 1, 1, k}; k ++;
                nums.push_back(y1 - 1); nums.push_back(y2 - 1); nums.push_back(y2); nums.push_back(y1);
        }
        sort ( nums.begin(), nums.end() );
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        
        sort ( nd, nd + k, [&](Node a, Node b){
                if ( a.x != b.x ) return a.x < b.x;
                if ( a.y != b.y ) return a.y < b.y;
                return a.id > b.id;
        });
        for ( ll i = 0; i < k; i ++ ) {
                if ( !isqry[nd[i].id] ) { // 不是查询
                        update (get_Id(nd[i].y), nd[i].v); // 更新
                } else {
                        ll thisqry = whichqry[nd[i].id]; // 这个点是哪个查询
                        q[thisqry].res[q[thisqry].k ++] = query(get_Id(nd[i].y)); // 对这个询问的一个res加入一个前缀和
                }
        }
        for ( ll i = 0; i < m; i ++ ) {
                sort ( q[i].res, q[i].res + 4, greater<ll>() ); 
                printf("%lld\n", q[i].res[0] - q[i].res[1] - q[i].res[2] + q[i].res[3]); // 二维区间和
        }
}
```
