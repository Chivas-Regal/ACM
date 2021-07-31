# 🔗
https://pintia.cn/problem-sets/1384757951243542528/problems/1384758301778305035

# 💡
是一个单一对next数组的应用过程

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
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

const int maxn = 100005;

int Next[maxn];
int ans[maxn];
string s;

inline void get_next(){
    int i = 0;
    int k = -1;
    Next[0] = -1;
    int len = s.size();
    while(i < len){
        if(k == -1 || s[i] == s[k]) Next[++i] = ++k;
        else                        k = Next[k];
    }
}


Chivas{
    IOS;
    getline(cin,s);
    get_next();
    
    int len = s.size();
    int len_ans = 0;
    int j = Next[s.size()];
    while(j > 0){
        ans[len_ans ++] = j;
        j = Next[j];
    }
    sort(ans, ans + len_ans, greater<int>());

    if(s.size() == 1){
        cout << "1" << endl;
        Regal;
    }

    int res = len - ans[1] * 2;
    if(res < 0) res = 0;
    printf("%d", res);
    Regal;
}
```
