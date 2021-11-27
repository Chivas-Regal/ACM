# 🔗
https://codeforces.com/problemset/problem/1200/E

# 💡
题目意思是，每次合并 res 和当前字符串 s   
我们在合并时有可能会删去字符串，但是删去的长度不会超过s  
所以我们在匹配时只需要匹配不超过vec[i]长度的res与vec[i]的公共前后缀  

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

#define CHIVAS_ inline int MAIN()
#define _REGAL return 0;

#define SP system("pause")
#define IOS ios::sync_with_stdio(false)
//#define map unordered_map

#define pbb pair<bool, bool>
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
                void Main(){ int cass; for ( cin >> cass; cass; cass -- ) { solve();} };
        }
        namespace One_cass {
                void Main(){ solve(); };
        }
}
inline void Solution_In_Codeforces::solve() {}




inline void Get_next ( int *nxt, string s ) { // 自获取nxt数组
        nxt[0] = -1;
        for ( int i = 0, j = -1; i < s.size(); i ++ ) {
                while ( j >= 0 && s[i + 1] != s[j + 1] ) j = nxt[j];
                if ( s[i + 1] == s[j + 1] ) j ++;
                nxt[i + 1] = j;
        }
}
inline int KMP ( string a, string b ) { // kmp前后缀匹配
        int nxt[b.size() + 10];
        int res;
        Get_next(nxt, b);
        for ( int i = -1, j = -1; i + 1 < a.size(); i ++ ) {
                while ( j >= 0 && b[j + 1] != a[i + 1] ) j = nxt[j];
                if ( b[j + 1] == a[i + 1] ) j ++;
                if ( i + 1 == a.size() - 1 ) res = j;
                if ( j + 1 == b.size() ) j = nxt[j];
        }return res + 1;
}


CHIVAS_{
        int n; cin >> n;
        vector<string> vec;
        for ( int i = 0; i < n; i ++ ) {
                string s; cin >> s;
                vec.push_back(s);
        }
        string res = vec[0];
        for ( int i = 1; i < n; i ++ ) {
                int las = MIN(res.size(), vec[i].size() + 1);           // res后面用来匹配vec[i]的长度
                string a = res.substr(res.size() - las, las);           // res后面用来匹配vec[i]的字符串
                int com = KMP(a, vec[i]);                               // a 与 vec[i] 匹配后得到的要删去字符的数量
                res += vec[i].substr(com, vec[i].size() - com + 1);     // res 加上这次匹配的字符
        } cout << res << endl;
        _REGAL;
}















int main(){

#ifndef ONLINE_JUDGE
freopen("in.in", "r", stdin);
freopen("out.out", "w", stdout);
#endif

        MAIN();

#ifndef ONLINE_JUDGE
cerr    << "\033[1m\033[31m\n" 
        << "\n\n===============================\n" 
        << "|| Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s. ||\n" 
        << "===============================" 
        << "\033[0m";
#endif

        exit(0);
}
```
