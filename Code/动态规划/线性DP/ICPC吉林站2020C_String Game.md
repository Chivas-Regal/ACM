# 🔗
<a href="https://codeforces.com/gym/102800/attachments"><img src="https://i.loli.net/2021/11/11/wdMOylHJ54xEeXm.png"></a>

<details>
  <summary align="center">查看题解</summary>
           
# 💡
~~依稀记得好像做过类似的题来着~~  
我们每次遇到一个字母  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline c" />   
在所给序列  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline c" />  出现的位置假设为  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  
因为当这个字母出现之后，比它小一位也就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;i-1" title="\inline i-1" /> 位多了一个渠道推向第  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 位，那么：  
如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;i\neq1" title="\inline i\neq1" />  那么  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i]+=dp[i-1]" title="\inline dp[i]+=dp[i-1]" />   
而当  <img src="https://latex.codecogs.com/svg.image?\inline&space;i=1" title="\inline i=1" /> 时，我们只是做到让推的源头  <img src="https://latex.codecogs.com/svg.image?\inline&space;+1" title="\inline +1" /> 而已，那么：  
如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;i=1" title="\inline i=1" /> 那么  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp[i]++" title="\inline dp[i]++" />   

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 1e3 + 10;
const int mod = 1e9 + 7;
ll dp[N];
int main () {
        ios::sync_with_stdio(false);
        string s1, s2;
        while ( cin >> s1 >> s2 ) {
                memset ( dp, 0, sizeof dp );
                for ( int i = 0; i < s1.size(); i ++ ) {
                        for ( int j = s2.size() - 1; j >= 0; j -- ) {
                                if ( s1[i] == s2[j] ) {
                                        if ( j ) dp[j] = (dp[j] + dp[j - 1]) % mod;
                                        else     dp[j] = (dp[j] + 1) % mod;
                                }
                        }
                }
                cout << dp[s2.size() - 1] << endl;
        }
}
```
