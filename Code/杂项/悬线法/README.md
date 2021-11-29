<h1 align="center">📕【模板】悬线法</h1>
<h3> ❓ : 在 01矩阵 内求最大的 全1矩阵  面积</h3>

预处理出每个点的列中最长值，横向左移最远点，横向右移最远点，这样就有了长和高  
  
在求面积之前，还要缩一下横向端点  
原因是：  
<table>
  <tr>
    <td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td><td>1</td>  
  </tr>
  <tr>
    <td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td>  
  </tr>
  <tr>
    <td>0</td><td>1</td><td>1</td><td>x</td><td>1</td><td>1</td><td>0</td>
  </tr>
</table>
此时x点得到的是由第三行固定的左右边和整个3行的高  
但明显应需要被上面的lft和rgt继承一下才行  
所以我们要用上一行的结果在一定条件下缩边    
  
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

#define LOWBIT(x) ((x) & (-x))
#define LOWBD(a, x) lower_bound(a.begin(), a.end(), x) - a.begin()
#define UPPBD(a, x) upper_bound(a.begin(), a.end(), x) - a.begin()
#define TEST(a) cout << "---------" << a << "---------" << '<br>'

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
template<typename T> inline pair<T, T> MaxInVector_ll(vector<T> vec){T MaxVal = -LNF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return {MaxVal, MaxId};}
template<typename T> inline pair<T, T> MinInVector_ll(vector<T> vec){T MinVal = LNF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return {MinVal, MinId};}
template<typename T> inline pair<T, T> MaxInVector_int(vector<T> vec){T MaxVal = -INF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return {MaxVal, MaxId};}
template<typename T> inline pair<T, T> MinInVector_int(vector<T> vec){T MinVal = INF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return {MinVal, MinId};}
template<typename T> inline pair<map<T, T>, vector<T> > DIV(T n){T nn = n;map<T, T> cnt;vector<T> div;for(ll i = 2; i * i <= nn; i ++){while(n % i == 0){if(!cnt[i]) div.push_back(i);cnt[i] ++;n /= i;}}if(n != 1){if(!cnt[n]) div.push_back(n);cnt[n] ++;n /= n;}return {cnt, div};}
template<typename T>             vector<T>& operator--            (vector<T> &v){for (auto& i : v) --i;            return  v;}
template<typename T>             vector<T>& operator++            (vector<T> &v){for (auto& i : v) ++i;            return  v;}
template<typename T>             istream& operator>>(istream& is,  vector<T> &v){for (auto& i : v) is >> i;        return is;}
template<typename T>             ostream& operator<<(ostream& os,  vector<T>  v){for (auto& i : v) os << i << ' '; return os;}
inline int inputInt(){int X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1);}
inline void outInt(int X){if(X<0) {putchar('-'); X=~(X-1);}int s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}
inline ll inputLL(){ll X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1); }
inline void outLL(ll X){if(X<0) {putchar('-'); X=~(X-1);}ll s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}

const int N = 1e3 + 10;
char Map[N][N];
int lft[N][N], rgt[N][N], up[N][N];

inline void solve () {

        int n = inputInt(), m = inputInt(); // 长 * 宽
        for ( int i = 1; i <= n; i ++ ) for ( int j = 1; j <= m; j ++ ) Map[i][j] = inputInt();

        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 1; j <= m; j ++ )     lft[i][j] = rgt[i][j] = j * (Map[i][j] == 1), up[i][j] = (Map[i][j] == 1); // 初始化
                for ( int j = 2; j <= m; j ++ )     if ( Map[i][j] && Map[i][j - 1] ) lft[i][j] = lft[i][j - 1]; // 递推左端点
                for ( int j = m - 1; j >= 0; j -- ) if ( Map[i][j] && Map[i][j + 1] ) rgt[i][j] = rgt[i][j + 1]; // 递推右端点
        }
        for ( int i = 2; i <= n; i ++ ) {
                for ( int j = 1; j <= m; j ++ ) if ( Map[i][j] && Map[i - 1][j] ) up[i][j] = up[i - 1][j] + 1; // 递推高
        }
        for ( int i = 2; i <= n; i ++ ) {
                for ( int j = 1; j <= m; j ++ ) {
                        if ( Map[i][j] && Map[i - 1][j] ) { // 第一行之外缩横边
                                lft[i][j] = MAX(lft[i][j], lft[i - 1][j]);
                                rgt[i][j] = MIN(rgt[i][j], rgt[i - 1][j]);
                        }
                }
        }
        int res = 0;
        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 1; j <= n; j ++ ) {
                        res = MAX(res, up[i][j] * (rgt[i][j] - lft[i][j] + 1)); // 面积 = 长 * 高
                }
        }
        outInt(res);
}

CHIVAS_{
        solve();
        _REGAL;
};
```
