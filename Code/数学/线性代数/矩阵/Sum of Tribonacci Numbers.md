# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2793

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

const int maxn = 100;
const int mod = 1e9 + 7;
const int n = 4;
struct Matrix
{
    ll m[maxn][maxn];
    Matrix(int flag)
    {
        fir(i, 1, n)
        {
            fir(j, 1, n)
            {
                m[i][j] = flag * (i == j);
            }
        }
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
int main()
{
    ll fibo[5] = {0, 3, 1, 1, 1};
    ll l, r;
    while (scanf("%lld%lld", &l, &r) == 2)
    {
        //我从1开始算的，题目是从0开始的，所以位数++，但区间和应包含l，所以l--
        l++;
        r++;
        l--;
        //
        ll ans_l = 0;
        ll ans_r = 0;
        if (l <= 3)
            ans_l = l;
        else
        {
            Matrix cur_l(0);
            cur_l.m[1][1] = cur_l.m[1][2] = cur_l.m[1][3] = cur_l.m[1][4] = cur_l.m[2][2] = cur_l.m[2][3] = cur_l.m[2][4] = cur_l.m[3][2] = cur_l.m[4][3] = 1;
            cur_l = cur_l.ksm(cur_l, l - 3);
            fir(i, 1, 4)
            {
                ans_l = (ans_l + cur_l.m[1][i] * fibo[i] % mod) % mod;
            }
        }
        if (r <= 3)
            ans_r = r;
        else
        {
            Matrix cur_r(0);
            cur_r.m[1][1] = cur_r.m[1][2] = cur_r.m[1][3] = cur_r.m[1][4] = cur_r.m[2][2] = cur_r.m[2][3] = cur_r.m[2][4] = cur_r.m[3][2] = cur_r.m[4][3] = 1;
            cur_r = cur_r.ksm(cur_r, r - 3);
            fir(i, 1, 4)
            {
                ans_r = (ans_r + cur_r.m[1][i] * fibo[i] % mod) % mod;
            }
        }
        cout << (ans_r - ans_l + mod) % mod << endl;
    }
    return 0;
}
```
