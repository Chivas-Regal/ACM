# 🔗
<a href="https://codeforces.com/problemset/problem/612/D"><img src="https://i.loli.net/2021/09/09/jmbocQT6YXziOwB.png"></a>

# 💡
这道题可以看作一个个[l,r]铺布，看最好多少  
能很快想到可以用数组去模拟高度  
范围这么大就告辞  
那么就可以使用差分数组的思想：只改两个点打到区间修改的目的  
由于全放在一个完整图的数组里面我们遍历的时候不好遍历，所以数组内只放置l和r的位置  
  
对l和r都存在的数组进行升序排序，并设一个记录高度的值
对于一个l，如果在这个位置+1之后是k，说明是一个满足题意的区间的开始，塞入答案  
对于一个r，如果在这个位置-1之前是k，说明是一个满足题意的区间的结束，塞入答案  
但要考虑两相邻区间贴着的情况，也就是同一个点存在一个l也存在一个r，那么此时我们可以先去使用l进行高度+1再用r进行高度-1，这样就安全了  
  
输出的时候一次输出两个就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <cstring>
#include <list>
using namespace std;
#define ll long long
const ll mod = 998244353;
const double PI = acos(-1.0);
const double eps = 1e-9;

int main () {
        ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        int k, n; cin >> n >> k;
        vector<pair<int, int> > vec;
        for ( int i = 0; i < n; i ++ ) {
                int x, y; cin >> x >> y;
                vec.push_back({x, 1});
                vec.push_back({y, -1});
        }
        sort ( vec.begin(), vec.end(), [] ( pair<int, int> a, pair<int, int> b) {
                if ( a.first != b.first ) return a.first < b.first;
                return a.second > b.second;
        });

        vector<int> res;
        int lvl = 0; // 高度
        for ( int i = 0; i < vec.size(); i ++ ) {
                if ( vec[i].second == 1 ) {
                        lvl ++;
                        if ( lvl == k ) res.push_back(vec[i].first);
                } else {
                        if ( lvl == k ) res.push_back(vec[i].first);
                        lvl --;
                }
        }
        cout << res.size() / 2 << endl;
        for ( int i = 0; i < res.size(); i += 2 ) {
                cout << res[i] << " " << res[i + 1] << endl;
        }
}
```
