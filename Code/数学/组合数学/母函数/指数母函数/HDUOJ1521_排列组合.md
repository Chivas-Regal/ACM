# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1521

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

const int maxn = 15;
double c1[maxn], c2[maxn];
ll num[maxn];
ll F[maxn];
ll n, m;

void Factorial(){
    F[0] = 1;
    for (int i = 1; i < maxn; i++)
        F[i] = F[i - 1] * i;
}

void init(){
    mm(c1, 0);
    mm(c2, 0);
    for (int i = 0; i <= num[1]; i++)
        c1[i] = 1.0 / F[i];
}

Chivas{
    Factorial();
    while (scanf("%lld%lld", &n, &m) == 2){
        for (int i = 1; i <= n; i++)
            scanf("%lld", &num[i]);
        init();
        for (int i = 2; i <= n; i++){
            for (int j = 0; j <= m; j++){
                for (int k = 0; k + j <= m && k <= num[i]; k++)
                    c2[j + k] += c1[j] / F[k];
            }
            for (int j = 0; j <= m; j++)
                c1[j] = c2[j], c2[j] = 0;
        }
        printf("%.0f\n", c1[m] * F[m]);
    }
    Regal;
}
```
