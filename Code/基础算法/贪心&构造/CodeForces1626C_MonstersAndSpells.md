# 🔗
<a href="https://codeforces.com/contest/1626/problem/C"><img src="https://s2.loli.net/2022/01/18/1VrQXE9Npse7bBY.png"></a>

# 💡  
建立一个这样的模型 <img src="https://s2.loli.net/2022/01/18/Q1KzUoAIOs4lqR8.jpg">  
  
我们可以从  <img src="https://latex.codecogs.com/svg.image?\inline&space;k[i],h[i]" title="\inline k[i],h[i]" /> 中得出，我们至少要从  <img src="https://latex.codecogs.com/svg.image?\inline&space;k[i]-h[i]+1" title="\inline k[i]-h[i]+1" /> 这个时刻开始释放  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 的攻击  
才能安全地在  <img src="https://latex.codecogs.com/svg.image?\inline&space;k[i]" title="\inline k[i]" /> 时释放出  <img src="https://latex.codecogs.com/svg.image?\inline&space;h[i]" title="\inline h[i]" /> 的攻击  
为了贪心，我们得出开始时间  <img src="https://latex.codecogs.com/svg.image?\inline&space;beg[i]=k[i]-h[i]+1" title="\inline beg[i]=k[i]-h[i]+1" /> ，结束时间  <img src="https://latex.codecogs.com/svg.image?\inline&space;k[i]" title="\inline k[i]" />   
  
而需要更早蓄力更晚触发的中途就可以将晚蓄力早触发的怪消灭  
那么我们要保证蓄力是一个严格单调递增的序列即可  
  
但是要考虑到三角形部分重叠的情况  
这种就要在之前蓄力的基础上消灭该怪兽后不停止继续蓄力  
才可以安全消灭后面那只怪兽  
所以要合并一下区间  
对于每个  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> ，如果存在  <img src="https://latex.codecogs.com/svg.image?\inline&space;j<i" title="\inline j<i" /> 并且满足上面条件（  <img src="https://latex.codecogs.com/svg.image?\inline&space;beg[i]\ge&space;beg[j]\;and\;beg[i]\le&space;k[j]" title="\inline beg[i]\ge&space;beg[j]\;and\;beg[i]\le&space;k[j]" />  ），那么合并区间操作为  <img src="https://latex.codecogs.com/svg.image?\inline&space;beg[i]=beg[j]" title="\inline beg[i]=beg[j]" />   
  
然后我们就可以用单调栈求上升序列了  
对于每个序列累加  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^{k-beg+1}i" title="\inline \sum\limits_{i=1}^{k-beg+1}i" /> 的和  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void Solve () {
        ll n; cin >> n;
        ll k[n + 10], h[n + 10];
        ll beg[n + 10];
        for ( ll i = 0; i < n; i ++ ) cin >> k[i];
        for ( ll i = 0; i < n; i ++ ) cin >> h[i];
 
        for ( ll i = 0; i < n; i ++ ) beg[i] = k[i] - h[i] + 1;
        for ( ll i = 0; i < n; i ++ ) {
                for ( int j = i; j >= 0; j -- ) {
                        if ( beg[i] >= beg[j] && beg[i] <= k[j] ) beg[i] = beg[j];
                }
        }
        
        stack<pair<ll, ll> > stk;
        for ( ll i = 0; i < n; i ++ ) {
                ll x = beg[i];
                while ( stk.size() && stk.top().second >= x ) stk.pop();
                stk.push({x, k[i]});
        }
 
        ll res = 0;
        while ( stk.size() ) {
                ll fir = stk.top().first, sec = stk.top().second; stk.pop();
                res += (1 + sec - fir + 1) * (sec - fir + 1) / 2;
        }
        cout << res << endl;
 

```
