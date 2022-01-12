# 🔗
<a href="https://codeforces.com/contest/1624/problem/D"><img src="https://s2.loli.net/2022/01/13/mcZylx8VHn47gIh.png"></a>

# 💡
由于**分配后的最小值最大**，所以我们肯定是希望均分  
根据回文串的性质，如果我们能找出来一对一对的相同字符，那么我们可以把它分到每个字符串两侧  
所以我们拿出来成对的字符，即偶数个字符  <img src="https://latex.codecogs.com/svg.image?\inline&space;num2/2" title="\inline num2/2" />    
把它们分给  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" /> 个人  
先记为分成了  <img src="https://latex.codecogs.com/svg.image?\inline&space;res" title="\inline res" /> 轮  
那么一定会有  <img src="https://latex.codecogs.com/svg.image?\inline&space;k-num2\%k" title="\inline k-" /> 比  <img src="https://latex.codecogs.com/svg.image?\inline&space;num2\%k" title="\inline num2\%k" /> 少了两个，我们尽可能均分，让那  <img src="https://latex.codecogs.com/svg.image?\inline&space;num2\%k" title="\inline num2\%k" /> 个人每个人拿出来一个字符，此时和它配对的字符落单放到中间，然后在总字符串内的所有落单的字符个数中加进这些字符，设加后总共有  <img src="https://latex.codecogs.com/svg.image?\inline&space;num1" title="\inline num1" /> 个单字符，这些单字符可以拼给那  <img src="https://latex.codecogs.com/svg.image?\inline&space;k-num2\%k" title="\inline k-num2\%k" /> 个人，如果给的完，答案就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;num2/k\times2+1" title="\inline num2/k\times2+1" /> ，否则就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;num2/k\times2" title="\inline num2/k\times2" /> 

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void Solve () {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        int cnt[400]; memset(cnt, -1, sizeof cnt);
        int vis[200005] = {0};
        int num2 = 0;
        for ( int i = 0; i < n; i ++ ) {
                if ( ~cnt[s[i]] ) {
                        vis[i] = 1;
                        vis[cnt[s[i]]] = 1;
                        cnt[s[i]] = -1;
                        num2 ++;
                } else {
                        cnt[s[i]] = i;
                }
        }
        int num1 = n - num2 * 2;
 
        int lft_ppl = k - num2 % k;
        num1 += num2 % k;
        if ( num1 >= lft_ppl ) cout << num2 / k * 2 + 1 << endl;
        else cout << num2 / k * 2 << endl;
}
```
