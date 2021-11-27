# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=1496

# 💡
1.暴力存三重循环然后查最后一个是否存在  
2.用大size存数组，直接把数放进下标内  
3.用小size存数组，然后用除余存地址  

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
const int maxn_solve2 = 2e6 + 10;
const int maxn_solve3 = 5e4 + 10;//100 * 100 最多产生 10000 种可能性
int x[110];//打平方表
int num[maxn_solve3];//该地址存放元素个数
int val[maxn_solve3];//该地址存放的什么元素
int _hash[maxn_solve2];
int a, b, c, d;
#pragma endregion

//主体-------------------------------------------------------------------------

inline int Hash(int x){//除余选址
   int id = x % maxn_solve3;//第一步固定地址范围
   if(id < 0) id += maxn_solve3;//x可能为负数，负数除余出来的地址+maxn就为正了
   while(num[id] && val[id] != x) //前用作存入时的判断，后用于查找时的判断
      id = (id + 1) % maxn_solve3;//环式选址：后面的找不到就去前面找
   return id;
}

inline void solve_1(){
   for(int i = 0; i < 110; i ++) x[i] = i * i;
   while(scanf("%d%d%d%d", &a, &b, &c, &d) == 4){
      if((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0)){
         printf("0\n");
         continue;
      }

      ll res = 0;

      for(int i = 1; i <= 100; i ++){
         for(int j = 1; j <= 100; j ++){
            for(int k = 1; k <= 100; k ++){
               int cur_s = x[i] * a + x[j] * b + x[k] * c;
               int end_be_mod = cur_s % d;
               int end_ans = ( - cur_s) / d;
               if(end_be_mod == 0 && end_ans <= 10000 && end_ans > 0 && (int)sqrt(end_ans) * (int)sqrt(end_ans) == end_ans) 
                  res ++;
            }
         }
      }

      printf("%lld\n", res * 16);
   }
}

inline void solve_2(){
   for(int i = 0; i < 110; i ++) x[i] = i * i;
   while(scanf("%d%d%d%d", &a, &b, &c, &d) == 4){
      if((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)){
         printf("0\n");
         continue;
      }

      mm(_hash, 0);

      //存入
      for(int i = 1; i <= 100; i ++){
         for(int j = 1; j <= 100; j ++){
            _hash[x[i] * a + x[j] * b + 1000000] ++;//防负数，所以 + 1000000
         }
      }

      ll res = 0;

      //统计
      for(int i = 1; i <= 100; i ++){
         for(int j = 1; j <= 100; j ++){
            res += _hash[ - (c * x[i] + d * x[j]) + 1000000];
         }
      }

      printf("%lld\n", res * 16);
   }
}

inline void solve_3(){
   for(int i = 0; i <= 100; i ++) x[i] = i * i;
   while(scanf("%d%d%d%d", &a, &b, &c, &d) == 4){
      if((a < 0 && b < 0 && c < 0 && d < 0) || (a > 0 && b > 0 && c > 0 && d > 0)){
         printf("0\n");//怎么都不可能为0
         continue;
      }
      mm(num, 0), mm(val, 0);

      //存入 a * x[1]^2 + b * x[2]^2的所有可能性
      for(int i = 1; i <= 100; i ++){
         for(int j = 1; j <= 100; j ++){
            int cur = x[i] * a + x[j] * b;
            int hash_cur = Hash(cur);
            val[hash_cur] = cur, num[hash_cur] ++;
         }
      }

      ll res = 0;

      for(int i = 1; i <= 100; i ++){
         for(int j = 1; j <= 100; j ++){
            int cur = - (x[i] * c + x[j] * d);//查找相反的
            int hash_cur = Hash(cur);
            res += num[hash_cur];//计算该位置存入多少个数
         }
      }

      printf("%lld\n", res * 16);//因为我们只找了[0, 100]，每一个都对称，所以要乘 2^4 = 16

   }
}

Chivas{
   Regal;
}
```
