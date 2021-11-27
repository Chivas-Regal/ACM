# 🔗
<a href="https://codeforces.com/problemset/problem/1557/C"><img src="https://i.loli.net/2021/09/13/7RtnEshvGNxBioz.png"></a>

# 💡
首先把整个<img src="https://latex.codecogs.com/svg.image?n" title="n" />个k位数画成一个<img src="https://latex.codecogs.com/svg.image?n\times&space;k" title="n\times k" />的矩阵  
然后对于每一列，也就是<img src="https://latex.codecogs.com/svg.image?n" title="n" />个数的每一位  
如果全<img src="https://latex.codecogs.com/svg.image?1" title="1" />了话<img src="https://latex.codecogs.com/svg.image?\And&space;=1" title="\And =1" />，有一个<img src="https://latex.codecogs.com/svg.image?0" title="0" />就是<img src="https://latex.codecogs.com/svg.image?0" title="0" />。  
偶数个<img src="https://latex.codecogs.com/svg.image?1" title="1" />了话<img src="https://latex.codecogs.com/svg.image?\bigoplus&space;=0" title="\bigoplus =0" />，奇数个<img src="https://latex.codecogs.com/svg.image?\bigoplus&space;=1" title="\bigoplus =1" />  
  
得到两条性质：  
**n为奇数时：** 这一位最多在含有偶数个<img src="https://latex.codecogs.com/svg.image?1" title="1" />的时候与和异或相等，都是<img src="https://latex.codecogs.com/svg.image?0" title="0" />  
**n为偶数时：** 这一位在全<img src="https://latex.codecogs.com/svg.image?1" title="1" />时，<img src="https://latex.codecogs.com/svg.image?\And&space;=1" title="\And =1" />，<img src="https://latex.codecogs.com/svg.image?\bigoplus&space;=0" title="\bigoplus =0" />。而在全<img src="https://latex.codecogs.com/svg.image?1" title="1" />以下的偶数个时，<img src="https://latex.codecogs.com/svg.image?\And&space;=\bigoplus&space;=0" title="\And =\bigoplus =0" />  
  
那么有两类解决方案：  
**n为奇数时：**   
每一位最多只能相等，就是在每一位都有偶数个<img src="https://latex.codecogs.com/svg.image?1" title="1" />或者全<img src="https://latex.codecogs.com/svg.image?1" title="1" />的情况下  
所以我们对每一位的n个数字进行排列组合，设偶数个<img src="https://latex.codecogs.com/svg.image?1" title="1" />和全<img src="https://latex.codecogs.com/svg.image?1" title="1" />的组合情况累加为<img src="https://latex.codecogs.com/svg.image?has\_Eve&plus;1" title="has\_Eve+1" />    
那么答案就是  
<img src="https://latex.codecogs.com/svg.image?(has\_Eve&plus;1)^k" title="(has\_Eve+1)^k" />   
**n为偶数时：**  
每一位可以是相等，就是在每一位在非全<img src="https://latex.codecogs.com/svg.image?1" title="1" />且有偶数个的情况下，设为<img src="https://latex.codecogs.com/svg.image?has\_Eve" title="has\_Eve" />  
当前位还可以大于，就是在这一位(设为<img src="https://latex.codecogs.com/svg.image?i" title="i" />)全<img src="https://latex.codecogs.com/svg.image?1" title="1" />的情况下，那么前面的所有位都可以任意个<img src="https://latex.codecogs.com/svg.image?\And&space;=1" title="\And =1" />组合，方案有<img src="https://latex.codecogs.com/svg.image?(2^n)^{i-1}" title="(2^n)^{i-1}" />个  
所以这一位就是要递推，答案是  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}i\{1\to&space;k\}:\\&res=res\times&space;has\_Eve&space;&plus;&space;(2^n)^{i-1}\end{aligned}" title="\begin{aligned}i\{1\to k\}:\\&res=res\times has\_Eve + (2^n)^{i-1}\end{aligned}" />

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
ll f[N];

inline void Get_F () {
        f[0] = 1;
        for ( int i = 1; i < N; i ++ ) 
                f[i] = f[i - 1] * i % mod;
}
inline ll ksm ( ll a, ll b ) {
        ll res = 1;
        while ( b > 0 ) {
                if ( b & 1 ) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }
        return res;
}
inline ll C ( ll a, ll b ) {
        return f[a] * ksm(f[b], mod - 2) % mod * ksm(f[a - b], mod - 2) % mod;
}

inline void solve () {
        ll n, k; cin >> n >> k;

        ll has_Eve = 0; for ( ll i = 0; i < n; i += 2 ) has_Eve = (has_Eve + C(n, i)) % mod;
        if ( n & 1 ) {
                cout << ksm ( has_Eve + 1, k) << endl; // 每一位都是要么选偶数个要么全选，只有这样才能相等
        } else {
                ll res = 1;
                for ( ll i = 1; i <= k; i ++ ) {
                        res = res * has_Eve % mod;                 // 第i位不全是1 -- 前一位满足的方案数乘它
                        res = (res + ksm(ksm(2, n), i - 1)) % mod; // 第i位全是1 -- 前面的可以随意搞
                }
                cout << res << endl;
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        Get_F();
        int cass;
        for ( cin >> cass; cass; cass -- ) {
                solve();
        }
}
```
