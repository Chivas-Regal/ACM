
# 🔗 
https://acm.dingbacode.com/showproblem.php?pid=1384

# 💡
设置dis[i]表示[0, i]这个区间至少有多少点能被选中</br>
于是得到三个约束点</br>
1. (b[i]) - (a[i] - 1) >= c[i]
2. (d[i]) - (d[i - 1]) >= 0
3. (d[i]) - (d[i - 1]) <= 1
根据这三个条件建图，然后用“>=”求最长路即可

# <img src="https://img-blog.csdnimg.cn/20210712210334254.png" >

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
#define EACH_CASE(cass) for (cin >> cass; cass; cass--)

#define LS l, mid, rt << 1
#define RS mid + 1, r, rt << 1 | 1
#define GETMID (l + r) >> 1

using namespace std;

template<typename T> inline void Read(T &x){T f = 1; x = 0;char s = getchar();while(s < '0' || s > '9'){if(s == '-') f = -1; s = getchar();}while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=getchar();}x*=f;}
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
template<typename T> inline void read(T &f) { f = 0; T fu = 1; char c = getchar();while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }f *= fu;}
template<typename T> inline void write(T x) { if(x < 0) x = ~(x - 1), putchar('-'); if(x > 9) write(x / 10); putchar(x % 10 + '0'); }

const int N = 250000;
int n;
int dis[N], vis[N];
struct Edge{ int nxt, to, val; }edge[N];
int head[N];
int cnt;
int stt, tgt;

inline void Init (){
        for(int i = 0; i < N; i ++){
                vis[i] = 0;
                dis[i] = -1e9;
                head[i] = -1;
        }
        cnt = 0;
        stt = 1e9, tgt = -1;
} 

inline void AddEdge (int from, int to, int val){
        edge[++cnt].nxt = head[from];
        edge[cnt].to = to;
        edge[cnt].val = val;
        head[from] = cnt;
}

inline void DrawMap (){
        for (int i = 0, a, b, c; i < n; i ++){
                scanf("%d%d%d", &a, &b, &c);
                AddEdge(a - 1, b, c);
                
                stt = MIN(stt, a - 1);
                tgt = MAX(tgt, b);
        }
        for (int i = stt; i <= tgt; i ++){
                AddEdge(i - 1, i, 0);
                AddEdge(i, i - 1, -1);
        }
}

inline void SPFA (int start){
        dis[start] = 0;
        queue<int> que; que.push(start); vis[start] = 1;
        while (que.size()){
                int x = que.front(); que.pop(); vis[x] = 0;
                for (int i = head[x]; ~i; i = edge[i].nxt){
                        int y = edge[i].to;
                        if (dis[y] < dis[x] + edge[i].val){
                                dis[y] = dis[x] + edge[i].val;
                                if (!vis[y]) vis[y] = 1, que.push(y);
                        }
                }
        }
}

CHIVAS_{
        while (scanf("%d", &n) == 1){
                Init();
                DrawMap();
                SPFA(stt);
                printf("%d\n", dis[tgt]);
        }
        _REGAL;
}
```
