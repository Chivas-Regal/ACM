# 🔗
https://acm.hdu.edu.cn/showproblem.php?pid=3336

# 💡
开始的时候想到，如果枚举出来前缀，然后用KMP搜一遍  
时间O(n^2)，肯定会超时  
  
那么想到KMP是使用nxt数组进行回溯到重复的公共前后缀  
那么我们可以发现每一次回溯都是因为有一个相同的串（而且如果前面顶到头，则就与前缀有关了）  
那么我们只需要每个位置统计一下回溯的数量即可  
不断回溯时间过长，可以使nxt[i]递推出dp[i] = dp[nxt[i]] + 1  

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
#include <unordered_map>
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

#define CHIVAS_ inline int Main()
#define _REGAL return 0;

#define SP system("pause")
#define IOS ios::sync_with_stdio(false)
//#define map unordered_map

#define pii pair<int, int> 
#define pll pair<ll, ll>
#define PB(x) push_back(x)
#define ALL(a) a.begin(),a.end()
#define MEM(a, b) memset(a, b, sizeof(a))
#define EACH_CASE(cass) for (cass = inputInt(); cass; cass--)

#define LS l, mid, rt << 1
#define RS mid + 1, r, rt << 1 | 1
#define GETMID (l + r) >> 1

using namespace std;
inline int inputInt(){int X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1);}
inline void outInt(int X){if(X<0) {putchar('-'); X=~(X-1);}int s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}
inline ll inputLL(){ll X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1); }
inline void outLL(ll X){if(X<0) {putchar('-'); X=~(X-1);}ll s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}

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

namespace Solution_In_Codeforces{
        inline void solve();
        namespace N_cass {
                int Main(){ int cass; for ( cin >> cass; cass; cass -- ) { solve();} return 0;};
        }
        namespace One_cass {
                int Main(){ solve(); return 0;};
        }
}

const int mod = 1e4 + 7;
const int N = 2e5 + 10;

class KMP_node{
private:
        string a, b;
        int nxt[N], dp[N];

public:
        inline KMP_node ( string aa, string bb ) { a = aa, b = bb; }
        inline void Get_Next ( ) {
                int j = -1;
                for ( int i = 0; i < b.size(); i ++ ) nxt[i] = -1, dp[i] = 0;
                for ( int i = 0; i + 1 < b.size(); i ++ ) {
                        while ( j >= 0 && b[j + 1] != b[i + 1] ) j = nxt[j];
                        if ( b[j + 1] == b[i + 1] ) j ++;
                        nxt[i + 1] = j;
                }
        }
        inline int Work ( ) { // 既然每次回溯都证明有一个公共串（也就是有一个相等的），回溯太慢，我们用nxt递推
                int res = 0;
                for ( int i = 0; i < b.size(); i ++ ) {
                        dp[i] = dp[nxt[i]] + 1;
                        res = (res + dp[i]) % mod;
                }
                return res;
        }
};

inline void Solution_In_Codeforces::solve(){
        int n; cin >> n; string s; cin >> s;
        KMP_node kmp = KMP_node("", s);
        kmp.Get_Next();  
        cout << kmp.Work() << endl;
}

CHIVAS_{IOS;
        Solution_In_Codeforces::N_cass::Main();
        _REGAL;
}









































int main(){

#ifndef ONLINE_JUDGE
freopen("in.in", "r", stdin);
freopen("out.out", "w", stdout);
#endif

        Main();

#ifndef ONLINE_JUDGE
cerr << "\033[1m\033[31m" << "\n\n===============================\n" << "|| Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s. ||\n" << "===============================" << "\033[0m";
#endif

        exit(0);
}
```
