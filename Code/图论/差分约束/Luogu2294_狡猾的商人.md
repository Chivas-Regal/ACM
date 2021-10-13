# 🔗
<a href="https://www.luogu.com.cn/problem/P2294"><img src="https://i.loli.net/2021/09/30/NfUE4PLFRgHaudw.png"></a>

# 💡
对于给定的a,b,c  
可以使用前缀和，(b)-(a-1)=c  
那么就建边:  
(b)-(a-1)<=c  
(a-1)-(b)<=-c  
  
即然检查正确性，那么就跑图，对于每个连通块看一下有没有负环  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll N = 1e2 + 10, M = 2e3 + 10;

int stt[M], tgt[M], val[M], cnt;
int dis[N], vis[N];
int n, m;

inline bool Bellman_Ford ( int x ) {
        memset ( dis, 0x3f3f3f, sizeof dis ); dis[x] = 0;
        for ( int k = 0; k < n - 1; k ++ ) 
                for ( int i = 0; i < cnt; i ++ )
                        dis[tgt[i]] = min ( dis[tgt[i]], dis[stt[i]] + val[i] ), 
                        vis[tgt[i]] = 1;
        for ( int i = 0; i < cnt; i ++ )
                if ( dis[tgt[i]] > dis[stt[i]] + val[i] ) 
                        return false;
        return true;
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif 
        int cass;
        for ( scanf("%d", &cass); cass; cass -- ) {
                scanf("%d%d", &n, &m);
                cnt = 0; memset ( vis, 0, sizeof vis );
                for ( int i = 0, a, b, c; i < m; i ++ ) 
                        scanf("%d%d%d", &a, &b, &c),
                        stt[cnt] = a - 1, tgt[cnt] = b, val[cnt ++] = c,
                        stt[cnt] = b, tgt[cnt] = a - 1, val[cnt ++] = -c;
                dis[0] = 0;
                
                bool flag = true;
                for ( int i = 0; i <= n; i ++ ) {
                        if ( !vis[i] && !Bellman_Ford( i ) ) { flag = false; break; }
                }
                if ( flag ) puts("true");
                else        puts("false");
        }
        return 0;
}
```
