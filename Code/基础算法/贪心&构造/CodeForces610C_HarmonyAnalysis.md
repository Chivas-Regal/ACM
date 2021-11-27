# 🔗
<a href="https://codeforces.com/problemset/problem/610/C"><img src="https://i.loli.net/2021/09/09/5bs9eFzcH6RDMtj.png"></a>

# 💡
化简一下，给个n，构造边长为2^n的方阵，其中行两两之间有一半的数不同  
那么对于n-1的时候，我们每一行也有一半的不同，可以利用上一步的每一行横向复制一下（"10"->"1010"）  
那么还少一半，我们设当前对第i行复制，那么发现"第i行"加上"它自己的反"可以和自己复制产生一半的不同（因为后一半都不相同）  
我们将这两种复制方式设为构造1和构造2  
  
接下来检验正确性  
其中第i行的构造1和构造2形成的行明显成立  
对于第i+1行的构造2和第i行的构造1来看，第i行和第i-1行的不同数量设为x，长度设为sz  
第i行的反和第i-1行的不同数量为sz-x  
因为x是sz的一半（前面一个矩阵一定成立），那么sz-x=x   
因为第i行的构造1和第i-1行的构造1由于复制的缘故使得相似度乘2依旧满足  
则第i行的构造1和第i-1行的构造2依旧满足  
  
则得到一种递推方式：  
对于当前边长为2^i的方阵设为 {{a,b}{c,d}}  
我们下一步可以推出 {{a,b,a,b},{a,b,-a,-b},{c,d,c,d},{c,d,-c,-d}}  
这样对每一行进行一次构造1和构造2推出下一次的方阵  
从2^0开始递推构造  

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

const int N = 1000;
string s1[N], s2[N]; // 轮流构造，滚动数组

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        int n; cin >> n;
        s1[0] = "1";
        if ( n == 0 ) {
                cout << "+" << endl;
                return 0;
        }
        for ( int k = 1; k <= n; k ++ ) {
                if ( k & 1 ) {
                        int cnt = 0;
                        for ( int i = 0; i < (1 << (k - 1)); i ++ ) {
                                string cur1 = s1[i] + s1[i];
                                string cur2 = s1[i];
                                for ( int j = 0; j < s1[i].size(); j ++ ) cur2 += (!(s1[i][j] - '0')) + '0';
                                s2[cnt++] = cur1, s2[cnt++] = cur2;
                        }
                } else {
                        int cnt = 0;
                        for ( int i = 0; i < (1 << (k - 1)); i ++ ) {
                                string cur1 = s2[i] + s2[i];
                                string cur2 = s2[i];
                                for ( int j = 0; j < s2[i].size(); j ++ ) cur2 += (!(s2[i][j] - '0')) + '0';
                                s1[cnt++] = cur1, s1[cnt++] = cur2;
                        }
                }
        }
        if ( n & 1 ) {
                for ( int i = 0; i < (1 << n); i ++ ) {
                        for ( int j = 0; j < s2[i].size(); j ++ ) {
                                if ( s2[i][j] == '0' ) cout << '*';
                                else cout << '+';
                        }cout << endl;
                }
        } else {
                for ( int i = 0; i < (1 << n); i ++ ) {
                        for ( int j = 0; j < s1[i].size(); j ++ ) {
                                if ( s1[i][j] == '0' ) cout << '*';
                                else cout << '+';
                        }cout << endl;
                }
        }
}
```
