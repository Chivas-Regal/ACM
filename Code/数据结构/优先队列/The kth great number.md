# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=4006

# 💡
插入也是很费时的，反正m之后的用不到  
就实时存储实时pop就行   


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
int n, m;
priority_queue<int, vector<int>, greater<int> > pque;
#pragma endregion

Chivas{
    IOS;
    while(scanf("%d%d", &n, &m) == 2){
        
        while(pque.size()) pque.pop();

        for(int i = 0; i < n; i ++){
            getchar();
            char op; scanf("%c", &op);
            if(op == 'I'){
                int x; scanf("%d", &x);
                pque.push(x);
                if(pque.size() > m) pque.pop();
            }else{
                printf("%d\n", pque.top());
            }
        }
    }
    Regal;
}
```
