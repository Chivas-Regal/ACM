# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7020"><img src="https://img-blog.csdnimg.cn/f79012f522be4ae3beaac838fe1de587.png"></a>

# 💡
与[LuoguP4062 Yazid 的新生舞会](https://www.luogu.com.cn/problem/P4062)一样，是求含有绝对众数的区间个数，但是数据量是1e6所以最多只能有一个log，但是如果一个
log就很难做到很多分治类做法  
  
对于一个数x，对于第i个位置，如果当前位置是x那么就可以设置为1，否则是-1  
那么对这个值求一下前缀和sum，如果对于一个位置sum[i]-sum[j]>0，说明这段区间内这个数出现个数比别的所有数出现个数要多  
那么问题就转化为，对于每个数x，建立完sum数组之后，求每一个位置前面sum[j] < sum[i]的个数  
  
可以维护一个f1数组用来维护每一个sum的个数，f2数组是用来对f1进行区间修改的差分数组  
在当前这一段一直出现x或者未到最小值，可以直接线性求解，SUM不断累加sum[个数]    
如果到了最小值并且还是没有出现x，意味着一直下减，前面一定不会出现解  
那么就可以跳过这一段，里面的要改的数可以通过区间修改一起改了，同时SUM重置为0  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#define ll long long
using namespace std;


const int N = 2e6 + 10;

map<int, vector<int> > g;

int n, cass, a[N]; 
ll res = 0;

inline void Solve ( int x ) {
        g[x].push_back(n + 1);
        unordered_map<ll, ll> f1, f2;
        f1[0] = 1; ll sum = 0/*前面多少个比当前前缀和小的*/, tmp = 0/*当前前缀和*/, minn = 0/*前面出现过的最小前缀和*/;
        for ( int i = 1, j = 0; i <= n; i ++ ) {
                if ( i > g[x][j] ) j ++; // 保持g[x][j]一直 >= i
                if ( a[i] == x ) {
                        tmp ++; 
                        f1[tmp] += f2[tmp] + 1; // 利用差分的f2让f1往前走一步
                        f2[tmp + 1] += f2[tmp]; f2[tmp] = 0;
                        sum += f1[tmp - 1]; // 又多了一个比tmp小的
                        res += sum;
                } else if ( tmp - 1 <= minn ) { // 这个区间跳过
                        int len = g[x][j] - i; // 跳过区间的每个sum的个数 ++
                        ++ f2[tmp - len + 1]; -- f2[tmp]; // 区间修改
                        ++ f1[tmp - len];
                        tmp -= len;
                        i = g[x][j] - 1;
                        sum = 0; // 最小的，前面没有更小的了，所以sum清0
                } else {
                        sum -= f1[-- tmp]; // 就是光减而已，也没多什么，就利用已有的f1计算即可
                        res += sum;
                        ++ f1[tmp];
                }
                if ( tmp < minn ) minn = tmp; // 最小值维护一下
        }
}

int main () {
        ios::sync_with_stdio(false);
        for ( cin >> cass; cass; cass -- ) {
                cin >> n;
                for ( int i = 1; i <= n; i ++ ) {
                        cin >> a[i];
                        g[a[i]].push_back(i); // 对每个存一下位置
                }
                res = 0;
                for ( auto v : g ) { // 分开解决
                        Solve(v.first);
                        g[v.first].clear(); // 在求完就可以删掉了
                }
                cout << res << endl;
        }
}

```
