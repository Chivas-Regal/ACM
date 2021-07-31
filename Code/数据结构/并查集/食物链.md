# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2844

# 💡
分析到题中有三种集合关系  
  
我们在得到谁吃谁的时候无法对两者进行合并  
所以可以对a的被吃、b的吃、a的吃、b的吃进行合并  
即两种权值以n为边界开成两维  

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
const int maxn = 155000;

int nod[maxn];
int n, k;
int cnt = 0;
#pragma endregion


//主体------------------------------------------------------------

inline int find(int x){
    return x == nod[x]? x:nod[x]=find(nod[x]);
}

inline void merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx != fy){
        nod[fx] = fy;
    }
}

inline void init(){
    for(int i = 0; i < maxn; i ++){
        nod[i] = i;
    }
}

Chivas{
    IOS;
    cin >> n >> k;
    init();
    for(int i = 0; i < k; i ++){
        int id, x, y;
        cin >> id >> x >> y;
        if(x > n || y > n || x <= 0 || y <= 0){
            ++cnt;
            continue;
        }
        int fx = find(x);
        int fy = find(y);
        if(id == 1){
            if(find(x) == find(y + n) || find(x) == find(y + 2 * n))  ++cnt;
            else  merge(x, y), merge(x + n, y + n), merge(x + 2 * n, y + 2 * n);
        }else{
            if(x == y){
                cnt ++;
                continue;
            }
            if(find(x) == find(y) || find(x) == find(y + 2 * n))     ++cnt;
            else  merge(x, y + n), merge(x + n, y + 2 * n), merge(x + 2 * n, y);
        }
    }
    cout << cnt << endl;
    Regal;
}
