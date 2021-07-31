<h1 align="center">【模板】</h1>

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
#include <string>
#include <vector>
#include <cstdio>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>
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

#define CHIVAS int main()
#define _REGAL exit(0)

#define SP system("pause")
#define IOS ios::sync_with_stdio(false)
#define map unordered_map

#define PB(x) push_back(x)
#define ALL(a) ((a).begin(),(a).end())
#define MEM(a, b) memset(a, b, sizeof(a))
#define EACH_CASE(cass) for (scanf("%d", &cass); cass; cass--)

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

const int maxn = 2e5 + 10;

int x[maxn], y[maxn];
int n, m;

struct Edge{//前向星中，前标为0表示正图，1表示反图
    int nxt, to;
}edge[2][maxn];
int head[2][maxn];
int cnt[2];

int nod[maxn];//集合代表（类似并查集）
vector<int> inv;//DFS1得到的反序列
map<int, int> vis;//记录是否使用过
map<int, ll> num;//记录每个集合有多少个元素

inline void Init(){
    vis.clear();
    inv.clear();
    num.clear();
    for(int i = 0; i <= m; i ++) head[1][i] = head[0][i] = -1;
    for(int i = 0; i <= n; i ++) nod[i] = i;
    cnt[1] = cnt[0] = 0;
}
inline void add_edge(int id, int from, int to){
    edge[id][++cnt[id]] = {head[id][from], to};
    head[id][from] = cnt[id];
}
inline void DFS1(int x){//1.正向遍历出反向（当成无向图的）遍历顺序
    vis[x] = 1;
    for(int i = head[0][x]; ~i; i = edge[0][i].nxt){//正向一个集合一个集合地遍历一遍
        if(!vis[edge[0][i].to]) DFS1(edge[0][i].to);
    }inv.push_back(x);//后序遍历得到反遍历序列
}
inline void DFS2(int x, int y){
    vis[x] = 0;
    nod[x] = y;//压入集合
    for(int i = head[1][x]; ~i; i = edge[1][i].nxt){//反向对之前遍历过的集合进行遍历
        if(vis[edge[1][i].to]) DFS2(edge[1][i].to, y);
    }
}
inline void solve(){
    scanf("%d%d", &n, &m);Init();
    for(int i = 0; i < m; i ++){
        scanf("%d%d", &x[i], &y[i]);
        add_edge(0, x[i], y[i]);
        add_edge(1, y[i], x[i]);
    }

    for(int i = 0; i < m; i ++){
        if(!vis[x[i]]) DFS1(x[i]);
    }
    for(int i = inv.size() - 1; i >= 0; i --){//按正序后的序列进行遍历
        if(vis[inv[i]]) DFS2(inv[i], inv[i]);
    }

    map<int, int> used;
    for(int i = 0; i < m; i ++){//计算一个集合内的元素个数
        if(!used[x[i]]) used[x[i]] = 1, num[nod[x[i]]] ++;
    }

    ll res = 0;
    for(auto &i : num){//得到C(k, 2)的累加和
        res += i.second * (i.second - 1) / 2;
    }printf("%lld\n", res);
}
CHIVAS{IOS;
    int cass;
    EACH_CASE(cass){
        solve();
    }
    _REGAL;
}
```
