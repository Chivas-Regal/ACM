# 🔗
http://poj.org/problem?id=2833

# 💡
两个堆分别存最大的n1个数和最小的n2个数  
计算非这俩堆内的元素和  

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
int n, n1, n2; 
priority_queue<int, vector<int>, greater<int> > pque1;
priority_queue<int> pque2;
#pragma endregion

Chivas{
    IOS;
    while(scanf("%d%d%d", &n1, &n2, &n) == 3){

        if((!n) && (!n1) && (!n2)) break;
        
        ll res = 0;
        ll cnt_res = n - n1 - n2;

        for(int i = 0; i < n; i ++){
            int x; scanf("%d", &x); res += x;
            pque1.push(x); pque2.push(x);
            if(pque1.size() > n1) pque1.pop();
            if(pque2.size() > n2) pque2.pop();
        }

        while(pque1.size()) res -= pque1.top(), pque1.pop();
        while(pque2.size()) res -= pque2.top(), pque2.pop();

        printf("%.6f\n", res * 1.0 / cnt_res);
    }
    Regal;
}
```
