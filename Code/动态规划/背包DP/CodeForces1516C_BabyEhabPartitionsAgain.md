# 🔗
https://codeforces.com/contest/1516/problem/C

# 💡
本题目的是让求：是否能删去一个数或者不删数，使得整个序列不可被拆分成两个相同的序列  
  
那么首先我们要知道一个序列可以被拆分成两个子序列的条件  
即和为偶数，同时可以选出来几个数的和为 sum / 2，其中 sum 是所有数的和  
所以非这两种情况下，我们根本不用删数就能保证不可拆  
那么我们在判断的时候可以使用**01背包**进行判断，在容量为 sum/2 是否有数可以凑出来这个值  
  
然后就是对删什么数的一个查找过程（利用dp思想）  
我们知道，如果整个序列除上同一个数，那么它能不能拆的答案还是跟以前一样，因为对整体效果不影响  
也就是说，一个所有数被缩小的序列能否拆开，决定了我们原数组能否被拆开，这就是我们的子问题  
这里有三种方法  
  
**方法1:**  
那么我们的目的是暴露出其中的奇数，使得这个 sum' 不再是偶数，它就不能再拆了  
所以我们对每个数不断“除2”，直到数组中出现第一个奇数，输出它的下标即可  
（但要加一个判断它是不是一开始就有奇数）  

**方法2:**  
是对方法1的一个延伸方法，就是求得每个数里面最多含了几个2  
其中含2最少的肯定就是最早变成奇数的  
这种方法好在不用最后再特判一下是不是一开始就有奇数导致我们跳过了循环  
  
**方法3:**  
是上面讲的思路的最直观解法  
我们求得整个序列的GCD  
然后对整个序列约分一下  
其中第一个奇数我们就可以删去让数组不可拆  

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

#define LOWBIT(x) ((x) & (-x))
#define LOWBD(a, x) lower_bound(a.begin(), a.end(), x) - a.begin()
#define UPPBD(a, x) upper_bound(a.begin(), a.end(), x) - a.begin()
#define TEST(a) cout << "---------" << a << "---------" << endl

#define CHIVAS_ int main()
#define _REGAL exit(0)
#define SP system("pause")
#define IOS ios::sync_with_stdio(false)

//#define map unordered_map

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
template<typename T> inline pair<T, T> MaxInVector_ll(vector<T> vec){T MaxVal = -LNF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal <vec[i]) MaxVal = vec[i], MaxId = i; return {MaxVal, MaxId};}
template<typename T> inline pair<T, T> MinInVector_ll(vector<T> vec){T MinVal = LNF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i])MinVal = vec[i], MinId = i; return {MinVal, MinId};}
template<typename T> inline pair<T, T> MaxInVector_int(vector<T> vec){T MaxVal = -INF, MaxId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MaxVal <vec[i]) MaxVal = vec[i], MaxId = i; return {MaxVal, MaxId};}
template<typename T> inline pair<T, T> MinInVector_int(vector<T> vec){T MinVal = INF, MinId = 0;for(int i = 0; i < (int)vec.size(); i ++) if(MinVal > vec[i])MinVal = vec[i], MinId = i; return {MinVal, MinId};}
template<typename T> inline pair<map<T, T>, vector<T> > DIV(T n){T nn = n;map<T, T> cnt;vector<T> div;for(ll i = 2; i * i <= nn; i ++){while(n % i == 0){if(!cnt[i]) div.push_back(i);cnt[i] ++;n /= i;}}if(n != 1){if(!cnt[n]) div.push_back(n);cnt[n] ++;n /= n;}return {cnt, div};}
template<typename T> vector<T>& operator-- (vector<T> &v){for (auto& i : v) --i; return v;}
template<typename T> vector<T>& operator++ (vector<T> &v){for (auto& i : v) ++i; return v;}
template<typename T> istream& operator>>(istream& is, vector<T> &v){for (auto& i : v) is >> i; return is;}
template<typename T> ostream& operator<<(ostream& os, vector<T> v){for (auto& i : v) os << i << ' '; return os;}
inline int inputInt(){int X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1);}
inline void outInt(int X){if(X<0) {putchar('-'); X=~(X-1);}int s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}
inline ll inputLL(){ll X=0; bool flag=1; char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}if(flag) return X;return ~(X-1); }
inline void outLL(ll X){if(X<0) {putchar('-'); X=~(X-1);}ll s[20],top=0;while(X) {s[++top]=X%10; X/=10;}if(!top) s[++top]=0;while(top) putchar(s[top--]+'0');}

// 方法1 ------------------------------------------------------------------------------------------
inline bool is_all_even(vector<int> vec){
        for(int i = 0; i < vec.size(); i ++){
                if(vec[i] & 1) return false;
        }
        return true;
}
inline void Cout_Find_1(vector<int> vec){
        while(is_all_even(vec)){
                for(int i = 0; i < vec.size(); i ++){//每个数不断 / 2，直到第一个奇数出现
                        vec[i] >>= 1;
                        if(vec[i] & 1){
                                outInt(1); puts("");
                                outInt(i + 1); puts("");
                                return;
                        }
                }
        }
        for(int i = 0; i < vec.size(); i ++){ // 如果本身就含有奇数
                if(vec[i] & 1){
                        outInt(1); puts("");
                        outInt(i + 1); puts("");
                        return;
                }
        }
}
// --------------------------------------------------------------------------------------------------


// 方法2 ---------------------------------------------------------------------------------------------

inline void Cout_Find_2(vector<int> vec){//寻找每个数
        vector<int> b(vec.size(), 0);
        for(int i = 0; i < vec.size(); i ++){
                while(vec[i] % (1 << b[i]) == 0) b[i] ++;
                b[i] --;
        }
        int res_id = 0;
        for(int i = 0; i < vec.size(); i ++){
                if(b[i] < b[res_id]) res_id = i;
        }
        outInt(1); puts("");
        outInt(res_id + 1); puts("");
}
// ----------------------------------------------------------------------------------------------------


// 方法3 -----------------------------------------------------------------------------------------------

inline void Cout_Find_3(vector<int> vec){//直接约分整个数组
        int gcd = vec[0];
        for(int i = 0; i < vec.size(); i ++) gcd = GCD(gcd, vec[i]);
        for(int i = 0; i < vec.size(); i ++){
                vec[i] /= gcd;
                if(vec[i] & 1){
                        outInt(1); puts("");
                        outInt(i + 1); puts("");
                        return;
                }
        }
}
// ----------------------------------------------------------------------------------------------------

CHIVAS_{
        int n = inputInt();
        vector<int> a(n), dp(200010, 0);
        int sum = 0;
        for(int i = 0; i < n; i ++){
                a[i] = inputInt();
                sum += a[i];
        }
        for(int i = 0; i < n; i ++){//01背包凑sum / 2
                for(int j = sum; j >= a[i]; j --){
                        dp[j] = MAX(dp[j], dp[j - a[i]] + a[i]);
                }
        }
        if((sum & 1) || dp[sum >> 1] != (sum >> 1)){//为奇数或者凑不出来都是0
                outInt(0); puts("");
                return 0;
        }

        Cout_Find_1(a);//全是偶数且可以凑出sum / 2时，寻找要删哪个
        
        _REGAL;
}




```




