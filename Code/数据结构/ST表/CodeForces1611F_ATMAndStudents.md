# 🔗
<a href="https://codeforces.com/contest/1611/problem/F"><img src="https://i.loli.net/2021/11/26/piPkK8fFsSXBa5C.png"></a>

# 💡
看到这个题首先会想一段区间会被前缀影响也会被后缀影响，那么我们可以采用区间求解的形式  
  
由于收益的累加是从前往后的，所以我们建立一个前缀和  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{sum\}" title="\inline \{sum\}" />  表示从  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" />  到  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  这一段的总收益为  <img src="https://latex.codecogs.com/svg.image?\inline&space;sum[i]" title="\inline sum[i]" />    
如果我们选  <img src="https://latex.codecogs.com/svg.image?\inline&space;[l,r]" title="\inline [l,r]" />  这一段，因为不看前面的收益了，所以从  <img src="https://latex.codecogs.com/svg.image?\inline&space;l" title="\inline l" />  到  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" />  的准确收益会是  <img src="https://latex.codecogs.com/svg.image?\inline&space;sum[x]-sum[l-1]" title="\inline sum[x] - sum[l - 1]" />   
而这一段能否被选择的关键在于**这一段准确收益的最小值是否低于<img src="https://latex.codecogs.com/svg.image?\inline&space;s" title="\inline s" />**  
  
好了， <img src="https://latex.codecogs.com/svg.image?\inline&space;\{sum\}" title="\inline \{sum\}" />  的**区间最小值**，可以开一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;ST" title="\inline ST" />  表  

```cpp
for ( int i = 1; i <= n; i ++ ) st[i][0] = sum[i];

inline void Build () {
        int k = 32 - __builtin_clz(n) - 1;
        for ( int j = 1; j <= k; j ++ ) {
                for ( int i = 1; i + (1 << j) - 1 <= n; i ++ ) {
                        st[i][j] = min ( st[i][j - 1], st[i + (1 << (j - 1))][j - 1] );
                }
        }
}
inline ll Query ( int l, int r ) {
        int k = 32 - __builtin_clz(r - l + 1) - 1;
        return min ( st[l][k], st[r - (1 << k) + 1][k] );
}
```

那么如何确定最多能选多长的区间呢？  
由于区间长度的行于不行单调递增  
那么可以采用**二分区间长度**，对每一个二分到的区间长度下的区间最小值（准确收益下的）逐一判断  
如果不可行说明我们这个选的太长了，应该跑小的那一半，否则跑大的那一半  

```cpp
inline bool this_MinInLen ( int len ) {
        for ( int i = 1; i + len - 1 <= n; i ++ ) {
                ll cur = Query ( i, i + len - 1 );
                if ( s + (cur - sum[i - 1]) >= 0 ) { // cur-sum[i-1]：准确收益
                        if ( len > res.second - res.first + 1 ) res = {i, i + len - 1};
                        return true;
                }
        }
        return false;
}


int l = 1, r = n;
while ( l <= r ) {
        int mid = ( l + r ) >> 1;
        if ( this_MinInLen(mid) ) l = mid + 1;
        else                      r = mid - 1;
}
this_MinInLen ( l );
```

时间复杂度： $O(nlogn)$  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e5 + 10;
ll a[N], sum[N];
ll st[N][100];
int n;
ll s;
pair<int, int> res;

inline void Build () {
        int k = 32 - __builtin_clz(n) - 1;
        for ( int j = 1; j <= k; j ++ ) {
                for ( int i = 1; i + (1 << j) - 1 <= n; i ++ ) {
                        st[i][j] = min ( st[i][j - 1], st[i + (1 << (j - 1))][j - 1] );
                }
        }
}
inline ll Query ( int l, int r ) {
        int k = 32 - __builtin_clz(r - l + 1) - 1;
        return min ( st[l][k], st[r - (1 << k) + 1][k] );
}
inline bool this_MinInLen ( int len ) {
        for ( int i = 1; i + len - 1 <= n; i ++ ) {
                ll cur = Query ( i, i + len - 1 );
                if ( s + (cur - sum[i - 1]) >= 0 ) {
                        if ( len > res.second - res.first + 1 ) res = {i, i + len - 1};
                        return true;
                }
        }
        return false;
}

inline void Solve () {
        res = {0, -1};

        cin >> n >> s;
        for ( int i = 1; i <= n; i ++ ) {
                cin >> a[i];
                sum[i] = sum[i - 1] + a[i];
                st[i][0] = sum[i];
        }

        Build ();

        int l = 1, r = n;
        while ( l <= r ) {
                int mid = ( l + r ) >> 1;
                if ( this_MinInLen(mid) ) l = mid + 1;
                else                      r = mid - 1;
        }
        this_MinInLen ( l );
        
        if ( res.first <= res.second ) cout << res.first << " " << res.second << endl;
        else                           cout << -1 << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
