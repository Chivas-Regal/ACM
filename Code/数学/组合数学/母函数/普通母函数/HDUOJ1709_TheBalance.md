# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1709

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

const int maxn = 100005;
int n;
int A[110];
int c1[maxn];
int c2[maxn];

void init(){
    mm(c1, 0);
    mm(c2, 0);
    c1[0] = c1[A[1]] = 1;
}

main(){
    while (scanf("%d", &n) == 1){
        int sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]), sum += A[i];
        init();
        for (int i = 2; i <= n; i++){
            for (int j = 0; j <= sum; j++){
                for (int k = 0; k + j <= sum && k <= A[i]; k += A[i])
                    c2[abs(k - j)] += c1[j], c2[k + j] += c1[j];
            }
            for (int j = 0; j <= sum; j++)
                c1[j] = c2[j], c2[j] = 0;
        }

        vector<int> ans;
        for (int i = 0; i <= sum; i++){
            if(!c1[i]){
                ans.push_back(i);
            }
        }
        printf("%lu\n", ans.size());
        for (int i = 0; i < ans.size(); i++)
            printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
        return 0;
}

```
