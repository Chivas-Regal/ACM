# 🔗
http://poj.org/problem?id=2352

# 💡
因为y升序  
所以我们不用管  
每行插入之后看前面有多少个已经插入的就行了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
#pragma region
#pragma GCC optimize(3,"Ofast","inline")
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
#define PI acos(-1.0)
#define ll long long
#define INF 0x7FFFFFFF
#define Regal exit(0)
#define Chivas int main()
#define pb(x) push_back(x)
#define SP system("pause")
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define IOS ios::sync_with_stdio(false)
#define mm(a, b) memset(a, b, sizeof(a))
#define each_cass(cass) for (cin>>cass; cass; cass--)
#define test(a) cout << "---------" << a << "---------" << '\n'
 
using namespace std;
#pragma endregion

//全局变量
#pragma region
const int maxn = 40010;
int C[maxn];
int num[maxn] = {0};
int n;
#pragma endregion

//主体------------------------------------------

inline int Lowbit(int x){
    return x & (-x);
}

inline int Sum(int i){//前区间和
    int res = 0;
    while(i) res += C[i], i -= Lowbit(i);
    return res;
}

inline void UpDate(int i, int val){//后面的都冲上，万一有的放得更靠后呢？
    while(i <= maxn) C[i] += val, i += Lowbit(i);
}

Chivas{
    scanf("%d", &n);
    mm(C, 0);
    for(int i = 0, x, y; i < n; i ++){
        scanf("%d%d", &x, &y);
        x ++;
        UpDate(x, 1);//x位置更新完
        num[Sum(x)] ++;//统计
    }
    for(int i = 1; i <= n; i ++) printf("%d\n", num[i]);
    Regal;
}
```
