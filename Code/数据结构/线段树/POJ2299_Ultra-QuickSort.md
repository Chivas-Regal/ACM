
# 🔗
http://poj.org/problem?id=2299

# 💡


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

#define CHIVAS_ inline int MAIN(){
#define _REGAL return 0;}

#define SP system("pause")
#define IOS ios::sync_with_stdio(false)
//#define map unordered_map

#define pbb pair<bool, bool>
#define pii pair<int, int> 
#define pll pair<ll, ll>
#define PB(x) push_back(x)
#define ALL(a) a.begin(),a.end()
#define MEM(a, b) memset(a, b, sizeof(a))
#define EACH_CASE(cass) for ( int cass = inputInt(); cass; cass--)

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















// =============================================================  BeginCode  ==========================================================================================


const int maxn = 5e5 + 15;
struct SegTree{
        int lazy;
        int val;
} SegTree[maxn << 2];
struct Num{
        int id;
        int val;
        friend bool operator<(Num a,Num b){
                return a.val < b.val;
        }   
} Num[maxn];
int A[maxn];
int n;

inline void Disc();
inline void PushUp(int rt);
inline void PushDown(int l, int r, int rt);
inline void BuildTree(int l, int r, int rt);
inline void UpDate(int a, int b, int c, int l, int r, int rt);
inline ll Query(int a, int b, int l, int r, int rt);


CHIVAS_
        while(scanf("%lld",&n)==1,n){
                for (int i = 1; i <= n; i++) scanf("%lld", &Num[i].val), Num[i].id = i;
                Disc();
                ll cnt = 0;
                BuildTree(1, n, 1);
                for (int i = 1; i <= n; i++){
                UpDate(A[i], A[i], 1, 1, n, 1);
                cnt += Query(A[i]+1, n, 1, n, 1);
                }
                printf("%lld\n", cnt);
        }
_REGAL

inline void Disc(){
        int cnt = 0;
        sort(Num + 1, Num + n + 1);
        A[Num[1].id] = 1;
        cnt=1;
        for (int i = 2; i <= n; i++){
                if(Num[i].val==Num[i-1].val)
                A[Num[i].id] = cnt;
                else
                A[Num[i].id] = ++cnt;
        }
}
inline void PushUp(int rt){
        SegTree[rt].val = SegTree[rt << 1].val + SegTree[rt << 1 | 1].val;
}
inline void PushDown(int l, int r, int rt){
        if (!SegTree[rt].lazy)
                return;
        int mid = (l + r) >> 1;
        SegTree[rt << 1].val += SegTree[rt].lazy * (mid - l + 1);
        SegTree[rt << 1 | 1].val += SegTree[rt].lazy * (r - mid);
        SegTree[rt << 1].lazy += SegTree[rt].lazy;
        SegTree[rt << 1 | 1].lazy += SegTree[rt].lazy;
        SegTree[rt].lazy = 0;
}
inline void BuildTree(int l, int r, int rt){
        SegTree[rt].lazy = 0;
        if (l == r)
        {
                SegTree[rt].val = 0;
                return;
        }
        int mid = (l + r) >> 1;
        BuildTree(l, mid, rt << 1);
        BuildTree(mid + 1, r, rt << 1 | 1);
        PushUp(rt);
}
inline void UpDate(int a, int b, int c, int l, int r, int rt){
        if (a > r || b < l)
                return;
        if (a <= l && b >= r){
                SegTree[rt].val += c * (r - l + 1);
                SegTree[rt].lazy += c;
                return;
        }
        PushDown(l, r, rt);
        int mid = (l + r) >> 1;
        UpDate(a, b, c, l, mid, rt << 1);
        UpDate(a, b, c, mid + 1, r, rt << 1 | 1);
        PushUp(rt);
}
inline ll Query(int a, int b, int l, int r, int rt){
        if (a > r || b < l)
                return 0;
        if (a <= l && b >= r)
                return SegTree[rt].val;
        PushDown ( l, r, rt );
        int mid = (l + r) >> 1;
        return Query(a, b, l, mid, rt << 1) + Query(a, b, mid + 1, r, rt << 1 | 1);
}     





// =============================================================  EndCode  ==========================================================================================
































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
};
```
