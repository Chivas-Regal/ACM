# 🔗
https://codeforces.com/contest/1555/problem/D

# 💡
由于不能出现长度至少为2的回文子串，意味着两个同样的字符挨着就不成立   
  
那么分析一个较长的字符串，要想成立，在纸上模拟后发现只有六种构造方式，即以 a b c 为元素的六个排列作为循环节  
  
那么我们对每次裁出来的字符串求得这六种循环节所花费的最小值即可  

但是无疑每次循环一遍会超时，同时我们知道由于是排列，所以循环节一起从哪开始都无所谓，所以我们可以设立一个前缀和进行预处理，在求的时候计算它们差分的最小值即可  
  
同时观测数据还有两个特点：
1. r = l，必定为0
2. r - l + 1 = 2，此时要看一下前后是否相等
3. r - l + 1 > 2，那么就是我们上面说到的构造方式之间的比较

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
template<typename T> inline pair<T, T> MaxInVector_ll(vector<T> vec){T MaxVal = -LNF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return make_pair(MaxVal, MaxId);}
template<typename T> inline pair<T, T> MinInVector_ll(vector<T> vec){T MinVal = LNF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return make_pair(MinVal, MinId);}
template<typename T> inline pair<T, T> MaxInVector_int(vector<T> vec){T MaxVal = -INF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal < vec[i]) MaxVal = vec[i], MaxId = i; return make_pair(MaxVal, MaxId);}
template<typename T> inline pair<T, T> MinInVector_int(vector<T> vec){T MinVal = INF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i]) MinVal = vec[i], MinId = i; return make_pair(MinVal, MinId);}
template<typename T> inline pair<map<T, T>, vector<T> > DIV(T n){T nn = n;map<T, T> cnt;vector<T> div;for(ll i = 2; i * i <= nn; i ++){while(n % i == 0){if(!cnt[i]) div.push_back(i);cnt[i] ++;n /= i;}}if(n != 1){if(!cnt[n]) div.push_back(n);cnt[n] ++;n /= n;}return make_pair(cnt, div);}

inline int inputInt(){int X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1);}
inline void outInt(int X){if(X<0) {putchar('-'); X=~(X-1);}int s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}
inline ll inputLL(){ll X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1); }
inline void outLL(ll X){if(X<0) {putchar('-'); X=~(X-1);}ll s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}

const int N = 2e5 + 10;
int res1[N], res2[N], res3[N], res4[N], res5[N], res6[N];

inline void solve ( ){
        int n; cin >> n;
        int m; cin >> m;
        string s; cin >> s; s = "0" + s;
                        for (int i = 1; i < s.size(); i ++ ) {
                                if (i % 3 == 0){
                                        res1[i] = res1[i - 1] + (s[i] != 'a');
                                        res2[i] = res2[i - 1] + (s[i] != 'a');
                                        res3[i] = res3[i - 1] + (s[i] != 'b');
                                        res4[i] = res4[i - 1] + (s[i] != 'b');
                                        res5[i] = res5[i - 1] + (s[i] != 'c');
                                        res6[i] = res6[i - 1] + (s[i] != 'c');
                                } else if (i % 3 == 1) {
                                        res1[i] = res1[i - 1] + (s[i] != 'b');
                                        res2[i] = res2[i - 1] + (s[i] != 'c');
                                        res3[i] = res3[i - 1] + (s[i] != 'c');
                                        res4[i] = res4[i - 1] + (s[i] != 'a');
                                        res5[i] = res5[i - 1] + (s[i] != 'a');
                                        res6[i] = res6[i - 1] + (s[i] != 'b');
                                } else {
                                        res1[i] = res1[i - 1] + (s[i] != 'c');
                                        res2[i] = res2[i - 1] + (s[i] != 'b');
                                        res3[i] = res3[i - 1] + (s[i] != 'a');
                                        res4[i] = res4[i - 1] + (s[i] != 'c');
                                        res5[i] = res5[i - 1] + (s[i] != 'b');
                                        res6[i] = res6[i - 1] + (s[i] != 'a');
                                }
                        }
        while ( m -- ) {
                int l, r; cin >> l >> r;
                if(l == r){
                        cout << 0 << endl;
                } else if ( r == l + 1 ) {
                        if ( s[r] == s[l] ) cout << 1 << endl;
                        else cout << 0 << endl;
                } else {
                        cout << MIN( 
                                MIN(
                                MIN(res1[r] - res1[l - 1], res2[r] - res2[l - 1]), 
                                MIN(res3[r] - res3[l - 1], res4[r] - res4[l - 1])), 
                                MIN(res5[r] - res5[l - 1], res6[r] - res6[l - 1]) ) << endl;
                }
        }
}

CHIVAS_{IOS;
    solve();
    _REGAL;
}
```
