# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1027

# 💡
康托逆展开的模板题， 需牢记

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#pragma region
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
 
#pragma endregion

//全局变量
#pragma region
int n, m;
vector<int> f;//存阶乘
vector<int> vec;//存当前有多少个数可取（升序）
#pragma endregion

//主体----------------------------------------------------------------------------

void Jie_Cheng(){
    f.push_back(1);
    f.push_back(1);
    for(int i = 2; i < 13; i ++){
        f.push_back(f.back() * i);
    }
}

void Rev_Kangtuo(){
    vector<int> res;
    m --;
    for(int i = 1; i <= n; i ++){
        int id;
        if(n - i > 10) id = 0;//f[n - i]过大，m / f[n - i] = 0， m % f[n - i] = m，没必要
        else           id = m / f[n - i], m %= f[n - i];//加入第除数个，余数接着用
        res.push_back(vec[id]);
        vec.erase(vec.begin() + id);//删去
    }

    for(int i = 0; i < res.size(); i ++){
        printf("%d%c", res[i], i == res.size() - 1 ? '\n' : ' ');
    }
}

Chivas{
    Jie_Cheng();
    while(scanf("%d%d", &n, &m) == 2){
        vec.clear();
        for(int i = 1; i <= n; i ++) vec.push_back(i);
        Rev_Kangtuo();
    }
    Regal;
}
```
