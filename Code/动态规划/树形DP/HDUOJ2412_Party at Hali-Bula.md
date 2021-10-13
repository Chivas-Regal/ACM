# 🔗
https://acm.hdu.edu.cn/showproblem.php?pid=2412

# 💡
选了上司就不能选员工了  
所以我们设dp[i][0]表示不选根节点i时的最大选数，dp[i][1]表示选根节点i时的最大选数  
dp[i][0]了话，员工选不选都行，就对每个子节点求最优即可  
dp[i][1]了话，员工不能选，+dp[son[i]][0]    
  
在选使用哪个子状态时，使用的那个子状态如果是多解，那么此时父状态也是多解  
最后还要判断一下总问题的两种可能性是不是相同


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int N = 205;
struct Edge {
        int nxt; string to;
        inline Edge () {}
        inline Edge ( int _nxt, string _to ) : nxt(_nxt), to(_to) {}
} edge[2 * N];
unordered_map <string, int> head, vis, num;
unordered_map <string, pair<int, int> > dp, f; 
int cnt, n;
string stt; 

inline void Init () {
        head.clear();
        vis.clear();
        num.clear();
        cnt = 0;
}
inline void Add_edge ( string from, string to ) { edge[++cnt] = Edge(head[from], to); head[from] = cnt; }
inline void DFS ( string x ) {
        if ( !num[x] ) { dp[x] = make_pair(0, 1); f[x] = make_pair(0, 0); return; }
        vis[x] = 1;
        dp[x] = make_pair(0, 1);
        f[x] = make_pair(0, 0);
        for ( int i = head[x]; i; i = edge[i].nxt ) {
                string to = edge[i].to;
                if ( !vis[to] ) DFS ( to );

                if ( dp[to].first == dp[to].second ) { // 看看通过哪个推最优解，如果子阶段是多解，那么它对应的
                        dp[x].first += dp[to].first;
                        f[x].first = 1;
                } else if ( dp[to].first > dp[to].second ) {
                        dp[x].first += dp[to].first;
                        if ( f[to].first ) f[x].first = 1;
                } else if ( dp[to].first < dp[to].second ) {
                        dp[x].first += dp[to].second;
                        if( f[to].second ) f[x].first = 1;
                }
                dp[x].second += dp[to].first;
                if ( f[to].first ) f[x].second = 1;
        }
}

int main () {
        while ( cin >> n, n ) {
                Init();
                cin >> stt;
                for ( int i = 0; i < n - 1; i ++ ) {
                        string a, b; cin >> a >> b;
                        Add_edge( b, a ); num[b] ++;
                }
                DFS ( stt );
                if ( dp[stt].first > dp[stt].second ) { // 看看利用哪个得到最优解
                        cout << dp[stt].first << " " << (f[stt].first ? "No" : "Yes") << endl;
                } else if ( dp[stt].first < dp[stt].second ) {
                        cout << dp[stt].second << " " << (f[stt].second ? "No" : "Yes") << endl;
                } else {
                        cout << dp[stt].first << " " << "No" << endl;
                }
        }
        return 0;
}
```
