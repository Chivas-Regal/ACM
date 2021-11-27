# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1028

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
#define fir(i, a, n) for (int i = a; i <= n; i++)
#define rif(i, a, n) for (int i = a; i >= n; i--)
#define each_cass(cass) for (cin >> cass; cass; cass--)

using namespace std;

const int maxn = 200;
int c1[maxn];
int c2[maxn];

void init(){
    for (int i = 0; i < maxn; i++)
        c1[i] = 1, c2[i] = 0;
}

int main(){
    int n;
    while(cin>>n){
        init();
        for (int i = 2; i <= n; i++){//n-1次合并
            for (int j = 0; j <= n; j++)//第一个括号
                for (int k = 0; k + j <= n; k += i)//第二个括号
                    c2[j + k] += c1[j];
            for (int j = 0; j <= n; j++)//替换
                c1[j] = c2[j], c2[j] = 0;
        }
        cout << c1[n] << endl;
    }
    return 0;
}
```
