# 🔗
<a href="https://open.kattis.com/problems/letterwheels"><img src="https://i.loli.net/2021/08/20/jz6p7GT9JvOW4lm.png"></a>

# 💡
首先能想到的最暴力方式：  
固定s1串，然后枚举s2和s3的偏移量  
一个个枚举，看是不是成立，如果成立就维护一下最小值  
时间O(n^3)，妥妥的TLE  
  
那么在偏移量里面  
我们要枚举双重的，不如提前建立好一个字符串偏移一定的值是不是成立  
这样我们枚举一遍偏移量，然后再顺着字符串内部枚举一下在“这个偏移量之下，两个字符串之间能不能成立”  
然后我们在下面维护答案的时候  
枚举两个偏移量，自然就知道第三个偏移量了，就在这个基础上，如果三个字符串之间互相成立，就维护一下最小值  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <string>
#define INF 0x7FFFFFFF

using namespace std;
// 偏移： ->
const int N = 5e3 + 10;
int isSm[3][N]; // 0:对于1,2的偏移   1:对于2,3的偏移   2:对于1,3的偏移  =1:相同 =0:不同
int len, res = INF;
string s1, s2, s3;

int main () {

        cin >> s1 >> s2 >> s3; len = s1.size();
        
        for ( int i = 0; i < len; i ++ ) { // 偏移量
                for ( int j = 0; j < len; j ++ ) { // 一位一位枚举
                        if ( s1[j] == s2[(i + j) % len] ) isSm[0][i] = 1;
                        if ( s2[j] == s3[(i + j) % len] ) isSm[1][i] = 1;
                        if ( s1[j] == s3[(i + j) % len] ) isSm[2][i] = 1;
                }
        }

        for ( int i = 0; i < len; i ++ ) { // 2对于1的偏移量
                for ( int j = 0; j < len; j ++ ) { // 3对于1的偏移量
                        if ( /*1&3*/!isSm[2][j] &&
                             /*2&1*/!isSm[0][i] &&
                             /*3&2*/!isSm[1][( j - i + len) % len] ) {
                                res = min(res, max(i, j));
                                res = min(res, max(len - i, len - j));
                                res = min(res, min(i, len - i) + min(j, len - j));
                        }
                }
        }
        cout << (res == INF ? -1 : res) << endl;
}

```
