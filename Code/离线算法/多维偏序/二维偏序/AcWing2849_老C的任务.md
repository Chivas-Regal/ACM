# 🔗
<a href="https://www.acwing.com/problem/content/2849/"><img src="https://i.loli.net/2021/10/03/wqlsa1oPUgYFIJC.png"></a>

# 💡
这道题和[Stars](https://github.com/Chivas-Regal/ACM/blob/main/Code/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84/Stars.md)那道题很像  
其实都是在(<=x, <=y)上做文章  
但是这道题有一个特殊的地方就是要求区间  
那么可以想到前缀和->二维前缀和  
只需要将要查的矩形的四个点也传入要排序的数组中  
并标记为id=1(查询)，id=0(插入)  
那么就需要多出第三维（<=id）  
但是id我们每次求得只有前面id=0的点，所以一个变量就够了
  
**解法1:树状数组**  
如果当前遍历到的点是查询点的话就不update，而是query，查询后塞到查询的结构体中。否则update  
然后对一个查询结构体内的传进的四次query进行排序，最大的就是右下角的点，中等的是左下右上，最小的是左上  
然后用二维前缀和计算的方式进行计算即可  
**解法2:归并排序**  
就对查询点加一个val，在归并到时候对第二维进行排序  
然后双指针扫描固定，中途累加，如果是插入点就+1，否则+0，然后j的位置移动的时候加上这个sum即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
**解法1:树状数组**  
```cpp
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
**解法2:归并排序**
```cpp
const int N = 1e5 + 10, M = 5e5 + 10;
int n, m;
struct Data { 
        int a, b, c;
        int isQry, whichQry, sgn;
        ll sum;
}q[M], w[M];
ll res[N];

inline void merge_Sort ( int l, int r ) {
        if ( l >= r ) return;
        int mid = (l + r) >> 1;
        merge_Sort (l, mid); merge_Sort (mid + 1, r);
        int i = l, j = mid + 1, k = 0;
        ll sum = 0;
        while ( i <= mid && j <= r )
                if ( q[i].b <= q[j].b ) sum += !q[i].isQry * q[i].c, w[k ++] = q[i ++];
                else                    q[j].sum += sum,             w[k ++] = q[j ++];
        while ( i <= mid ) sum += !q[i].isQry * q[i].c, w[k ++] = q[i ++];
        while ( j <= r )   q[j].sum += sum,             w[k ++] = q[j ++];
        for ( i = l, j = 0; j < k; i ++, j ++ ) q[i] = w[j];
}

int main () {
        ios::sync_with_stdio(false);
        cin >> n >> m;
        for ( int i = 0; i < n; i ++ )
                cin >> q[i].a >> q[i].b >> q[i].c;
        int k = n;
        for ( int i = 0; i < m; i ++ ) {
                int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                q[k ++] = {x1 - 1, y1 - 1, 0, 1, i, 1};
                q[k ++] = {x1 - 1, y2,     0, 1, i, -1};
                q[k ++] = {x2,     y1 - 1, 0, 1, i, -1};
                q[k ++] = {x2,     y2,     0, 1, i, 1};
        }
        sort ( q, q + k, [&](Data a, Data b) {
                if ( a.a != b.a ) return a.a < b.a;
                if ( a.b != b.b ) return a.b < b.b;
                return a.isQry < b.isQry;
        });
        merge_Sort ( 0, k - 1 );
        for ( int i = 0; i < k; i ++ )
                if ( q[i].isQry )
                        res[q[i].whichQry] += q[i].sum * q[i].sgn;
        for ( int i = 0; i < m; i ++ ) cout << res[i] << endl;
        return 0;
}
```
