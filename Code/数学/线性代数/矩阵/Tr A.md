# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1575

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#include                                                  <map>
#include                                                  <set>
#include                                                <stack>
#include                                                <queue>
#include                                                <cmath>
#include                                               <string>
#include                                               <vector>
#include                                               <cstdio>
#include                                              <cstring>
#include                                             <iostream>
#include                                            <algorithm>
#define G                                                  10.0
#define LNF                                                1e18
#define eps                                                1e-6
#define mod                                             1e9 + 7
#define ll                                            long long
#define INF                                          0x7FFFFFFF
#define PI                                           acos(-1.0)
#define pb(x)                                      push_back(x)
#define SP                                      system("pause")
#define mm(a, b)                        memset(a, b, sizeof(a))
#define fir(i, a, n)                for (ll i = a; i <= n; i++)
#define rif(i, a, n)                for (ll i = a; i >= n; i--)
#define each_cass(cass)  for (scanf("%d", &cass); cass; cass--)

using namespace std;

const int maxn = 100;
int n, k;
struct Mat{
    ll m[maxn][maxn];
    Mat(int flag){
        fir(i, 1, n)
            fir(j, 1, n)
                m[i][j] = flag * (i == j);
    }
    Mat Mul(Mat a,Mat b){
        Mat ans(0);
        fir(i, 1, n)
            fir(j, 1, n)
                fir(k, 1, n)
                    ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j])%9973;
        return ans;
    }
    Mat ksm(Mat a,ll b){
        Mat ans(1);
        while(b){
            if(b&1)
                ans = Mul(ans, a);
            a = Mul(a, a);
            b >>= 1;
        }
        return ans;
    }
};
int main(){
    int cass;
    each_cass(cass){
        Mat cur(0);
        scanf("%d%d", &n, &k);
        fir(i, 1, n)
            fir(j, 1, n)
                scanf("%lld", &cur.m[i][j]);
        cur = cur.ksm(cur, k);
        ll res = 0;
        fir(i, 1, n) res = (res + cur.m[i][i]) % 9973;
        printf("%lld\n", res);
    }
    return 0;
}
```
