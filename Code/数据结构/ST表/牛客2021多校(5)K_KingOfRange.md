# 🔗
https://ac.nowcoder.com/acm/contest/11256/K

# 💡
求整个数列中，Max - Min > k 的子区间个数
  
我们锁定左端点  
如果能固定到最短的右端点  
那么就可以在这个右端点的基础上向右延伸到右边界n  
即获得 n - r + 1 个满足条件的区间  

那么在端点的移动过程中  
我们可以使用双指针的计数思想   
另外我们还想能O(1)查询到区间的 Max 和 Min  
所以我们可以预处理出区间的 Max 和 Min  
于是用到ST表去处理

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
/*
           ________   _                                              ________                              _
          /  ______| | |                                            |   __   |                            | |
         /  /        | |                                            |  |__|  |                            | |
         |  |        | |___    _   _   _   ___  _   _____           |     ___|   ______   _____   ___  _  | |
         |  |        |  __ \  |_| | | | | |  _\| | | ____|          |  |\  \    |  __  | |  _  | |  _\| | | |
         |  |        | |  \ |  _  | | | | | | \  | | \___           |  | \  \   | |_/ _| | |_| | | | \  | | |
         \  \______  | |  | | | | \ |_| / | |_/  |  ___/ |          |  |  \  \  |    /_   \__  | | |_/  | | |
Author :  \________| |_|  |_| |_|  \___/  |___/|_| |_____| _________|__|   \__\ |______|     | | |___/|_| |_|
                                                                                         ____| |
                                                                                         \_____/
*/
//#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <utility>
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
#define EPS 1e-6
#define PI acos(-1.0)
#define INF 0x7FFFFFFF

#define ll long long
#define ull unsigned long long 
#define INT __int128

#define LOWBIT(x) ((x) & (-x))
#define LOWBD(a, x) lower_bound(a.begin(), a.end(), x) - a.begin()
#define UPPBD(a, x) upper_bound(a.begin(), a.end(), x) - a.begin()
#define TEST(a) cout << "---------" << a << "---------" << endl

#define CHIVAS_ int main()
#define _REGAL exit(0)

#define SP system("pause")
#define IOS ios::sync_with_stdio(false)
//#define map unordered_map

#define _int(a) int a; cin >> a
#define  _ll(a) ll a; cin >> a
#define _char(a) char a; cin >> a
#define _string(a) string a; cin >> a
#define _vectorInt(a, n) vector<int>a(n); cin >> a
#define _vectorLL(a, b) vector<ll>a(n); cin >> a

#define PB(x) push_back(x)
#define ALL(a) a.begin(),a.end()
#define MEM(a, b) memset(a, b, sizeof(a))
#define EACH_CASE(cass) for (cass = inputInt(); cass; cass--)

#define LS l, mid, rt << 1
#define RS mid + 1, r, rt << 1 | 1
#define GETMID (l + r) >> 1

using namespace std;


template<typename T> inline T MAX(T a, T b){return a > b? a : b;}
template<typename T> inline T MIN(T a, T b){return a > b? b : a;}
template<typename T> inline void SWAP(T &a, T &b){T tp = a; a = b; b = tp;}
template<typename T> inline T GCD(T a, T b){return b > 0? GCD(b, a % b) : a;}
template<typename T> inline void ADD_TO_VEC_int(T &n, vector<T> &vec){vec.clear(); cin >> n; for(int i = 0; i < n; i ++){T x; cin >> x, vec.PB(x);}}
template<typename T> inline pair<T, T> MaxInVector_ll(vector<T> vec){T MaxVal = -LNF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return make_pair(MaxVal, MaxId);}
template<typename T> inline pair<T, T> MinInVector_ll(vector<T> vec){T MinVal = LNF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return make_pair(MinVal, MinId);}
template<typename T> inline pair<T, T> MaxInVector_int(vector<T> vec){T MaxVal = -INF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return make_pair(MaxVal, MaxId);}
template<typename T> inline pair<T, T> MinInVector_int(vector<T> vec){T MinVal = INF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return make_pair(MinVal, MinId);}
template<typename T> inline pair<map<T, T>, vector<T> > DIV(T n){T nn = n;map<T, T> cnt;vector<T> div;for(ll i = 2; i * i <= nn; i ++){while(n % i == 0){if(!cnt[i]) div.push_back(i);cnt[i] ++;n /= i;}}if(n != 1){if(!cnt[n]) div.push_back(n);cnt[n] ++;n /= n;}return make_pair(cnt, div);}

inline int inputInt(){int X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1);}
inline void outInt(int X){if(X<0) {putchar('-'); X=~(X-1);}int s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}
inline ll inputLL(){ll X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1); }
inline void outLL(ll X){if(X<0) {putchar('-'); X=~(X-1);}ll s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}

const int N = 1e5 + 10;
int n, m;
int st_Max[N << 1][100], st_Min[N << 1][100]; // 开大一点，防止倍增越界
int Log2[N << 1];
inline void Get_Log2 ( ) { // 预处理 log 
        Log2[1] = 0;
        for (ll i = 2; i < N; i ++ ) Log2[i] = Log2[i / 2] + 1;
}
inline void Pre_Max_Min ( ) { // 预处理ST表
        int k = Log2[n];
        for ( int j = 1; j <= k; j ++ ) 
                for ( int i = 1; i + (1 << j) - 1 <= n; i ++ ) 
                        st_Max[i][j] = MAX(st_Max[i][j - 1], st_Max[i + (1 << (j - 1))][j - 1]),
                        st_Min[i][j] = MIN(st_Min[i][j - 1], st_Min[i + (1 << (j - 1))][j - 1]);
}
inline int Query_Max ( int l, int r ) { // ST表查询区间的最大值
        int k = Log2[r - l + 1];
        return MAX(st_Max[l][k], st_Max[r - (1 << k) + 1][k]);
}
inline int Query_Min ( int l, int r ) { // ST表查询区间的最小值
        int k = Log2[r - l + 1];
        return MIN(st_Min[l][k], st_Min[r - (1 << k) + 1][k]);
}
inline ll Solve ( int k ) {
        ll res = 0;
        for ( int l = 1, r = 1; l <= n && r <= n; l ++ ) { // 双指针维护区间
                while ( r <= n && Query_Max(l, r) - Query_Min(l, r) <= k ) r ++; // 移动右端点保证满足条件
                res += (ll)n - r + 1; // r 到 n 的区间都可以
        }
        return res;
}

CHIVAS_{
        Get_Log2();

        n = inputInt(), m = inputInt();
        for ( int i = 1; i <= n; i ++ )  st_Max[i][0] = st_Min[i][0] = inputInt();

        Pre_Max_Min();

        while ( m -- ) {
                outLL(Solve(inputLL())); puts("");
        }
        _REGAL;
}
```
