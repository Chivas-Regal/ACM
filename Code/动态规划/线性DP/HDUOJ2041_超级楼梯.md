# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2041

<details>
  <summary align="center">查看题解</summary>
           
# 💡
递推的思想  
每一个台阶都可以由前一个与前两个得来  
所以sum[i] = sum[i - 1] + sum[i - 2]  


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

#pragma endregion

//主体------------------------------------------

inline void solve(){
    ll n; cin >> n;
    vector<ll> vec;
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(1);
    for(int i = 3; i <= n ; i++) vec.push_back(vec.back() + vec[vec.size() - 2]);
    cout << vec[n] << endl;
}

Chivas{
    int cass;
    each_cass(cass){
        solve();
    }
    Regal;
}
```
