# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7055"><img src="https://i.loli.net/2021/10/14/DHYf7mUtuZ8W9T5.png"></a>

# 💡
对于这种，我们分开考虑贡献  
对于一个字符出现的位置进行记录  
并可以得出一个个这个字符没有出现的连续段落，大小设置为sz    
  
相差i个的段落的位置个数的相乘每一个贡献是i^2  
那么对于每个字符贡献就是  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}&\sum\limits_{i=1}^{sz}\sum\limits_{j=i&plus;1}^{sz}[a_ia_j(j-i)^2]\\=&\sum\limits_{i=1}^{sz}\sum\limits_{j=i&plus;1}^{sz}[a_j*a_ii^2-2a_jj*a_ii&plus;a_jj^2*a_i]\end{aligned}" title="\begin{aligned}&\sum\limits_{i=1}^{sz}\sum\limits_{j=i+1}^{sz}[a_ia_j(j-i)^2]\\=&\sum\limits_{i=1}^{sz}\sum\limits_{j=i+1}^{sz}[a_j*a_ii^2-2a_jj*a_ii+a_jj^2*a_i]\end{aligned}" />  
看到这个式子应很快反应到，对于j:[2->sz]，每次累加的都是(j-1)的三个前缀和  
  
所以设三个前缀和  
`sum1[i]` 表示 `a[i] * i * i` 的前缀和  
`sum2[i]` 表示 `a[i] * i` 的前缀和  
`sum3[i]` 表示 `a[i]` 的前缀和  
然后j从2往n遍历，每次加上`a[j] * j * j * sum3[j-1]`再减去`a[j] * j * 2 * sum2[j - 1]`再加上`a[j] * sum1[j - 1]`  
  
把每个字符求得的贡献累加一下即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll mod = 998244353;

const ll N = 1e5 + 10;
ll sum1[N], sum2[N], sum3[N];

inline void Solve() {
        map<char, vector<ll> > los, mp;
        string s; cin >> s;
        for ( ll i = 0; i < s.size(); i ++ ) {
                mp[s[i]].push_back(i);
        }
        for ( auto i : mp ) {
                los[i.first].push_back(0); // 整体向后移，方便前缀和记录
                los[i.first].push_back(i.second[0] + 1);// 初始的区间
                for ( ll j = 1; j < i.second.size(); j ++ ) los[i.first].push_back(i.second[j] - i.second[j - 1]); // 两两区间
                los[i.first].push_back(s.size() - i.second.back()); // 最后的区间
        }
        ll res = 0;
        for ( auto i : los ) {
                for ( ll j = 1; j < i.second.size(); j ++ ) {
                        sum1[j] = (sum1[j - 1] + i.second[j] * j % mod * j % mod ) % mod;
                        sum2[j] = (sum2[j - 1] + i.second[j] * j % mod) % mod;
                        sum3[j] = (sum3[j - 1] + i.second[j]) % mod;
                }
                for ( ll j = 2; j < i.second.size(); j ++ ) {
                        res = ( res + i.second[j] * j % mod * j % mod * sum3[j - 1] % mod) % mod;
                        res = ((res - i.second[j] * j % mod * 2 % mod * sum2[j - 1] % mod) % mod + mod) % mod;
                        res = ( res + i.second[j] * sum1[j - 1] % mod) % mod;
                }
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
