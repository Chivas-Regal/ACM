# 🔗
<a href="https://codeforces.com/contest/1627/problem/D"><img src="https://s2.loli.net/2022/01/18/GtWesXr3kMwVHCY.png"></a>

# 💡
可以简单的得到，其实就是每次选任意多任意的位置上的数，将它们的  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> 放进数组  
那么我们可以枚举这个  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> ，将数组中所有是它的倍数的数求一下  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> ，如果这些数的  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> 就是我们当前枚举的  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> 并且该  <img src="https://latex.codecogs.com/svg.image?\inline&space;gcd" title="\inline gcd" /> 没有在原数组内出现过，那么我们就可以加入  
  
枚举所有的倍数，埃氏筛就可以实现  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e6 + 1;
int vis[N];
 
inline int gcd ( int a, int b ) {
        return b ? gcd(b, a % b) : a;
}
 
int main () {
        ios::sync_with_stdio(false);
 
        int n; cin >> n;
        for ( int i = 0; i < n; i ++ ) {
                int x; cin >> x;
                vis[x] = 1;
        }
        int res = 0;
        for ( int i = 1; i < N; i ++ ) {
                if ( vis[i] ) continue;
                int g = 0;
                for ( int j = i; j < N; j += i ) {
                        if ( vis[j] ) g = gcd(g, j);
                }
                res += g == i;
        }
        cout << res << endl;
}
```
