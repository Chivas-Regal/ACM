# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1757

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#include                                            <algorithm>
#include                                             <iostream>
#include                                              <cstring>
#include                                               <string>
#include                                               <vector>
#include                                               <cstdio>
#include                                                <stack>
#include                                                <queue>
#include                                                <cmath>
#include                                                  <map>
#include                                                  <set>
#define G                                                  10.0
#define LNF                                                1e18
#define eps                                                1e-6
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

const int maxn = 15;

ll n, k, mod;
struct Mat{
    ll m[maxn][maxn];
    Mat(ll flag){//构造函数
        fir(i, 1, n) 
            fir(j, 1, n) 
                m[i][j] = flag * (i == j);
    }
    Mat Mul(Mat a,Mat b){//矩阵乘
        Mat ans(0);
        fir(i, 1, n)
            fir(j, 1, n)
                fir(k, 1, n)
                    ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
        return ans;
    }
    Mat ksm(Mat a,ll b){//快速幂
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
    while (scanf("%lld%lld", &k, &mod) == 2){
        Mat cur(0);
        n = 10;
        fir(i, 1, n) scanf("%lld", &cur.m[1][i]);
        fir(i, 2, n)
            fir(j, 1, n)
                cur.m[i][j] = 1 * (i - 1 == j);
        if(k<10){
            printf("%lld\n", k % mod);
            continue;
        }
        cur = cur.ksm(cur, k-9);
        ll ans = 0;
        fir(i, 1, n) ans = (ans + cur.m[1][i] * (10 - i) % mod) % mod;
        printf("%lld\n", ans);
    }
    //SP;
}
```
