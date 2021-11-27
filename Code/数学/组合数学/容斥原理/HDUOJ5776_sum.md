# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=5776

# 💡


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
#define each(cass) for (cin>>cass; cass; cass--)
#define test(a) cout << "---------" << a << "---------" << '\n'
 
using namespace std;
#pragma endregion

//全局变量
#pragma region
string fro[100005];
string enn[100005];
int n, m;
vector<int> a;
map<int, int> vis;
int sum;
int cass;
#pragma endregion

inline void solve(){
    a.clear();
    vis.clear();
    sum = 0;
    cin >> n >> m;
    for(int i = 0, x; i < n; i ++){
        cin >> x;
        a.push_back(x);
    }
    for(int i = 0; i < n; i ++){
        sum = (sum + a[i]) % m;
        if(sum == 0){
            cout << "YES" << endl;
            return;
        }
        if(vis[sum]){
            cout << "YES" << endl;
            return;
        }
        vis[sum] = 1;
    }
    cout << "NO" << endl;
}

Chivas{
    each(cass){
        solve();
    }
    Regal;
}
```
