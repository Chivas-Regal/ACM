# 🔗
<a href="https://codeforces.com/gym/102163/problem/A"><img src="https://s2.loli.net/2022/01/05/OLajGf3wosketHd.png"></a>

# 💡
答案问我们在满足一定条件下的结果，要最优的  
可以使用二分答案  
  
我们对结果  <img src="https://latex.codecogs.com/svg.image?\inline&space;len" title="\inline len" /> 进行二分，思考这个答案如何进行  <img src="https://latex.codecogs.com/svg.image?\inline&space;check" title="\inline check" />  
  
首先，这两条线的长度都至少为  <img src="https://latex.codecogs.com/svg.image?\inline&space;len\times2" title="\inline len\times2" />   
我们设横线为  <img src="https://latex.codecogs.com/svg.image?\inline&space;p" title="\inline p" /> 竖线为  <img src="https://latex.codecogs.com/svg.image?\inline&space;q" title="\inline q" /> ，每条线都有  <img src="https://latex.codecogs.com/svg.image?\inline&space;\{a,b,pos\}" title="\inline \{a,b,pos\}" /> ，即端点、垂直坐标，我们枚举竖线，满足的情况应为  <img src="https://latex.codecogs.com/svg.image?\inline&space;q.pos\in[p.a+len,p.b-len]" title="\inline q.pos\in[p.a+len,p.b-len]" /> 且  <img src="https://latex.codecogs.com/svg.image?\inline&space;q.pos\in[q.a+len,q.b-len]" title="\inline q.pos\in[q.a+len,q.b-len]" />，这个集合  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha" title="\inline \alpha" />  是包含在集合  <img src="https://latex.codecogs.com/svg.image?\inline&space;\beta:q.pos\in[p.a,p.b]" title="\inline q.pos\in[p.a+len,p.b-len]" /> 中的，我们首先要满足  <img src="https://latex.codecogs.com/svg.image?\inline&space;\alpha" title="\inline \alpha" /> 才能找  <img src="https://latex.codecogs.com/svg.image?\inline&space;\beta" title="\inline \beta" />      
我们可以把这两个情况用两种方式同步求  
   

对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;\beta" title="\inline \alpha" />，可以发现这三者有偏序关系，所以排序就可以解决  
我们存入每个横线的  <img src="https://latex.codecogs.com/svg.image?\inline&space;a+len" title="\inline l" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;b-len" title="\inline b" /> 以及竖线的  <img src="https://latex.codecogs.com/svg.image?\inline&space;pos" title="\inline pos" /> ，将它们进行排序后进行遍历，如果当前遍历到的是横线的  <img src="https://latex.codecogs.com/svg.image?\inline&space;a" title="\inline a" /> ，就把这个横线的  <img src="https://latex.codecogs.com/svg.image?\inline&space;pos" title="\inline pos" /> 存入，如果是  <img src="https://latex.codecogs.com/svg.image?\inline&space;b" title="\inline b" /> 就把这个横线的  <img src="https://latex.codecogs.com/svg.image?\inline&space;pos" title="\inline pos" /> 弹出，这个可以用一个 `multiset` 来维护  
如果遍历到的是  <img src="https://latex.codecogs.com/svg.image?\inline&space;q" title="\inline q" /> 的  <img src="https://latex.codecogs.com/svg.image?\inline&space;pos" title="\inline pos" /> ，就是子集的求法  
已知所有存在 `multiset` 中的  <img src="https://latex.codecogs.com/svg.image?\inline&space;pos" title="\inline pos" /> 都是满足第一个集合的情况，我们在其中进行二分出满足  <img src="https://latex.codecogs.com/svg.image?\inline&space;[q.a+len" title="\inline [p.a" /> 这个子集的最左端，如果这个点也能满足  <img src="https://latex.codecogs.com/svg.image?\inline&space;\le&space;q.b-len" title="\inline \le&space;q.b-len" /> 那么就说明可能存在比这个答案更大的情况，我们就  <img src="https://latex.codecogs.com/svg.image?\inline&space;check" title="\inline check" /> 成功了  


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
onst int N = 1e5 + 10;

struct node {
        int a, b, pos;
        inline friend bool operator < ( node a, node b ) {
                if ( a.a != b.a ) return a.a < b.a;
                return a.b < b.b;
        }
} p[N], q[N];
int n, m;

inline bool Check ( int len ) {
        vector<node> vec;
        for ( int i = 0; i < n; i ++ ) {
                if ( p[i].b - p[i].a >= 2 * len ) 
                        vec.push_back({p[i].a + len, 1, p[i].pos}), // 优先满足区间的左端点
                        vec.push_back({p[i].b - len, 3, p[i].pos}); // 最后满足区间的右端点
        }
        for ( int i = 0; i < m; i ++ ) {
                if ( q[i].b - q[i].a >= 2 * len ) 
                        vec.push_back({q[i].pos, 2, i}); // 我们要尽可能在两个端点中间看看有没有 q[i].pos
        }
        sort ( vec.begin(), vec.end() );

        multiset<int> mst;
        for ( auto i : vec ) {
                if ( i.b == 1 ) mst.insert(i.pos);
                else if ( i.b == 3 ) mst.erase(mst.find(i.pos));
                else {
                        auto id = mst.lower_bound(q[i.pos].a + len); // 找子集合的区间左端点
                        if ( id == mst.end() ) continue; // 找不到
                        if ( *id <= q[i.pos].b - len ) return true;  // 这个也能满足子集合的区间右端点
                }
        }
        return false;
}

inline void Solve () {
        cin >> n >> m;
        for ( int i = 0, x, y, z; i < n; i ++ ) cin >> x >> y >> z, p[i] = {min(x, y), max(x, y), z};
        for ( int i = 0, x, y, z; i < m; i ++ ) cin >> x >> y >> z, q[i] = {min(x, y), max(x, y), z};

        int l = 0, r = 5e4;
        int res = 0;
        while ( l <= r ) {
                int mid = (l + r) >> 1;
                if ( Check(mid) ) l = mid + 1, res = mid;
                else r = mid - 1;
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
