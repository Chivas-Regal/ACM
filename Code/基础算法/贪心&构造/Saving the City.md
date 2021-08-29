# 🔗
<a href="https://codeforces.com/contest/1443/problem/B"><img src="https://i.loli.net/2021/08/29/z5yBLOSX9EefWMq.png"></a>

# 💡
一个贪心问题  
如果两个连通'1'之间的'0'的个数*b<=a，那么完全可以连通掉然后一起点燃  
否则不可以  
那么就是一个模拟题了  
我们计算两个连通1之间的'0'个数，如果<=a/b的话，就全更新为'1'  
最后再点燃操作  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#define ll long long
using namespace std;

inline void Solve () {
        int a, b; cin >> a >> b;
        string s; cin >> s;

        int res = 0;

        // 连通
        int canSwp = a / b;
        int stt = 0; while ( s[stt] == '0' ) stt ++;
        for ( int i = stt; i < s.size() - 1; i ++ ) 
                if ( s[i + 1] == '1' && s[i] == '0' ) {
                        int ii = i, cnt = 0;
                        while ( s[ii] == '0' )  
                                cnt ++, 
                                ii --;
                        if ( cnt <= canSwp ) 
                                res += cnt * b,
                                fill(s.begin() + ii + 1, s.begin() + i + 1, '1');
                }

        // 点燃
        res += (s[0] == '1') * a;
        for ( int i = 1; i < s.size(); i ++ ) 
                res += (s[i] == '1' && s[i - 1] != '1' ) * a;
        cout << res << endl;
}

int main () {
        int cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}

```
