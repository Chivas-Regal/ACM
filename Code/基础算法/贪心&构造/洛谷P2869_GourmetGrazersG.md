# 🔗
<a href="https://www.luogu.com.cn/problem/P2869"><img src="https://s2.loli.net/2021/12/30/iAuGayU2cfsNeOn.png"></a>

# 💡
一个很显然的贪心题  
但注意这里有两个关键字：价格，口感  
这两个关键字同级，如果直接进行双关键字排序然后双关键字`lowerbound`会导致因为关键字主次之分产生的错误比较  
留意一下最后要求的东西是最小价格  
  
那么我们深究一下问题：保证口感的同时，选取价格要求范围内最小的  
那么我们可以只对口感排序，从大口感奶牛开始往小口感扫  
每扫一个口感，就要将这个口感以上所有的草的价格都加到一个容器内  
那么这组容器对应的奶牛口感一定是满足的  
那么我们只需要`lowerbound`出最小的满足价格要求的价格即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e5 + 10;
multiset<int> mst;
struct grass {
        int p, q;
        inline friend bool operator < (grass a, grass b) {
                if (a.q != b.q) return a.q < b.q;
                return a.p < b.p;
        }
} g[N];
struct cow {
        int a, b;
        inline friend bool operator < (cow a, cow b) {
                if (a.b != b.b) return a.b < b.b;
                return a.a < b.a;
        }
} c[N];
int n, m;

int main () {
        cin >> n >> m;
        for ( int i = 0; i < n; i ++ ) cin >> c[i].a >> c[i].b;
        for ( int i = 0; i < m; i ++ ) cin >> g[i].p >> g[i].q;
        sort ( g, g + m );
        sort ( c, c + n );

        ll res = 0;
        for ( int i = n - 1, j = m - 1; i >= 0; i -- ) {
                while ( j >= 0 && g[j].q >= c[i].b ) 
                        mst.insert(g[j].p),
                        j --;
                multiset<int>::iterator it = mst.lower_bound(c[i].a);
                if ( it == mst.end() ) {
                        cout << "-1" << endl;
                        return 0;
                }
                res += (ll)*it;
                mst.erase(it);
        }
        cout << res << endl;
}
```
