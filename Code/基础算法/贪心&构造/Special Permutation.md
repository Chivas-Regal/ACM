# 🔗
https://codeforces.com/problemset/problem/1454/A

# 💡
签到手速题  
每一个数往后错一位就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

using namespace std;

inline void Solve () {
        int n; cin >> n;
        for ( int i = 0; i < n; i ++ ) cout << (i + 1) % n + 1 << " ";
        puts("");
}

int main () {
        int cass;
        for ( cin >> cass; cass; cass -- ) Solve();
}
```
