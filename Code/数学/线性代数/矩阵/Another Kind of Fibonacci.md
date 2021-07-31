# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=3306

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
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
const int mod = 1e4 + 7;
const int n = 4;
struct Matrix
{
    ll m[10][10];
    Matrix(int flag)
    {
        fir(i, 1, n)
            fir(j, 1, n)
                m[i][j] = flag * (i == j);
    }
    Matrix Mul(Matrix a, Matrix b)
    {
        Matrix ans(0);
        fir(i, 1, n)
            fir(j, 1, n)
                fir(k, 1, n)
                    ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
        return ans;
    }
    Matrix ksm(Matrix a, ll b)
    {
        Matrix ans(1);
        while (b)
        {
            if (b & 1)
                ans = Mul(ans, a);
            a = Mul(a, a);
            b >>= 1;
        }
        return ans;
    }
};

int main(){
    ll N, X, Y;
    ll a[5] = {0ll, 2ll, 1ll, 1ll, 1ll};
    while(scanf("%lld%lld%lld",&N,&X,&Y)==3){
        N++;
        if (N <= 2)
        {
            printf("%lld\n", N);
            continue;
        }
        Matrix cur(0);
        cur.m[1][1] = cur.m[4][2] = 1;
        cur.m[1][2] = cur.m[2][2] = X * X % mod;
        cur.m[1][3] = cur.m[2][3] = 2 * X * Y % mod;
        cur.m[1][4] = cur.m[2][4] = Y * Y % mod;
        cur.m[3][3] = Y % mod;
        cur.m[3][2] = X % mod;
        cur = cur.ksm(cur, N-2);
        ll res = 0;
        for (int i = 1; i <= 4; i++)
            res = (res + cur.m[1][i] * a[i] % mod) % mod;
        printf("%lld\n", res);
    }
    return 0;
}
```
