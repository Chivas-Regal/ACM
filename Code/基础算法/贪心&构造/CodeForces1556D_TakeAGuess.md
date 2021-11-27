# 🔗
<a href="https://codeforces.com/contest/1556/problem/D"><img src="https://i.loli.net/2021/08/30/h6sKcJRUbtDH9TZ.png"></a>

# 💡
本题我们可以把原数组构造出来，所以重在发现一个公式关系  
对于每一位，我们可以用或运算求出这一位是否存在1，同时加上与运算求出这一位有几个1  
则公式为：<img src="https://latex.codecogs.com/svg.image?a_{12}=a_1&plus;a_2=a_1|a_2&plus;a_1\&&space;a_2" title="a_{12}=a_1+a_2=a_1|a_2+a_1\& a_2" />  
同时可以推出一组方程组运算关系：<img src="https://latex.codecogs.com/svg.image?a_1=\frac&space;{a_{12}&plus;a_{13}-a{23}}{2}" title="a_1=\frac {a_{12}+a_{13}-a{23}}{2}" />  
然后直接：<img src="https://latex.codecogs.com/svg.image?a_{i&plus;1}=a_{i&plus;1}\&a_i&plus;a_{i&plus;1}|a_i-a_i" title="a_{i+1}=a_{i+1}\&a_i+a_{i+1}|a_i-a_i" />即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define ll long long

using namespace std;

int main () {
#ifndef ONLINE_JUDGE
        freopen("../in.in", "r", stdin);
        freopen("../out.out", "w", stdout);
#endif
        auto And = [&](int a, int b) { // 放出询问，返回给定值
            cout << "and " << a << " " << b << endl;
            int ord;
            cin >> ord;
            return ord;
        };
        auto Or = [&](int a, int b) { // 放出询问，返回给定值
            cout << "or " << a << " " << b << endl;
            int ord;
            cin >> ord;
            return ord;
        };

        int n, k;
        cin >> n >> k;
        int a12 = And(1, 2) + Or(1, 2),
            a13 = And(1, 3) + Or(1, 3),
            a23 = And(2, 3) + Or(2, 3);
        vector<int> vec;
        vec.push_back((a12 - a23 + a13) / 2); 
        vec.push_back((a12 + a23 - a13) / 2); 
        vec.push_back((a23 + a13 - a12) / 2); // 前三个先造好
        
        while ( vec.size() < n ) {
                int aa = And(vec.size(), vec.size() + 1) + Or(vec.size(), vec.size() + 1);
                vec.push_back(aa - vec.back());
        }
        sort ( vec.begin(), vec.end() );
        cout << "finish " << vec[k - 1] << endl;
        return 0;
}
```
