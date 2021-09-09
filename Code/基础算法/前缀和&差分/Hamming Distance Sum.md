# 🔗
<a href="https://codeforces.com/problemset/problem/608/B"><img src="https://img-blog.csdnimg.cn/1ad09f3dcdae48929edc16088cf4ac6d.png"></a>

# 💡
求一位一位匹配下的不相似度和  
那么考虑一下可以计算一下a串每个位置的元素对这个匹配度的贡献值  
锁定一下这个位置都能和b串的哪个区间的字符匹配  
计算可得是[i,b.size()-a.size()+i]的区间匹配  
  
如果当前a[i]是'1'，那么我们统计一下这个区间内的'0'的个数  
如果当前a[i]是'0'，那么我们统计一下这个区间内的'1'的个数  
  
预处理一下前缀和，然后对于枚举每个b[i]求一下对应的区间和累加即可  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#define ll long long

using namespace std;

const int N = 2e5 + 10;
ll sum[2][N], res;
// sum[i][j]表示j以前i出现的个数

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        string a, b; cin >> a >> b;
        a = "0" + a,   b = "0" + b;

        for ( int i = 1; i < b.size(); i ++ ) 
                sum[1][i] = sum[1][i - 1] + (b[i] == '1'),
                sum[0][i] = sum[0][i - 1] + (b[i] == '0');

        for ( int i = 1; i <= a.size(); i ++ ) {
                if ( a[i] == '1' ) res = res + sum[0][b.size() - a.size() + i] - sum[0][i - 1];
                else               res = res + sum[1][b.size() - a.size() + i] - sum[1][i - 1];
        }
        cout << res << endl;
        return 0;
}
```
