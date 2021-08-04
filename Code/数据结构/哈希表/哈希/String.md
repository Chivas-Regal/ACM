# 🔗
https://acm.hdu.edu.cn/showproblem.php?pid=4821

# 💡
我们可以考虑把一段 m * l 的子串分成 m 个 l 的子串  
然后利用map统计不同的个数  
  
但是我们发现，从 1 步进到 s.size() 明显时间过长，达到 O(n^2)  
我们也能发现，这些串都是以 l 为周期进行的，也就是说我们在移动 l 次 1 后，将会锁定与第一次串同周期的区间  
那么我们就只需外层遍历 1 ～ l，然后每一次遍历都要直接通道最后。  
不同的 m * l 增一个后面的 l 区间，减一个前面的 l 区间，维护这 m * l 的不同l长子串个数

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





unordered_map<ull, int> mp;
int m, l; string s;


const int BASE = 31;
const int N = 1e5  +10;
class StringHash_Implement{
private:
        string s;
        ull HASH[N], amg[N];
public:
        inline StringHash_Implement ( string ss ) { s = ss; }
        inline void Init () {
                HASH[0] = s[0] - 'a';
                amg[0] = 1;
                for ( int i = 1; i < s.size(); i ++ ) {
                        HASH[i] = HASH[i - 1] * BASE + (ull)(s[i] - 'a');
                        amg[i] = amg[i - 1] * BASE;
                }
        }
        inline ull Get ( int l, int len ) {
                int r = l + len - 1;
                if ( l == 0 ) return HASH[r];
                return HASH[r] - HASH[l - 1] * amg[len];
        }
};

inline void Solve ( StringHash_Implement strHsh ) {
        int res = 0;
        for( int j = 0, lft = j, rgt = lft + m * l - 1; j < l && rgt < s.size(); j ++, lft = j, rgt = lft + m * l - 1 ) { // 锁定一下当前枚举的 m * l 的 lft 和 rgt 
                mp.clear();
                for ( int i = 0 ; i < m; i ++ ) mp[strHsh.Get(lft + i * l, l)] ++; // 先对这 m * l 存一下
                if ( mp.size() == m ) res ++;
                while ( rgt + l < s.size() ) { // 向后以 l 为单位地步进
                        lft += l, rgt += l;
                        
                        ull lose = strHsh.Get(lft - l, l);              //即将丢失的串
                        ull obtain = strHsh.Get(rgt - l + 1, l);        //即将获得的串
                        mp[lose] --;
                        if ( !mp[lose] ) mp.erase(lose);
                        mp[obtain] ++;

                        if ( mp.size() == m ) res ++;
                }
        }cout << res << endl;
}


CHIVAS_{
        while ( cin >> m >> l ) {
                cin >> s; 
                StringHash_Implement strHsh = StringHash_Implement(s);
                strHsh.Init(); Solve(strHsh);
        }
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
