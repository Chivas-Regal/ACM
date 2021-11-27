# 🔗
https://codeforces.com/contest/1511/problem/D

# 💡
问题化简一下：我们要构造出来一个字符串，使得每两个连着的字符形成的长度为2的字符串出现的次数尽量少  
那我们就aa,ab,ac,ad,ae...,bb,bc,bd,be,...,......  
由于aaa三个同放在开头会直接形成两个同样的长度为2的字符串，那么这里我们删去其中一个a即可  
所以构造方式为：  
第一个字符x在第一对里面只出现一次，在接下来的对里匹配x+1直到'a'+k-1  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

using namespace std;

int main () {

        int n, k; cin >> n >> k;

        while ( 1 ) {
                for ( char i = 'a'; i < 'a' + k; i ++ ) {

                        cout << i,  n --; 
                        if ( !n ) return 0;

                        for ( char j = i + 1; j < 'a' + k; j ++ ) {

                                cout << i, n --;
                                if ( !n ) return 0;

                                cout << j, n --;
                                if ( !n ) return 0;

                        }
                }
        }
        return 0;
}



```
