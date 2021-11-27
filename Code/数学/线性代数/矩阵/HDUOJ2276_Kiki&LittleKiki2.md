# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2276


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

ll len, n;
const ll mod = 2;
struct Matrix
{
    ll m[110][110];
    Matrix(int flag)
    {
        fir(i, 1, len)
            fir(j, 1, len)
                m[i][j] = flag * (i == j);
    }
    Matrix Mul(Matrix a, Matrix b)
    {
        Matrix ans(0);
        fir(i, 1, len)
            fir(j, 1, len)
                fir(k, 1, len)
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
    while (scanf("%lld", &n) == 1)
    {
        string s;
        getchar();
        cin >> s;
        len = s.size();
        Matrix cur(0);
        for (int i = 1; i <= len; i++)
        {
            cur.m[i][i] = 1;
            if (i > 1)
                cur.m[i][i - 1] = 1;
            else
                cur.m[i][len] = 1;
        }
        cur = cur.ksm(cur, n);
        ll a[len + 10];
        for (int i = 0; i < len; i++)
        {
            a[i + 1] = s[i] - '0';
        }
        ll ans[105] = {0};
        fir(i, 1, len)
            fir(j, 1, len) 
                ans[i] = (ans[i] + cur.m[i][j] * a[j]) % mod;//最后一个矩阵的每一行都要求出来
        fir(i, 1, len) printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}
/*
构建(len*len)的矩阵：
1 0 0 0 0 0 1
1 1 0 0 0 0 0
0 1 1 0 0 0 0
0 0 1 1 0 0 0
0 0 0 1 1 0 0
0 0 0 0 1 1 0
0 0 0 0 0 1 1
*/
```
