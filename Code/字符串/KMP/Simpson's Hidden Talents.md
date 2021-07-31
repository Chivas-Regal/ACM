# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2594

# 💡
把两个串拼在一起  
求总串的nxt值但不能超过两个串的最小长度  
  
这里就算一下a的nxt值  
然后KMP中b和a向后走  
b的后面和a的nxt含的长度匹配  
若b走到尾存一下当前的res也就是a的j  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#pragma region
#pragma GCC optimize(3,"Ofast","inline")
#include <unordered_map>
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
struct KMP_node{
    string a, b;
    int nxt[1000005];
    inline void GET_NEXT(){//求前面的数的nxt数组
        int len = a.size();
        int j = -1;
        for(int i = 0; i < len; i ++) nxt[i] = -1;
        for(int i = 0; i < len - 1; i ++){
            while(j >= 0 && a[i + 1] != a[j + 1]) j = nxt[j];
            if(a[i + 1] == a[j + 1]) j ++;
            nxt[i + 1] = j;
        }
    }
    inline void KMP(){
        int lenb = b.size();
        int lena = a.size();
        int j = -1;
        int res = 0;//答案长度
        for(int i = -1; i < lenb - 1; i ++){//在B中匹配A的前串
            while(j >= 0 && a[j + 1] != b[i + 1]) j = nxt[j];
            if(a[j + 1] == b[i + 1]) j ++;
            if(i + 1 == lenb - 1) res = j;//看b走到最后a的j能走到哪
            if(j == lena - 1) j = nxt[j];//走到最后就向前拉
        }
        if(res == -1) cout << "0" << endl;
        else          cout << a.substr(0, res + 1) << " " << res + 1 << endl;
    }
}nd;

#pragma endregion

//主体------------------------------------------

Chivas{
    string a, b;
    IOS;
    while(cin >> a >> b){
        nd.a = a;
        nd.b = b;
        nd.GET_NEXT();
        nd.KMP();
    }
    Regal;
}
```
