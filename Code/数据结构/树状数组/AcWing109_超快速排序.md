# 🔗
https://www.acwing.com/problem/content/109/

# 💡
对数据进行离散化操作，然后求逆序对即可  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
/*
非最佳离散化写法，未完善
*/


#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#define rep1(i, a, n) for (int i = a; i <= n; i++)
#define rep2(i, a, n) for (int i = a; i >= n; i--)
#define mm(a, b) memset(a, b, sizeof(a))
#define elif else if
typedef long long ll;
void mc(int *aa, int *a, int len) { rep1(i, 1, len) * (aa + i) = *(a + i); }
const int INF = 0x7FFFFFFF;
const double G = 10;
const double eps = 1e-6;
const double PI = acos(-1.0);
const int mod = 1e9 + 7;
using namespace std;

int N;
int a[510000];
int flag[510000];
int C[510000];
int num[510000];

int lowbit(int x)
{
    return x & (-x);
}

int make_c(int x)
{
    int res = 0;
    int down_x = x + 1 - lowbit(x);
    rep2(i,x,down_x)
    {
        res += a[i];
    }
    return res;
}

int sum(int x)
{
    int res = 0;
    while(x>0)
        res += C[x], x -= lowbit(x);
    return res;
}

void update(int x,int val)
{
    while(x<=N)
        C[x] += val, x += lowbit(x);
}

int main()
{
    while(scanf("%d",&N)==1,N)
    {
        mm(C, 0);
        mm(a, 0);
        ll cnt = 0;
        rep1(i, 1, N) scanf("%d", &flag[i]), num[i] = flag[i];
        sort(num + 1, num + N + 1);
        rep1(i, 1, N)
        {
            flag[i] = lower_bound(num + 1, num + N + 1, flag[i]) - (num + 1) + 1;
            a[flag[i]] = 1;
            update(flag[i], 1);//a[flag[i]] + 1
            cnt += sum(N) - sum(flag[i]);
        }
        printf("%lld\n", cnt);
    }
}
```
