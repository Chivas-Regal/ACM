# 🔗
<a href="https://codeforces.com/contest/1593/problem/D2"><img src="https://i.loli.net/2021/10/14/TKNPUoI84dOLbG7.png"></a>

# 💡
这道题是让一半的数一样  
那么就在差值上做文章  
  
首先还是个特判，如果已经有一半以上都是一样的话那么就是-1  
然后枚举基点是谁  
对基点以后的数求一下他们与基点的差值  
0特殊记录一下因为这代表与基点相同的点，并塞到一个计数变量cnt内  
  
对每个差值统计一下因数k，因为每个因数都可以让这个差值变成0  
枚举的过程中，如果出现一个因数出现的个数+cnt超过一半了，那么就维护一下答案的最大值  
但要记得也去统计另一个因数dir/k并且满足条件了话就维护  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 300;
int a[N], dir[N];
map<int, int> mp;

inline void Solve() {
        mp.clear();
        int n; cin >> n;
        for ( int i = 0; i < n; i ++ ) cin >> a[i], mp[a[i]] ++;
        for ( int i = 0; i < n; i ++ ) if ( mp[a[i]] >= n / 2 ) { cout << "-1" << endl; return; }
        sort ( a, a + n );
        
        int res = -1;

        for ( int i = 0; i < n / 2 + 1; i ++ ) {
                int samecnt = 0; mp.clear();
                for ( int j = i; j < n; j ++ ) {
                        samecnt += a[j] == a[i];
                        dir[j] = a[j] - a[i];
                }
                for ( int j = i; j < n; j ++ ) {
                        if ( dir[j] == 0 ) continue;
                        for ( int k = 1; k * k <= dir[j]; k ++ ) {
                                if ( dir[j] % k == 0 ) {
                                        mp[k] ++;
                                        if ( mp[k] + samecnt >= n / 2 ) res = max ( res, k );
                                        if ( k * k != dir[j] ) {
                                                mp[dir[j] / k] ++;
                                                if ( mp[dir[j] / k] + samecnt >= n / 2 ) res = max ( res, dir[j] / k );
                                        } 
                                }
                        }
                }
        }        
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
