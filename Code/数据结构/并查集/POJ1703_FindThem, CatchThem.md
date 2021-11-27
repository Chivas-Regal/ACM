# 🔗
http://poj.org/problem?id=1703

# 💡
与食物链一样
并查集不仅用在正面对象
也可以对背后的对象建立并查集
所以关键是在分析都对什么建立并查集

本题让建立两个集合（两个不同的帮派）
故可以对每个帮派的反派也建立
来维护相反派之间的关系
因为有时候得到某种关系的时候，无法进行两者合并，只能对a的反派和b合并，b的反派和a合并


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
const int maxn = 2e5 + 10;
int nod[maxn];
int n, m;
#pragma endregion

//主体----------------------------------------------------------------------------------

inline void Init(){
    for(int i = 0; i <= n * 2; i ++) nod[i] = i;
}

inline int find(int x){
    return x == nod[x] ? x : nod[x] = find(nod[x]);
}

inline void merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx != fy) nod[fx] = fy;
}

inline void solve(){

    scanf("%d%d", &n, &m);
    Init();
    
    for(int i = 0; i < m; i ++){
        char op;
        int a, b;
        getchar();
        scanf("%c%d%d", &op, &a, &b);
        if(op == 'A'){
            int fa = find(a);
            int fb = find(b);
            int fa_n = find(a + n);
            int fb_n = find(b + n);
            if(fa_n == fb_n || fa == fb)
                cout << "In the same gang." << endl;
            else if(fa_n == fb || fa == fb_n)
                cout << "In different gangs." << endl;
            else   
                cout << "Not sure yet." << endl;
        }else{
            merge(a + n, b);
            merge(b + n, a);
        }
    }
}

Chivas{
    IOS;
    int cass;
    scanf("%d", &cass);
    while(cass--){
        solve();
    }
    Regal;
}
