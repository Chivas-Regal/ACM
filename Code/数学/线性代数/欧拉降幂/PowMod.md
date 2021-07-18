# 🔗
https://acm.dingbacode.com/showproblem.php?pid=5728

# 💡
问题可拆解成两个子问题（子过程）  
<ol>
  <li>
    <b>解K</b><br>
    由于 n 无平方因子，所以 n 唯一分解成几个质因子之后，每个质因子 p 都与别的互质<br><br>
    即：<br><img src="https://latex.codecogs.com/svg.image?\phi(p*\frac&space;np)=\phi(p)*\phi(\frac&space;np)" title="\phi(p*\frac np)=\phi(p)*\phi(\frac np)" /><br><br>
    设<br><img src="https://latex.codecogs.com/svg.image?\sum\limits_{n=1}^m\phi(i,n)=f(n,m)" title="\sum\limits_{n=1}^m\phi(i,n)=f(n,m)" /><br><br>
    <img src="https://latex.codecogs.com/svg.image?\sum\limits_{n=1}^m\phi(i,n)=\phi(p)\sum\limits_{i=1}^m\phi(i,\frac&space;np)&plus;\sum\limits_{i=1}^{\frac&space;mp}\phi(i,n)" title="\sum\limits_{n=1}^m\phi(i,n)=\phi(p)\sum\limits_{i=1}^m\phi(i,\frac np)+\sum\limits_{i=1}^{\frac mp}\phi(i,n)" /><img src="https://latex.codecogs.com/svg.image?\Rightarrow&space;f(n,m)=\phi(p)*f(\frac&space;np,&space;m)&plus;f(n,&space;\frac&space;mp)" title="\Rightarrow f(n,m)=\phi(p)*f(\frac np, m)+f(n, \frac mp)" /><br>
  </li>
  <li>
    <b>递归降幂</b><br>
    用<br><img src="https://latex.codecogs.com/svg.image?a^b=a^{b%\phi(n)&plus;\phi(n)}(mod\quad&space;n)" title="a^b=a^{b%\phi(n)+\phi(n)}(mod\quad n)" />递归一层层降幂<br>
    递归出口是 phi = 1 <br>
  </li>
</ol>

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

#define LOWBIT(x) ((x) & (-x))
#define LOWBD(a, x) lower_bound(a.begin(), a.end(), x) - a.begin()
#define UPPBD(a, x) upper_bound(a.begin(), a.end(), x) - a.begin()
#define TEST(a) cout << "---------" << a << "---------" << '\n'

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

const int N = 1e7 + 10, mod = 1e9 + 7;
int phi[N], isprime[N];
int sum[N];
vector<int> prime;

inline void GET_PHI () {
        isprime[0] = isprime[1] = 1, phi[1] = 1;
        for ( int i = 2; i < N; i ++ ) {
                if ( !isprime[i] ) prime.push_back(i), phi[i] = i - 1;
                for ( int j = 0; j < prime.size() && i * prime[j] < N; j ++ ) {
                        isprime[i * prime[j]] = 1;
                        if ( i % prime[j] == 0 ) {
                                phi[i * prime[j]] = phi[i] * prime[j];
                                break;
                        }else   phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                }
        }
        for ( int i = 1; i < N; i ++ ) sum[i] = (sum[i - 1] + phi[i]) % mod;
}

inline ll GET_K ( int n, int m ) { //解K
        //把f ( n, m )换回累加phi的形式，会得到三个特判，也能成为递归出口
        if ( m < 1 ) return 0;
        if ( m == 1 ) return phi[n];
        if ( n == 1 ) return sum[m];

        if ( phi[n] == n - 1 ) return (GET_K(1, m) * phi[n] % mod + GET_K(n, m / n)) % mod; // 质数，没必要查因子了
        for ( int i = 2; i * i <= n; i ++ ){ // 质因子拆解
                if ( n % i ) continue;
                return (phi[i] * GET_K(n / i, m) % mod + GET_K(n, m / i)) % mod;
        }
}

inline ll ksm ( ll a, ll b, ll mod ) {
        ll res = 1;
        while ( b ) {
                if ( b & 1 ) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }return res;
}

inline ll get(ll k, ll p){ // 递归降层幂
        if ( p == 2 ) return k & 1;
        return ksm ( k, get ( k, phi[p] ) + phi[p], p );
}

CHIVAS_{GET_PHI();
        int n, m, p;
        while ( scanf ( "%d%d%d", &n, &m, &p ) == 3 ) {
                ll k = GET_K ( n, m );
                outLL ( get ( k, p ) ); puts("");
        }
        _REGAL;
};



```
