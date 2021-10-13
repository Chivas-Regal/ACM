# 🔗
http://poj.org/problem?id=1258

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
//#pragma GCC optimize(3,"Ofast","inline")
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

const int maxn = 110;
struct Node{
    int x, y;
    int dis;
};
int nod[maxn];
int n;

inline bool cmp(Node a, Node b){
    return a.dis < b.dis;
}
inline void init(){
    for(int i = 0; i < maxn; i++) nod[i] = i;
}
inline int find(int x){
    return nod[x] == x? x : nod[x] = find(nod[x]);
}
inline bool isFamily(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx == fy) return true;
    else         return false;
}
inline void Merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx != fy){
        nod[fx] = fy;
    }
}

Chivas{
    while(scanf("%d", &n) == 1){
        init();
        vector<Node> vec;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                int len;
                scanf("%d", &len);
                vec.push_back({i, j, len});
            }
        }
        sort(vec.begin(), vec.end(), cmp);
        
        int cnt = 0;
        int sum = 0;
        for(int i = 0; i < vec.size(); i++){
            if(!isFamily(vec[i].x, vec[i].y)) 
                Merge(vec[i].x, vec[i].y), 
                cnt++, 
                sum += vec[i].dis;
            if(cnt == n - 1) 
                break;
        }
        printf("%d\n", sum);
    }
    Regal;
}
```
