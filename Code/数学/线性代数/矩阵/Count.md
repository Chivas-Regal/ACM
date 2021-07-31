# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=6470

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
const int mod = 123456789;
ll n;
struct Mat{
    ll m[maxn][maxn];
    Mat(int flag){
        fir(i, 1, 6)
            fir(j, 1, 6)
                m[i][j] = flag * (i == j);
    }
    Mat Mul(Mat a,Mat b){
        Mat ans(0);
        fir(i, 1, 6)
            fir(j, 1, 6)
                fir(k, 1, 6)
                    ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j])%mod;
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
    ll a[10];
    a[1] = 2, a[2] = 1, a[3] = 8, a[4] = 4, a[5] = 2, a[6] = 1;
    each_cass(cass){
        scanf("%lld", &n);
        if(n<3){
            printf("%lld\n", n);
            continue;
        }
        Mat cur(0);
        cur.m[1][1] = 1;
        cur.m[1][2] = 2;
        cur.m[1][3] = 1;
        cur.m[1][4] = 3;
        cur.m[1][5] = 3;
        cur.m[1][6] = 1;
        cur.m[2][1] = 1;
        cur.m[3][3] = 1;
        cur.m[3][4] = 3;
        cur.m[3][5] = 3;
        cur.m[3][6] = 1;
        cur.m[4][4] = 1;
        cur.m[4][5] = 2;
        cur.m[4][6] = 1;
        cur.m[5][5] = 1;
        cur.m[5][6] = 1;
        cur.m[6][6] = 1;
        cur = cur.ksm(cur, n - 2);
        ll ans = 0;
        
        for (int i = 1; i <= 6; i++)
            ans = (ans + a[i] * cur.m[1][i] % mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```
