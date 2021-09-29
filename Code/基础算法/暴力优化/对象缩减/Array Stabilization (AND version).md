# 🔗
<a href="https://codeforces.com/contest/1579/problem/F"><img src="https://i.loli.net/2021/09/29/NnoeacT3WZUPmtb.png"></a>

# 💡
首先应该很明显看到的是，每一个1在遇到0后都会变成0  
即一次次滚动，每滚动一次，都有一些1变成0进行下一次滚动  
  
可以想到会有很多0具有一样的作用，所以没必要全部都算，考虑对象缩减  
同层内0碰到0不用管，因为后面那个0足够有代表性：它都碰不到1，前面的那个也没必要继续走它的路；它能碰到的1也已经开始进入下一次滚动了  
之前的0也不用管了，因为它们已经尽力了，每次只考虑他们中新晋的0  
  
那么问题就成为了：  
每次将上一次得到的新0进行滚动  
每产生一个新0，就加入下一次滚动的数组内  
下一次就利用这些新0进行滚动  
  
如果最后没有新得到的0了就开始遍历，如果存在“漏网之1”，那么就输出-1    
否则就输出滚动次数-1（最后一轮没有对碰，所以不算  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdio>
#include <queue>
#include <set>
#define ll long long
#define INF 0x3f3f3f3f

using namespace std;

inline void Solve () {
        int n, k; scanf("%d%d", &n, &k); int a[n];
        vector<int> vec;
        for ( int i = 0; i < n; i ++ ) {
                scanf("%d", &a[i]);
                if ( !a[i] ) vec.push_back(i);
        }
        int res = 0;
        while ( vec.size() ) {
                vector<int> cur;
                for ( auto i : vec ) {
                        int nxt = (i + k) % n;
                        if ( a[nxt] ) a[nxt] = 0, cur.push_back(nxt); // 新变成的0
                }       
                vec.clear(); for ( auto i : cur ) vec.push_back(i); // 新晋的0塞入数组
                res ++;
        }
        for ( int i = 0; i < n; i ++ ) if ( a[i] ) { printf("-1\n"); return; }
        printf("%d\n", res - 1 ); // 最后一轮是没有对碰的，所以最后一轮不算
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif 
        int cass;
        for ( scanf("%d", &cass); cass; cass -- ) {
                Solve();
        }
        return 0;
}
```
