# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1085

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
#define fir(i, a, n) for (ll i = a; i <= n; i++)
#define rif(i, a, n) for (ll i = a; i >= n; i--)
#define each_cass(cass) for (scanf("%d", &cass); cass; cass--)

using namespace std;

const int maxn = 100010;
int kind[4] = {0, 1, 2, 5};
int c1[maxn];
int c2[maxn];
int num[4];
int sum;

void init(){
    mm(c1, 0);
    mm(c2, 0);
    for (int i = 0; i <= sum; i++)
        c1[i] = 1, c2[i] = 0;
}

int main(){
    while (scanf("%d%d%d", &num[1], &num[2], &num[3]) == 3, num[1] || num[2] || num[3]){
        sum = num[1];
        init();
        for (int i = 2; i <= 3; i++){
            for (int j = 0; j <= sum; j++)
                for (int k = 0; k <= num[i] * kind[i]; k += kind[i])
                    c2[j + k] += c1[j];
            sum += num[i] * kind[i];
            for (int j = 0; j <= sum; j++)
                c1[j] = c2[j], c2[j] = 0;
        }
        for (int i = 0; i <= sum + 1; i++){
            if(!c1[i]){
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}

```
