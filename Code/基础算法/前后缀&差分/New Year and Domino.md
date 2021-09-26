# 🔗
<a href="https://codeforces.com/problemset/problem/611/C"><img src="https://user-images.githubusercontent.com/78973908/132656458-7e71dbd7-a4b8-4f48-b75e-07a89960f037.png"></a>

# 💡
因为行和列地位一样，接下来说行的性质也就是列的性质  
  
对于每个区间[l,r]我们查询的时候对于[l,l+1]和[l+1,l]的摆放方式其实是一样的，所以我们可以默认这个牌向左（上）摆放  
而摆放方式只有两种：左和上  
那么我们可以做两套前缀和  
sumrow[i][j]表示第i行的前j个格子可以横着放多少个牌  
sumcol[i][j]表示第j列第前i个格子可以竖着放多少个牌  
那么对于初始化的时候，如果当前格子和上一个格子有一个是"#"那么都不能累加，因为都没法放  
  
然后查询的时候，直接查sum[][r]-sum[][l]或sum[r][]-sum[l][]即可  
因为我们不需要第l个，它没法贡献  
每一行和每一列都遍历一次累加计算一下  
  
  
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <list>
using namespace std;
#define ll long long
#define eps 1e-12

const ll N = 510;
ll sumcol[N][N], sumrow[N][N];

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        ll n, m; cin >> n >> m;
        string Map[N];
        for ( ll i = 0; i < n; i ++ ) cin >> Map[i];
        for ( ll i = 0; i < n; i ++ ) {
                for ( ll j = 1; j < m; j ++ ) {
                        if ( Map[i][j - 1] == '.' && Map[i][j] == '.' ) sumrow[i][j] = sumrow[i][j - 1] +  1;
                        else sumrow[i][j] = sumrow[i][j - 1];  
                }
        }
        for ( ll j = 0; j < m; j ++ ) {
                for ( ll i = 1; i < n; i ++ ) {
                        if ( Map[i - 1][j] == '.' && Map[i][j] == '.' ) sumcol[i][j] = sumcol[i - 1][j] +  1;
                        else sumcol[i][j] = sumcol[i - 1][j];  
                }
        }
        ll q; cin >> q;
        while ( q -- ) {
                ll res =  0;
                ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                x1 --, y1 --, x2 --, y2 --;
                for ( ll i = x1; i <= x2; i ++ ) res += sumrow[i][y2] - sumrow[i][y1];
                for ( ll i = y1; i <= y2; i ++ ) res += sumcol[x2][i] - sumcol[x1][i];
                cout << res << endl;
        }
}
```
