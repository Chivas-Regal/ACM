# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1398

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
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
#define ll long long
#define INF 0x7FFFFFFF
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define SP system("pause")
#define mm(a, b) memset(a, b, sizeof(a))
#define each_cass(cass) for (cin >> cass; cass; cass--)

using namespace std;

const ll maxn = 1000;
ll c1[maxn];
ll c2[maxn];
ll a[1000];

void init(){
    for (ll i = 0; i < maxn; i++)
        c1[i] = 1, c2[i] = 0;
    for (ll i = 0; i < 1000; i++)
        a[i] = i * i;
}

int main(){
    ll n;
    while(scanf("%d",&n)==1,n){
        init();
        for (ll i = 2; i <= n; i++){
            for (ll j = 0; j <= n; j++)
                for (ll k = 0; k + j <= n; k += a[i])
                    c2[k + j] += c1[j];
            for (ll j = 0; j <= n; j++)
                c1[j] = c2[j], c2[j] = 0;
        }
        printf("%d\n", c1[n]);
    }
    return 0;
}

```
