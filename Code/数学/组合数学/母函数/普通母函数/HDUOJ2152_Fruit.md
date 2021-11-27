# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2152

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
#define Chivas int main()
#define Regal return 0
#define PI acos(-1.0)
#define pb(x) push_back(x)
#define SP system("pause")
#define mm(a, b) memset(a, b, sizeof(a))
#define fir(i, a, n) for (ll i = a; i <= n; i++)
#define rif(i, a, n) for (ll i = a; i >= n; i--)
#define each_cass(cass) for (scanf("%d", &cass); cass; cass--)

using namespace std;

const ll maxn = 1e4 + 10;
ll n, m;
struct fruit{
    ll a;
    ll b;
    void read(){
        scanf("%lld%lld", &a, &b);
    }
} f[110];
ll c1[maxn];
ll c2[maxn];

void init(){
    mm(c1, 0);
    mm(c2, 0);
    for (ll i = f[1].a; i <= f[1].b; i++)
        c1[i] = 1;
}

Chivas{
    while (scanf("%lld%lld", &n, &m) == 2){
        for (ll i = 1; i <= n; i++)
            f[i].read();
        init();
        for (ll i = 2; i <= n; i++){
            for (ll j = 0; j <= m; j++){
                for (ll k = f[i].a; k + j <= m && k <= f[i].b; k++)
                    c2[j + k] += c1[j];
            }
            for (ll j = 0; j <= m; j++)
                c1[j] = c2[j], c2[j] = 0;
        }
        printf("%lld\n", c1[m]);
    }
    Regal;
}

```
