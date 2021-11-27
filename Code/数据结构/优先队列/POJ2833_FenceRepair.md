# 🔗
http://poj.org/problem?id=2833

# 💡
分析样例说明中的构造方式  
每次选取最小的两个（证明方式可以联想到三角形定理）  
每次选取其中最小的两个拼一起再压入堆内  
如果堆长度=1就break  
  
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#pragma region
#pragma GCC optimize(3,"Ofast","inline")
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#define G 10.0
#define LNF 1e18
#define eps 1e-6
#define PI acos(-1.0)
#define ll long long
#define INF 0x7FFFFFFF
#define Regal exit(0)
#define Chivas int main()
#define pb(x) push_back(x)
#define SP system("pause")
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define IOS ios::sync_with_stdio(false)
#define mm(a, b) memset(a, b, sizeof(a))
#define each_cass(cass) for (cin>>cass; cass; cass--)
#define test(a) cout << "---------" << a << "---------" << '\n'
 
using namespace std;
#pragma endregion

//全局变量
#pragma region
int n; 
priority_queue<int, vector<int>, greater<int> > pque;
#pragma endregion


Chivas{
    IOS;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        pque.push(x);
    }

    ll res = 0;
    while(pque.size() > 1){
        int fir = pque.top(); pque.pop();
        int sec = pque.top(); pque.pop();

        pque.push(fir + sec);
        res += fir + sec;
    }

    cout << res << endl;

    Regal;
}
```
