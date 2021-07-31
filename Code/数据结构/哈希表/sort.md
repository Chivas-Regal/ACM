# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1425

# 💡
模板题  
  
sort或堆排肯定超时（unordered_map也超时就离谱）  
用hash表放位置  
输入完即存完  
  
输出时在范围内降序查找即可  

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
const int maxn = 1e6 + 10;
int mp[maxn];//存输入的某个数的个数
int n, m;
int vec[maxn];//存输入的数
#pragma endregion

//主体-------------------------------------------------------

Chivas{
   while(scanf("%d%d", &n, &m) == 2){

      for(int i = 0, x; i < n; i ++){
         scanf("%d", &vec[i]);
         mp[vec[i] + 500000]++;//"++"是因为可能重复输入，"+500000"是因为输入可能有负数
      }

      bool first_put = false;
      for(int i = 1000000; i >= 0; i--){
         while(m && mp[i]){
            if(first_put) printf(" %d",i - 500000);
            else          printf("%d", i - 500000), first_put = true;
            
            mp[i]--;
            m--;
         }
         if(!m) break;
      }
      printf("\n");
      

      for(int i = 0; i < n; i ++) mp[vec[i] + 500000] = 0;//清除

   }
   Regal;
}
```
